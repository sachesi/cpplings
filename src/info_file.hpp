#pragma once

#include <string>
#include <string_view>
#include <vector>

struct ExerciseInfo {
    std::string name;
    std::string dir;
    std::string hint;
    // Compile with -Werror and extra warnings.
    bool strict = false;
    // "thread" for ThreadSanitizer instead of the default sanitizers.
    std::string sanitizer;
    // The unmodified exercise already passes (e.g. intro1).
    bool skip_check_unsolved = false;

    std::string path() const { return "exercises/" + dir + "/" + name + ".cpp"; }
    std::string sol_path() const { return "solutions/" + dir + "/" + name + ".cpp"; }
};

struct InfoFile {
    int format_version = 0;
    std::string welcome_message;
    std::string final_message;
    std::vector<ExerciseInfo> exercises;

    // Parses the subset of TOML used by info.toml. Throws std::runtime_error.
    static InfoFile parse(std::string_view text);
};
