#include "app_state.hpp"

#include "cmd.hpp"
#include "embedded.hpp"
#include "term.hpp"

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <deque>
#include <filesystem>
#include <format>
#include <fstream>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <unordered_set>

namespace fs = std::filesystem;

namespace {

constexpr const char* state_file_name = ".cpplings-state.txt";
constexpr std::string_view state_file_header = "DON'T EDIT THIS FILE!\n\n";

constexpr std::string_view finish_line = R"(+----------------------------------------------------+
|          You made it to the finish line!           |
+--------------------------  ------------------------+
                          \/)"
                                         "\x1b[34m\n"
                                         R"(                  _________________
                 |  _____________  |
                 | |             | |
                 | |  > C++23_   | |
                 | |             | |
                 | |_____________| |
                 |_________________|
                        |___|
               _________|___|_________
              | [_][_][_][_][_][_][_] |
              |_______________________|
)"
                                         "\x1b[0m\n";

void write_file(const std::string& path, std::string_view content) {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out << content;
    if (!out) {
        throw std::runtime_error(std::format("Failed to write the file {}", path));
    }
}

class CheckProgressVisualizer {
public:
    explicit CheckProgressVisualizer(std::size_t total) : total_(total) {
        std::string out;
        term::clear(out);
        out += "Checking all exercises…\n";
        out += std::format("Progress: 0/{}", total_);
        term::write_stdout(out);
    }

    ~CheckProgressVisualizer() { term::write_stdout("\n\n"); }

    void checked(const std::string& name, bool done) {
        ++counter_;
        std::string out = done ? std::format("{}\r   DONE ", term::green) : std::format("{}\rPENDING ", term::red);
        out += term::reset;
        out += name;
        out += "\x1b[K\n";
        out += std::format("\rProgress: {}/{}", counter_, total_);
        term::write_stdout(out);
    }

private:
    std::size_t total_;
    std::size_t counter_ = 0;
};

} // namespace

AppState::AppState(std::vector<ExerciseInfo> infos, std::string final_message, Toolchain toolchain,
                   std::vector<std::string> edit_cmd, bool emit_file_links)
    : final_message_(std::move(final_message)),
      toolchain_(std::move(toolchain)),
      edit_cmd_(std::move(edit_cmd)),
      emit_file_links_(emit_file_links) {
    exercises_.reserve(infos.size());
    for (ExerciseInfo& info : infos) {
        Exercise exercise;
        static_cast<ExerciseInfo&>(exercise) = std::move(info);
        exercise.file_path = exercise.path();
        exercise.canonical_path = term::canonicalize(exercise.file_path);
        exercises_.push_back(std::move(exercise));
    }

    // Format: header comment, empty line, current exercise, empty line, done exercises.
    std::ifstream in(state_file_name);
    std::stringstream content;
    content << in.rdbuf();
    std::vector<std::string> lines;
    for (std::string line; std::getline(content, line, '\n');) {
        lines.push_back(line);
    }
    // The current exercise's line must be terminated even if nothing is done yet.
    bool terminated = !content.str().empty() && content.str().back() == '\n';
    if (lines.size() < 3 || lines[2].empty() || (lines.size() == 3 && !terminated)) {
        return;
    }

    std::unordered_set<std::string> done_names;
    for (std::size_t i = 4; i < lines.size() && !lines[i].empty(); ++i) {
        done_names.insert(lines[i]);
    }
    for (std::size_t i = 0; i < exercises_.size(); ++i) {
        if (done_names.contains(exercises_[i].name)) {
            exercises_[i].done = true;
            ++n_done_;
        }
        if (exercises_[i].name == lines[2]) {
            current_ = i;
        }
    }
    state_file_status_ = StateFileStatus::Read;
}

void AppState::write_state_file() const {
    std::string content(state_file_header);
    content += exercises_[current_].name;
    content += '\n';
    for (const Exercise& exercise : exercises_) {
        if (exercise.done) {
            content += '\n';
            content += exercise.name;
        }
    }
    write_file(state_file_name, content);
}

void AppState::set_current_exercise_ind(std::size_t ind) {
    if (ind == current_) {
        return;
    }
    if (ind >= exercises_.size()) {
        throw std::out_of_range("The exercise index is higher than the number of exercises");
    }
    current_ = ind;
    write_state_file();
}

void AppState::set_current_exercise_by_name(std::string_view name) {
    auto it = std::ranges::find(exercises_, name, &Exercise::name);
    if (it == exercises_.end()) {
        throw std::runtime_error(std::format("No exercise found for '{}'!", name));
    }
    current_ = static_cast<std::size_t>(it - exercises_.begin());
    write_state_file();
}

bool AppState::set_status(std::size_t ind, bool done) {
    Exercise& exercise = exercises_.at(ind);
    if (exercise.done == done) {
        return false;
    }
    exercise.done = done;
    n_done_ += done ? 1 : -1;
    return true;
}

void AppState::set_pending(std::size_t ind) {
    if (set_status(ind, false)) {
        write_state_file();
    }
}

void AppState::reset(std::size_t ind) {
    const Exercise& exercise = exercises_[ind];
    std::optional<std::string_view> original = embedded_file(exercise.file_path);
    if (!original) {
        throw std::runtime_error(std::format("No original version of {} is available", exercise.file_path));
    }
    fs::create_directories(fs::path(exercise.file_path).parent_path());
    write_file(exercise.file_path, *original);
}

void AppState::reset_current_exercise() {
    set_pending(current_);
    reset(current_);
}

const std::string& AppState::reset_exercise_by_ind(std::size_t ind) {
    if (ind >= exercises_.size()) {
        throw std::out_of_range("The exercise index is higher than the number of exercises");
    }
    set_pending(ind);
    reset(ind);
    return exercises_[ind].name;
}

std::optional<std::size_t> AppState::next_pending_exercise_ind() const {
    for (std::size_t i = current_ + 1; i < exercises_.size(); ++i) {
        if (!exercises_[i].done) {
            return i;
        }
    }
    for (std::size_t i = 0; i < current_; ++i) {
        if (!exercises_[i].done) {
            return i;
        }
    }
    return std::nullopt;
}

bool AppState::run_current_exercise(std::string* output) const {
    return run_exercise(current_exercise(), toolchain_, false, output);
}

std::optional<std::string> AppState::current_solution_path() const {
    const Exercise& exercise = current_exercise();
    std::string path = exercise.sol_path();
    std::optional<std::string_view> solution = embedded_file(path);
    if (!solution) {
        return std::nullopt;
    }
    fs::create_directories(fs::path(path).parent_path());
    write_file(path, *solution);
    return path;
}

std::optional<std::size_t> AppState::check_all_exercises() {
    term::write_stdout(term::hide_cursor);
    std::vector<std::optional<bool>> results(exercises_.size());
    {
        CheckProgressVisualizer visualizer(exercises_.size());

        std::atomic<std::size_t> next_ind = 0;
        std::mutex mutex;
        std::condition_variable cv;
        std::deque<std::pair<std::size_t, bool>> finished;
        std::size_t n_threads = std::max(1u, std::thread::hardware_concurrency());

        std::vector<std::jthread> workers;
        for (std::size_t t = 0; t < n_threads; ++t) {
            workers.emplace_back([&] {
                while (true) {
                    std::size_t ind = next_ind.fetch_add(1);
                    if (ind >= exercises_.size()) {
                        return;
                    }
                    bool success = false;
                    try {
                        success = run_exercise(exercises_[ind], toolchain_, false, nullptr);
                    } catch (const std::exception&) {
                    }
                    std::lock_guard lock(mutex);
                    finished.emplace_back(ind, success);
                    cv.notify_one();
                }
            });
        }

        for (std::size_t received = 0; received < exercises_.size(); ++received) {
            std::unique_lock lock(mutex);
            cv.wait(lock, [&] { return !finished.empty(); });
            auto [ind, success] = finished.front();
            finished.pop_front();
            lock.unlock();
            results[ind] = success;
            visualizer.checked(exercises_[ind].name, success);
        }
    }
    term::write_stdout(term::show_cursor);

    std::optional<std::size_t> first_pending;
    for (std::size_t i = 0; i < results.size(); ++i) {
        bool done = results[i].value_or(false);
        set_status(i, done);
        if (!done && !first_pending) {
            first_pending = i;
        }
    }
    write_state_file();
    return first_pending;
}

ExercisesProgress AppState::done_current_exercise(bool clear_before_final_check) {
    if (!exercises_[current_].done) {
        exercises_[current_].done = true;
        ++n_done_;
    }

    if (std::optional<std::size_t> next = next_pending_exercise_ind()) {
        set_current_exercise_ind(*next);
        return ExercisesProgress::NewPending;
    }

    if (clear_before_final_check) {
        std::string out;
        term::clear(out);
        term::write_stdout(out);
    } else {
        term::write_stdout("\n");
    }

    if (std::optional<std::size_t> first_pending = check_all_exercises()) {
        set_current_exercise_ind(*first_pending);
        return ExercisesProgress::NewPending;
    }

    render_final_message();
    return ExercisesProgress::AllDone;
}

void AppState::render_final_message() const {
    std::string out;
    term::clear(out);
    out += finish_line;
    std::string_view message = final_message_;
    while (!message.empty() && (message.front() == '\n' || message.back() == '\n')) {
        message = message.front() == '\n' ? message.substr(1) : message.substr(0, message.size() - 1);
    }
    if (!message.empty()) {
        out += message;
        out += '\n';
    }
    term::write_stdout(out);
}

void AppState::open_editor() {
    if (edit_cmd_.empty() || opened_in_editor_ == current_) {
        return;
    }
    opened_in_editor_ = current_;

    std::vector<std::string> cmd = edit_cmd_;
    cmd.push_back(current_exercise().file_path);
    CmdResult result = run_cmd(cmd, nullptr, std::chrono::seconds(5));
    if (!result.success()) {
        throw std::runtime_error(std::format("Failed to open {} with `{}`", current_exercise().file_path, cmd[0]));
    }
}
