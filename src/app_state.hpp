#pragma once

#include "exercise.hpp"
#include "info_file.hpp"
#include "toolchain.hpp"

#include <optional>
#include <string>
#include <vector>

enum class ExercisesProgress {
    // All exercises are done.
    AllDone,
    // A new exercise is now pending.
    NewPending,
    // The current exercise is still pending.
    CurrentPending,
};

enum class StateFileStatus { Read, NotRead };

class AppState {
public:
    AppState(std::vector<ExerciseInfo> infos, std::string final_message, Toolchain toolchain,
             std::vector<std::string> edit_cmd, bool emit_file_links);

    StateFileStatus state_file_status() const { return state_file_status_; }
    const std::vector<Exercise>& exercises() const { return exercises_; }
    std::size_t current_exercise_ind() const { return current_; }
    const Exercise& current_exercise() const { return exercises_[current_]; }
    int n_done() const { return n_done_; }
    int n_pending() const { return static_cast<int>(exercises_.size()) - n_done_; }
    bool emit_file_links() const { return emit_file_links_; }

    void set_current_exercise_ind(std::size_t ind);
    // Throws std::runtime_error if there is no such exercise.
    void set_current_exercise_by_name(std::string_view name);
    void set_pending(std::size_t ind);
    void reset_current_exercise();
    // Returns the name of the reset exercise.
    const std::string& reset_exercise_by_ind(std::size_t ind);

    bool run_current_exercise(std::string* output) const;
    // Writes the solution of the current exercise to `solutions/` and returns its path.
    std::optional<std::string> current_solution_path() const;

    // Returns the index of the first pending exercise, if any.
    std::optional<std::size_t> check_all_exercises();
    // Marks the current exercise as done and moves on to the next pending one. If
    // every exercise is marked as done, all of them are checked again first.
    ExercisesProgress done_current_exercise(bool clear_before_final_check);
    void render_final_message() const;

    // Opens the current exercise with `--edit-cmd` if it wasn't opened before.
    void open_editor();

private:
    std::vector<Exercise> exercises_;
    std::size_t current_ = 0;
    int n_done_ = 0;
    std::string final_message_;
    Toolchain toolchain_;
    std::vector<std::string> edit_cmd_;
    std::optional<std::size_t> opened_in_editor_;
    bool emit_file_links_;
    StateFileStatus state_file_status_ = StateFileStatus::NotRead;

    void write_state_file() const;
    bool set_status(std::size_t ind, bool done);
    std::optional<std::size_t> next_pending_exercise_ind() const;
    void reset(std::size_t ind);
};
