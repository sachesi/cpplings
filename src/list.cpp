#include "list.hpp"

#include "app_state.hpp"
#include "term.hpp"

#include <algorithm>
#include <format>
#include <optional>

namespace {

constexpr std::size_t col_spacing = 2;

// Appends text to a line while cutting it off at the terminal width. Escape
// sequences don't count towards the width.
class LineWriter {
public:
    LineWriter(std::string& out, int max_len) : out_(out), max_len_(static_cast<std::size_t>(max_len)) {}

    void text(std::string_view s) {
        for (std::size_t i = 0; i < s.size(); ++i) {
            unsigned char c = static_cast<unsigned char>(s[i]);
            bool continuation = (c & 0xC0) == 0x80;
            if (!continuation) {
                if (len_ >= max_len_) {
                    return;
                }
                ++len_;
            }
            out_ += s[i];
        }
    }

    void style(std::string_view escape) { out_ += escape; }

private:
    std::string& out_;
    std::size_t max_len_;
    std::size_t len_ = 0;
};

// Moves to the next line without scrolling when the cursor is on the last row.
void next_ln(std::string& out) {
    out += "\x1b[K\x1b[1E";
}

class ScrollState {
public:
    ScrollState(std::size_t n_rows, std::optional<std::size_t> selected, std::size_t max_scroll_padding)
        : n_rows_(n_rows),
          selected_(selected),
          offset_(selected ? (*selected > max_scroll_padding ? *selected - max_scroll_padding : 0) : 0),
          max_scroll_padding_(max_scroll_padding) {}

    std::size_t offset() const { return offset_; }
    std::optional<std::size_t> selected() const { return selected_; }
    std::size_t max_n_rows_to_display() const { return max_n_rows_to_display_; }

    void set_selected(std::size_t selected) {
        selected_ = selected;
        update_offset();
    }

    void select_next() {
        if (selected_) {
            set_selected(std::min(*selected_ + 1, n_rows_ - 1));
        }
    }

    void select_previous() {
        if (selected_) {
            set_selected(*selected_ > 0 ? *selected_ - 1 : 0);
        }
    }

    void select_first() {
        if (n_rows_ > 0) {
            set_selected(0);
        }
    }

    void select_last() {
        if (n_rows_ > 0) {
            set_selected(n_rows_ - 1);
        }
    }

    void set_n_rows(std::size_t n_rows) {
        n_rows_ = n_rows;
        if (n_rows_ == 0) {
            selected_.reset();
            return;
        }
        set_selected(selected_ ? std::min(*selected_, n_rows - 1) : 0);
    }

    void set_max_n_rows_to_display(std::size_t max_n_rows) {
        max_n_rows_to_display_ = max_n_rows;
        scroll_padding_ = std::min(max_n_rows_to_display_ / 4, max_scroll_padding_);
        update_offset();
    }

private:
    std::size_t n_rows_;
    std::size_t max_n_rows_to_display_ = 0;
    std::optional<std::size_t> selected_;
    std::size_t offset_;
    std::size_t scroll_padding_ = 0;
    std::size_t max_scroll_padding_;

    static std::size_t saturating_sub(std::size_t a, std::size_t b) { return a > b ? a - b : 0; }

    void update_offset() {
        if (!selected_) {
            return;
        }
        std::size_t min_offset =
            saturating_sub(*selected_ + scroll_padding_, saturating_sub(max_n_rows_to_display_, 1));
        std::size_t max_offset = saturating_sub(*selected_, scroll_padding_);
        std::size_t global_max_offset = saturating_sub(n_rows_, max_n_rows_to_display_);
        offset_ = std::min({std::max(offset_, min_offset), max_offset, global_max_offset});
    }
};

enum class Filter { Done, Pending, None };

class ListState {
public:
    std::string message;
    std::string search_query;

    explicit ListState(AppState& app_state)
        : app_state_(app_state),
          scroll_state_(app_state.exercises().size(), app_state.current_exercise_ind(), 5) {
        std::size_t name_col_width = 4;
        std::size_t path_col_width = 4;
        for (const Exercise& exercise : app_state.exercises()) {
            name_col_width = std::max(name_col_width, exercise.name.size());
            path_col_width = std::max(path_col_width, exercise.file_path.size());
        }
        name_col_width_ = name_col_width + col_spacing;
        path_col_width_ = path_col_width;
        set_term_size(term::size());
    }

    void set_term_size(term::Size size) {
        term_width_ = size.width;
        term_height_ = size.height;
        if (term_height_ == 0) {
            return;
        }
        constexpr int header_height = 1;
        // 1 progress bar, 2 footer message lines.
        constexpr int footer_height = 3;
        show_footer_ = term_height_ > header_height + footer_height;
        int rows = term_height_ - header_height - (show_footer_ ? footer_height : 0);
        scroll_state_.set_max_n_rows_to_display(static_cast<std::size_t>(std::max(rows, 0)));
    }

    Filter filter() const { return filter_; }

    void set_filter(Filter filter) {
        filter_ = filter;
        update_rows();
    }

    void select_next() { scroll_state_.select_next(); }
    void select_previous() { scroll_state_.select_previous(); }
    void select_first() { scroll_state_.select_first(); }
    void select_last() { scroll_state_.select_last(); }

    void reset_selected() {
        std::optional<std::size_t> selected = scroll_state_.selected();
        if (!selected) {
            message += "Nothing selected to reset!";
            return;
        }
        std::size_t ind = selected_to_exercise_ind(*selected);
        const std::string& name = app_state_.reset_exercise_by_ind(ind);
        message += std::format("The exercise `{}` has been reset", name);
        update_rows();
    }

    void apply_search_query() {
        message += "search:";
        message += search_query;
        message += '|';
        if (search_query.empty()) {
            return;
        }

        std::size_t row = 0;
        for (const Exercise& exercise : app_state_.exercises()) {
            if (!passes_filter(exercise)) {
                continue;
            }
            if (exercise.name.find(search_query) != std::string::npos) {
                scroll_state_.set_selected(row);
                return;
            }
            ++row;
        }
        message += " (not found)";
    }

    // Returns true if there was something to select.
    bool selected_to_current_exercise() {
        std::optional<std::size_t> selected = scroll_state_.selected();
        if (!selected) {
            message += "Nothing selected to continue at!";
            return false;
        }
        app_state_.set_current_exercise_ind(selected_to_exercise_ind(*selected));
        return true;
    }

    void draw() {
        if (term_height_ == 0) {
            return;
        }
        std::string out = "\x1b[?2026h\x1b[H";

        LineWriter header(out, term_width_);
        header.text("  Current  State    Name");
        header.text(std::string(name_col_width_ - 4, ' '));
        header.text("Path");
        next_ln(out);

        std::size_t n_displayed_rows = draw_rows(out);
        for (std::size_t i = n_displayed_rows; i < scroll_state_.max_n_rows_to_display(); ++i) {
            next_ln(out);
        }

        if (show_footer_) {
            draw_footer(out);
        }

        out += "\x1b[?2026l";
        term::write_stdout(out);
    }

private:
    AppState& app_state_;
    ScrollState scroll_state_;
    std::size_t name_col_width_ = 0;
    std::size_t path_col_width_ = 0;
    Filter filter_ = Filter::None;
    int term_width_ = 0;
    int term_height_ = 0;
    bool show_footer_ = true;

    bool passes_filter(const Exercise& exercise) const {
        switch (filter_) {
        case Filter::Done:
            return exercise.done;
        case Filter::Pending:
            return !exercise.done;
        case Filter::None:
            return true;
        }
        return true;
    }

    std::size_t selected_to_exercise_ind(std::size_t selected) const {
        std::size_t row = 0;
        const std::vector<Exercise>& exercises = app_state_.exercises();
        for (std::size_t i = 0; i < exercises.size(); ++i) {
            if (!passes_filter(exercises[i])) {
                continue;
            }
            if (row == selected) {
                return i;
            }
            ++row;
        }
        throw std::out_of_range("Invalid selection index");
    }

    void update_rows() {
        std::size_t n_rows = static_cast<std::size_t>(std::ranges::count_if(
            app_state_.exercises(), [&](const Exercise& e) { return passes_filter(e); }));
        scroll_state_.set_n_rows(n_rows);
    }

    void draw_exercise_name(LineWriter& writer, const Exercise& exercise) const {
        std::size_t match = search_query.empty() ? std::string::npos : exercise.name.find(search_query);
        if (match == std::string::npos) {
            writer.text(exercise.name);
            return;
        }
        std::string_view name = exercise.name;
        writer.text(name.substr(0, match));
        writer.style(term::magenta);
        writer.text(name.substr(match, search_query.size()));
        writer.style(term::default_fg);
        writer.text(name.substr(match + search_query.size()));
    }

    std::size_t draw_rows(std::string& out) const {
        std::size_t current = app_state_.current_exercise_ind();
        std::size_t offset = scroll_state_.offset();
        std::size_t max_rows = scroll_state_.max_n_rows_to_display();
        std::size_t row = 0;
        std::size_t n_displayed = 0;

        const std::vector<Exercise>& exercises = app_state_.exercises();
        for (std::size_t ind = 0; ind < exercises.size() && n_displayed < max_rows; ++ind) {
            const Exercise& exercise = exercises[ind];
            if (!passes_filter(exercise)) {
                continue;
            }
            if (row++ < offset) {
                continue;
            }

            LineWriter writer(out, term_width_);
            if (scroll_state_.selected() == offset + n_displayed) {
                writer.text("> ");
                writer.style(term::reverse);
                writer.style(term::bold);
            } else {
                writer.text("  ");
            }

            if (ind == current) {
                writer.style(term::red);
                writer.text(">>>>>>>  ");
            } else {
                writer.text("         ");
            }

            if (exercise.done) {
                writer.style(term::green);
                writer.text("DONE   ");
            } else {
                writer.style(term::yellow);
                writer.text("PENDING");
            }
            writer.style(term::default_fg);
            writer.text("  ");

            draw_exercise_name(writer, exercise);
            writer.text(std::string(name_col_width_ - exercise.name.size(), ' '));

            writer.style(term::blue);
            writer.style(term::underline);
            if (app_state_.emit_file_links() && !exercise.canonical_path.empty()) {
                out += "\x1b]8;;file://";
                out += exercise.canonical_path;
                out += "\x1b\\";
                writer.text(exercise.file_path);
                out += "\x1b]8;;\x1b\\";
            } else {
                writer.text(exercise.file_path);
            }
            writer.style(term::default_fg);
            writer.style(term::no_underline);
            writer.text(std::string(path_col_width_ - exercise.file_path.size(), ' '));

            next_ln(out);
            out += term::reset;
            ++n_displayed;
        }
        return n_displayed;
    }

    void hotkey(LineWriter& writer, std::string_view key) const {
        writer.style(term::yellow);
        writer.style(term::bold);
        writer.text(key);
        writer.style(term::reset);
    }

    void draw_footer(std::string& out) const {
        {
            std::string bar;
            // Line wrapping is disabled, so a character in the last column would be
            // overwritten by the next one.
            term::progress_bar(bar, app_state_.n_done(), static_cast<int>(app_state_.exercises().size()),
                               term_width_ - 1);
            out += bar;
            next_ln(out);
        }

        LineWriter writer(out, term_width_);
        if (!message.empty()) {
            writer.style(term::magenta);
            writer.text(message);
            writer.style(term::reset);
            next_ln(out);
            next_ln(out);
            return;
        }

        if (scroll_state_.selected()) {
            writer.text("↓/");
            hotkey(writer, "j");
            writer.text(" ↑/");
            hotkey(writer, "k");
            writer.text(" home/");
            hotkey(writer, "g");
            writer.text(" end/");
            hotkey(writer, "G");
            writer.text(" | ↵/");
            hotkey(writer, "c");
            writer.text("ontinue at | ");
            hotkey(writer, "r");
            writer.text("eset exercise");
            next_ln(out);

            LineWriter second(out, term_width_);
            hotkey(second, "s");
            second.text("earch | filter ");
            draw_filter_keys(second);
        } else {
            writer.text("filter ");
            draw_filter_keys(writer);
        }
        next_ln(out);
    }

    void draw_filter_keys(LineWriter& writer) const {
        auto active = [&](std::string_view key, std::string_view rest) {
            writer.style(term::underline);
            hotkey(writer, key);
            writer.style(term::magenta);
            writer.style(term::underline);
            writer.text(rest);
            writer.style(term::reset);
        };

        if (filter_ == Filter::Done) {
            active("d", "one");
        } else {
            hotkey(writer, "d");
            writer.text("one");
        }
        writer.text("/");
        if (filter_ == Filter::Pending) {
            active("p", "ending");
        } else {
            hotkey(writer, "p");
            writer.text("ending");
        }
        writer.text(" | ");
        hotkey(writer, "q");
        writer.text("uit list");
    }
};

void handle_list(AppState& app_state) {
    std::string clear = "\x1b[2J";
    term::write_stdout(clear);

    ListState list_state(app_state);
    list_state.draw();
    bool is_searching = false;

    while (true) {
        if (term::take_resize_event()) {
            list_state.set_term_size(term::size());
            list_state.draw();
        }

        term::Key key = term::read_key(-1);
        if (key.code == term::KeyCode::None) {
            continue;
        }

        list_state.message.clear();

        if (is_searching) {
            switch (key.code) {
            case term::KeyCode::Esc:
            case term::KeyCode::Enter:
                is_searching = false;
                list_state.search_query.clear();
                break;
            case term::KeyCode::Char:
                list_state.search_query += key.ch;
                list_state.apply_search_query();
                break;
            case term::KeyCode::Backspace:
                if (!list_state.search_query.empty()) {
                    list_state.search_query.pop_back();
                }
                list_state.apply_search_query();
                break;
            default:
                continue;
            }
            list_state.draw();
            continue;
        }

        switch (key.code) {
        case term::KeyCode::Down:
        case term::KeyCode::ScrollDown:
            list_state.select_next();
            break;
        case term::KeyCode::Up:
        case term::KeyCode::ScrollUp:
            list_state.select_previous();
            break;
        case term::KeyCode::Home:
            list_state.select_first();
            break;
        case term::KeyCode::End:
            list_state.select_last();
            break;
        case term::KeyCode::Enter:
            if (list_state.selected_to_current_exercise()) {
                return;
            }
            break;
        case term::KeyCode::Esc:
            // Redraw to remove the message.
            break;
        case term::KeyCode::Char:
            switch (key.ch) {
            case 'q':
            // Ctrl+C arrives as a character in raw mode.
            case '\x03':
                return;
            case 'j':
                list_state.select_next();
                break;
            case 'k':
                list_state.select_previous();
                break;
            case 'g':
                list_state.select_first();
                break;
            case 'G':
                list_state.select_last();
                break;
            case 'd':
                if (list_state.filter() == Filter::Done) {
                    list_state.set_filter(Filter::None);
                    list_state.message += "Disabled filter DONE";
                } else {
                    list_state.set_filter(Filter::Done);
                    list_state.message += "Enabled filter DONE │ Press d again to disable the filter";
                }
                break;
            case 'p':
                if (list_state.filter() == Filter::Pending) {
                    list_state.set_filter(Filter::None);
                    list_state.message += "Disabled filter PENDING";
                } else {
                    list_state.set_filter(Filter::Pending);
                    list_state.message += "Enabled filter PENDING │ Press p again to disable the filter";
                }
                break;
            case 'r':
                list_state.reset_selected();
                break;
            case 'c':
                if (list_state.selected_to_current_exercise()) {
                    return;
                }
                break;
            case 's':
            case '/':
                is_searching = true;
                list_state.apply_search_query();
                break;
            default:
                continue;
            }
            break;
        default:
            continue;
        }

        list_state.draw();
    }
}

} // namespace

void list(AppState& app_state) {
    term::InputMode input_mode(term::InputMode::Kind::Raw);
    term::FullScreen full_screen;
    handle_list(app_state);
}
