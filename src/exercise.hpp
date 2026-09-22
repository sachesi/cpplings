#pragma once

#include "info_file.hpp"

#include <string>

class Toolchain;

struct Exercise : ExerciseInfo {
    std::string file_path;
    // Empty if the file doesn't exist; used for terminal hyperlinks.
    std::string canonical_path;
    bool done = false;

    void terminal_file_link(std::string& out, bool emit_file_links) const;
};

// Compiles and runs the exercise (or its solution). Compiler diagnostics and the
// program's output are written to `output` if it isn't null.
bool run_exercise(const ExerciseInfo& exercise, const Toolchain& toolchain, bool solution, std::string* output);

void solution_link_line(std::string& out, const std::string& solution_path, bool emit_file_links);
