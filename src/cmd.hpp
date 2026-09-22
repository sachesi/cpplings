#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <vector>

struct CmdResult {
    int exit_code = -1;
    // Nonzero if the process was killed by a signal.
    int signal = 0;
    bool timed_out = false;
    bool output_truncated = false;

    bool success() const { return exit_code == 0 && signal == 0 && !timed_out; }
};

// Runs `argv` with stdin connected to /dev/null. Stdout and stderr are merged and
// appended to `output` if it isn't null. Throws std::system_error if the program
// can't be started.
CmdResult run_cmd(const std::vector<std::string>& argv, std::string* output,
                  std::optional<std::chrono::milliseconds> timeout = std::nullopt);
