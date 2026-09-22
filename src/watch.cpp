#include "watch.hpp"

#include "app_state.hpp"
#include "list.hpp"
#include "term.hpp"

#include <sys/stat.h>

#include <chrono>
#include <format>
#include <thread>

namespace {

constexpr int poll_interval_ms = 200;

constexpr std::string_view quit_msg = "q\n\n"
                                      "We hope you're enjoying learning C++!\n"
                                      "If you want to continue working on the exercises at a later point, you can "
                                      "simply run `cpplings` again in this directory.\n";

struct FileStamp {
    long long mtime_ns = -1;
    long long size = -1;
    bool operator==(const FileStamp&) const = default;
};

FileStamp stamp(const std::string& path) {
    struct stat st{};
    if (::stat(path.c_str(), &st) != 0) {
        return {};
    }
#ifdef __APPLE__
    long long ns = static_cast<long long>(st.st_mtimespec.tv_sec) * 1'000'000'000 + st.st_mtimespec.tv_nsec;
#else
    long long ns = static_cast<long long>(st.st_mtim.tv_sec) * 1'000'000'000 + st.st_mtim.tv_nsec;
#endif
    return {ns, static_cast<long long>(st.st_size)};
}

enum class WatchExit { Shutdown, List };

class WatchState {
public:
    WatchState(AppState& app_state, bool manual_run)
        : app_state_(app_state), manual_run_(manual_run), term_width_(term::size().width) {}

    void run_current_exercise() {
        const Exercise& exercise = app_state_.current_exercise();
        term::write_stdout(std::format("\nChecking the exercise `{}`. Please wait…\n", exercise.name));

        app_state_.open_editor();
        show_hint_ = false;
        stamp_ = stamp(exercise.file_path);

        output_.clear();
        bool success = app_state_.run_current_exercise(&output_);
        output_ += '\n';

        solution_path_.reset();
        if (success) {
            done_ = true;
            solution_path_ = app_state_.current_solution_path();
        } else {
            done_ = false;
            app_state_.set_pending(app_state_.current_exercise_ind());
        }

        // Keys pressed while the exercise was running are ignored.
        term::discard_pending_input();
        render();
    }

    bool file_changed() {
        const std::string& path = app_state_.current_exercise().file_path;
        FileStamp current = stamp(path);
        if (current == stamp_) {
            return false;
        }
        // Give editors a moment to finish writing the file.
        do {
            stamp_ = current;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            current = stamp(path);
        } while (current != stamp_);
        return true;
    }

    void reset_exercise() {
        std::string out;
        term::clear(out);
        out += "Resetting will undo all your changes to the file ";
        out += app_state_.current_exercise().file_path;
        out += "\nReset (y/n)? ";
        term::write_stdout(out);

        while (true) {
            term::Key key = term::read_key(-1);
            if (key.code != term::KeyCode::Char) {
                continue;
            }
            if (key.ch == 'y' || key.ch == 'Y') {
                app_state_.reset_current_exercise();
                // Without manual runs, the file watcher reruns the exercise.
                if (manual_run_) {
                    run_current_exercise();
                }
                return;
            }
            if (key.ch == 'n' || key.ch == 'N') {
                render();
                return;
            }
        }
    }

    ExercisesProgress next_exercise() {
        if (done_) {
            return app_state_.done_current_exercise(true);
        }
        return ExercisesProgress::CurrentPending;
    }

    bool done() const { return done_; }

    void show_hint() {
        if (!show_hint_) {
            show_hint_ = true;
            render();
        }
    }

    ExercisesProgress check_all_exercises() {
        std::optional<std::size_t> first_pending = app_state_.check_all_exercises();
        if (!first_pending) {
            app_state_.render_final_message();
            return ExercisesProgress::AllDone;
        }
        if (app_state_.current_exercise().done) {
            app_state_.set_current_exercise_ind(*first_pending);
            return ExercisesProgress::NewPending;
        }
        return ExercisesProgress::CurrentPending;
    }

    void update_term_width() {
        int width = term::size().width;
        if (width != term_width_) {
            term_width_ = width;
            render();
        }
    }

    void render() {
        // Prevents the first line from being shifted if clearing isn't supported.
        std::string out = "\n";
        term::clear(out);
        out += output_;

        if (show_hint_) {
            out += std::format("{}{}{}Hint{}\n", term::bold, term::underline, term::cyan, term::reset);
            std::string_view hint = app_state_.current_exercise().hint;
            while (!hint.empty() && (hint.back() == '\n' || hint.back() == ' ')) {
                hint.remove_suffix(1);
            }
            out += hint;
            out += "\n\n";
        }

        if (done_) {
            out += std::format("{}{}Exercise done ✓{}\n", term::bold, term::green, term::reset);
            if (solution_path_) {
                solution_link_line(out, *solution_path_, app_state_.emit_file_links());
            }
            out += "When done experimenting, enter `n` to move on to the next exercise\n\n";
        }

        term::progress_bar(out, app_state_.n_done(), static_cast<int>(app_state_.exercises().size()),
                           term_width_);
        out += "\nCurrent exercise: ";
        app_state_.current_exercise().terminal_file_link(out, app_state_.emit_file_links());
        out += "\n\n";

        auto key = [&](char k, std::string_view postfix) {
            out += term::bold;
            out += k;
            out += term::reset;
            out += postfix;
        };
        if (done_) {
            out += std::format("{}n{}:{}next{} / ", term::bold, term::reset, term::underline, term::reset);
        }
        if (manual_run_) {
            key('r', ":run / ");
        }
        if (!show_hint_) {
            key('h', ":hint / ");
        }
        key('l', ":list / ");
        key('x', ":reset / ");
        key('q', ":quit ? ");
        term::write_stdout(out);
    }

private:
    AppState& app_state_;
    bool manual_run_;
    int term_width_;
    std::string output_;
    bool show_hint_ = false;
    bool done_ = false;
    std::optional<std::string> solution_path_;
    FileStamp stamp_;
};

WatchExit run_watch(AppState& app_state, bool manual_run) {
    WatchState state(app_state, manual_run);
    state.run_current_exercise();

    while (true) {
        if (term::take_resize_event()) {
            state.update_term_width();
        }

        term::Key key = term::read_key(poll_interval_ms);
        if (key.code != term::KeyCode::Char) {
            if (!manual_run && state.file_changed()) {
                state.run_current_exercise();
            }
            continue;
        }

        switch (key.ch) {
        case 'n':
            switch (state.next_exercise()) {
            case ExercisesProgress::AllDone:
                return WatchExit::Shutdown;
            case ExercisesProgress::NewPending:
                state.run_current_exercise();
                if (state.done()) {
                    // The exercise is done although it wasn't marked as such.
                    // Check all exercises to fix the state file.
                    switch (state.check_all_exercises()) {
                    case ExercisesProgress::AllDone:
                        return WatchExit::Shutdown;
                    case ExercisesProgress::NewPending:
                        state.run_current_exercise();
                        break;
                    case ExercisesProgress::CurrentPending:
                        state.render();
                        break;
                    }
                }
                break;
            case ExercisesProgress::CurrentPending:
                break;
            }
            break;
        case 'r':
            if (manual_run) {
                state.run_current_exercise();
            }
            break;
        case 'h':
            state.show_hint();
            break;
        case 'l':
            return WatchExit::List;
        case 'x':
            state.reset_exercise();
            break;
        case 'q':
            term::write_stdout(quit_msg);
            return WatchExit::Shutdown;
        default:
            break;
        }
    }
}

} // namespace

void watch(AppState& app_state, bool manual_run) {
    term::InputMode input_mode(term::InputMode::Kind::Cbreak);
    while (run_watch(app_state, manual_run) == WatchExit::List) {
        list(app_state);
    }
}
