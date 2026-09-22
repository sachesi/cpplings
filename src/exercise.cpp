#include "exercise.hpp"

#include "cmd.hpp"
#include "term.hpp"
#include "toolchain.hpp"

#include <csignal>
#include <cstring>
#include <format>

namespace {

constexpr std::chrono::seconds run_timeout{10};

std::string signal_description(int sig) {
    switch (sig) {
    case SIGSEGV:
        return "SIGSEGV: invalid memory access";
    case SIGABRT:
        return "SIGABRT: the program aborted";
    case SIGILL:
        return "SIGILL: undefined behavior was detected";
    case SIGFPE:
        return "SIGFPE: arithmetic error such as a division by zero";
    default:
        return std::format("signal {}: {}", sig, strsignal(sig));
    }
}

void append_failure(std::string& output, std::string_view message) {
    output += term::bold;
    output += term::red;
    output += message;
    output += term::reset;
    output += '\n';
}

} // namespace

void Exercise::terminal_file_link(std::string& out, bool emit_file_links) const {
    out += term::blue;
    out += term::underline;
    term::file_link(out, file_path, emit_file_links ? canonical_path : "");
    out += term::default_fg;
    out += term::no_underline;
}

bool run_exercise(const ExerciseInfo& exercise, const Toolchain& toolchain, bool solution, std::string* output) {
    std::string source = solution ? exercise.sol_path() : exercise.path();
    std::string binary = std::string(build_dir) + "/" + exercise.name + (solution ? "_sol" : "");

    CmdResult compiled = run_cmd(toolchain.compile_command(exercise, source, binary), output);
    if (!compiled.success()) {
        return false;
    }

    if (output != nullptr) {
        if (!output->empty()) {
            *output += '\n';
        }
        *output += term::underline;
        *output += "Output";
        *output += term::reset;
        *output += '\n';
    }

    CmdResult ran = run_cmd({binary}, output, run_timeout);
    if (output == nullptr || ran.success()) {
        return ran.success();
    }

    if (!output->empty() && output->back() != '\n') {
        *output += '\n';
    }
    if (ran.output_truncated) {
        append_failure(*output, "The output was cut off after 1 MiB");
    }
    if (ran.timed_out) {
        append_failure(*output, std::format("The exercise was stopped after running for {} seconds",
                                            run_timeout.count()));
    } else if (ran.signal != 0) {
        append_failure(*output, std::format("The exercise crashed ({})", signal_description(ran.signal)));
    } else {
        append_failure(*output, "The exercise didn't run successfully (nonzero exit code)");
    }
    return false;
}

void solution_link_line(std::string& out, const std::string& solution_path, bool emit_file_links) {
    out += term::bold;
    out += "Solution";
    out += term::reset;
    out += " for comparison: ";
    out += term::cyan;
    out += term::underline;
    term::file_link(out, solution_path, emit_file_links ? term::canonicalize(solution_path) : "");
    out += term::default_fg;
    out += term::no_underline;
    out += '\n';
}
