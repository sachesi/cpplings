#include "app_state.hpp"
#include "dev.hpp"
#include "embedded.hpp"
#include "info_file.hpp"
#include "init.hpp"
#include "term.hpp"
#include "toolchain.hpp"
#include "watch.hpp"

#include <sys/resource.h>

#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

constexpr int current_format_version = 1;

constexpr std::string_view logo = R"(
       Welcome to...
                   _ _
   ___ _ __  _ __ | (_)_ __   __ _ ___
  / __| '_ \| '_ \| | | '_ \ / _` / __|
 | (__| |_) | |_) | | | | | | (_| \__ \
  \___| .__/| .__/|_|_|_| |_|\__, |___/
      |_|   |_|              |___/
)";

constexpr std::string_view pre_init_msg =
    "\nThe `exercises/` directory couldn't be found in the current directory.\n"
    "If you are just starting with cpplings, run the command `cpplings init` to initialize it.";

constexpr std::string_view usage = R"(cpplings is a collection of small exercises to get you used to writing and reading C++ code

Usage: cpplings [OPTIONS] [COMMAND]

Commands:
  init       Initialize the cpplings exercises
  run        Run a single exercise. Runs the next pending exercise if the exercise name is not specified
  check-all  Check all the exercises, marking them as done or pending accordingly
  reset      Reset a single exercise
  hint       Show a hint. Shows the hint of the next pending exercise if the exercise name is not specified
  dev        Commands for developing cpplings exercises (`dev check`)
  help       Print this message

Options:
      --no-editor        Disable automatic opening of the current file in VS Code
      --edit-cmd <CMD>   Open the current exercise by running `CMD EXERCISE_PATH`.
                         The command is not allowed to block (e.g. `vim`)
      --manual-run       Manually run the current exercise using `r` in the watch mode.
                         Only use this if cpplings fails to detect exercise file changes
  -h, --help             Print help
  -V, --version          Print version

Environment:
  CXX                    The C++ compiler to use (default: c++)
)";

struct Args {
    std::string command;
    std::optional<std::string> name;
    bool no_editor = false;
    bool manual_run = false;
    std::optional<std::string> edit_cmd;
};

[[noreturn]] void usage_error(const std::string& message) {
    std::cerr << "error: " << message << "\n\nFor more information, try '--help'.\n";
    std::exit(2);
}

Args parse_args(int argc, char** argv) {
    Args args;
    std::vector<std::string> positional;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            std::cout << usage;
            std::exit(0);
        } else if (arg == "-V" || arg == "--version") {
            std::cout << "cpplings " << CPPLINGS_VERSION << '\n';
            std::exit(0);
        } else if (arg == "--no-editor") {
            args.no_editor = true;
        } else if (arg == "--manual-run") {
            args.manual_run = true;
        } else if (arg == "--edit-cmd") {
            if (++i >= argc) {
                usage_error("a value is required for '--edit-cmd <CMD>'");
            }
            args.edit_cmd = argv[i];
        } else if (arg.starts_with("--edit-cmd=")) {
            args.edit_cmd = arg.substr(std::string_view("--edit-cmd=").size());
        } else if (arg.starts_with("-")) {
            usage_error(std::format("unexpected argument '{}' found", arg));
        } else {
            positional.push_back(arg);
        }
    }

    if (positional.empty()) {
        return args;
    }
    args.command = positional[0];
    const std::string& cmd = args.command;
    if (cmd == "help") {
        std::cout << usage;
        std::exit(0);
    }
    if (cmd == "init" || cmd == "check-all") {
        if (positional.size() > 1) {
            usage_error(std::format("unexpected argument '{}' found", positional[1]));
        }
    } else if (cmd == "run" || cmd == "hint") {
        if (positional.size() > 2) {
            usage_error(std::format("unexpected argument '{}' found", positional[2]));
        }
        if (positional.size() == 2) {
            args.name = positional[1];
        }
    } else if (cmd == "reset") {
        if (positional.size() != 2) {
            usage_error("`reset` requires the name of the exercise");
        }
        args.name = positional[1];
    } else if (cmd == "dev") {
        if (positional.size() != 2 || positional[1] != "check") {
            usage_error("the only dev command is `dev check`");
        }
    } else {
        usage_error(std::format("unrecognized subcommand '{}'", cmd));
    }
    return args;
}

std::vector<std::string> split_whitespace(const std::string& s) {
    std::istringstream in(s);
    std::vector<std::string> parts;
    for (std::string part; in >> part;) {
        parts.push_back(part);
    }
    return parts;
}

// Settings for the exercise processes, which inherit the environment.
void configure_exercise_environment() {
    rlimit no_core{0, 0};
    ::setrlimit(RLIMIT_CORE, &no_core);
    // Freed memory is overwritten, so reading it gives garbage instead of the old value.
    ::setenv("MALLOC_PERTURB_", "165", 0);
    ::setenv("ASAN_OPTIONS", "detect_stack_use_after_return=1", 0);
    ::setenv("UBSAN_OPTIONS", "print_stacktrace=1", 0);
}

int run(AppState& app_state) {
    std::string output;
    bool success = app_state.run_current_exercise(&output);

    std::string out = output;
    if (!success) {
        app_state.set_pending(app_state.current_exercise_ind());
        out += "Ran ";
        app_state.current_exercise().terminal_file_link(out, app_state.emit_file_links());
        out += " with errors\n";
        term::write_stdout(out);
        return 1;
    }

    out += std::format("{}✓ Successfully ran {}{}\n", term::green, app_state.current_exercise().file_path,
                       term::reset);
    if (std::optional<std::string> solution = app_state.current_solution_path()) {
        out += '\n';
        solution_link_line(out, *solution, app_state.emit_file_links());
        out += '\n';
    }
    term::write_stdout(out);

    if (app_state.done_current_exercise(false) != ExercisesProgress::AllDone) {
        out = "Next exercise: ";
        app_state.current_exercise().terminal_file_link(out, app_state.emit_file_links());
        out += '\n';
        term::write_stdout(out);
    }
    return 0;
}

int check_all(AppState& app_state) {
    std::optional<std::size_t> first_pending = app_state.check_all_exercises();
    if (!first_pending) {
        app_state.render_final_message();
        return 0;
    }
    if (app_state.current_exercise().done) {
        app_state.set_current_exercise_ind(*first_pending);
    }

    std::string out = "\n\n";
    if (app_state.n_pending() == 1) {
        out += "One exercise pending: ";
    } else {
        out += std::format("{}/{} exercises pending. The first: ", app_state.n_pending(),
                           app_state.exercises().size());
    }
    app_state.current_exercise().terminal_file_link(out, app_state.emit_file_links());
    out += '\n';
    term::write_stdout(out);
    return 1;
}

int real_main(int argc, char** argv) {
    Args args = parse_args(argc, argv);

    if (args.command == "init") {
        init();
        return 0;
    }
    if (args.command == "dev") {
        return dev_check();
    }

    if (!fs::is_directory("exercises")) {
        std::cout << logo << pre_init_msg << '\n';
        return 1;
    }

    InfoFile info = InfoFile::parse(*embedded_file("info.toml"));
    if (info.format_version > current_format_version) {
        throw std::runtime_error(
            "The format version specified in the `info.toml` file is higher than the last one supported.\n"
            "You need to upgrade cpplings.");
    }

    Toolchain toolchain = Toolchain::detect();
    write_compile_commands(toolchain, info.exercises);
    configure_exercise_environment();

    const char* term_program = std::getenv("TERM_PROGRAM");
    bool vs_code_term = term_program != nullptr && std::string_view(term_program) == "vscode";
    std::vector<std::string> edit_cmd;
    if (!args.no_editor) {
        if (vs_code_term) {
            edit_cmd = {"code"};
        } else if (args.edit_cmd) {
            edit_cmd = split_whitespace(*args.edit_cmd);
        }
    }

    AppState app_state(std::move(info.exercises), std::move(info.final_message), std::move(toolchain),
                       std::move(edit_cmd), !vs_code_term);

    std::string_view welcome = info.welcome_message;
    while (!welcome.empty() && (welcome.front() == '\n' || welcome.back() == '\n')) {
        welcome = welcome.front() == '\n' ? welcome.substr(1) : welcome.substr(0, welcome.size() - 1);
    }
    if (!welcome.empty() && app_state.state_file_status() == StateFileStatus::NotRead) {
        std::string out;
        term::clear(out);
        out += welcome;
        out += "\n\nPress ENTER to continue ";
        term::write_stdout(out);
        term::press_enter_prompt();
        out.clear();
        term::clear(out);
        term::write_stdout(out);
    }

    if (args.command.empty()) {
        if (!term::stdout_is_terminal()) {
            throw std::runtime_error("Unsupported or missing terminal/TTY");
        }
        term::install_signal_handlers();
        watch(app_state, args.manual_run);
        return 0;
    }

    if (args.command == "run") {
        if (args.name) {
            app_state.set_current_exercise_by_name(*args.name);
        }
        return run(app_state);
    }
    if (args.command == "check-all") {
        return check_all(app_state);
    }
    if (args.command == "reset") {
        app_state.set_current_exercise_by_name(*args.name);
        app_state.reset_current_exercise();
        std::string out = "The exercise ";
        app_state.current_exercise().terminal_file_link(out, app_state.emit_file_links());
        out += " has been reset\n";
        term::write_stdout(out);
        return 0;
    }
    if (args.command == "hint") {
        if (args.name) {
            app_state.set_current_exercise_by_name(*args.name);
        }
        std::string out = "Current exercise: ";
        app_state.current_exercise().terminal_file_link(out, app_state.emit_file_links());
        out += "\n\nHint:\n";
        std::string_view hint = app_state.current_exercise().hint;
        while (!hint.empty() && (hint.back() == '\n' || hint.back() == ' ')) {
            hint.remove_suffix(1);
        }
        out += hint;
        out += '\n';
        term::write_stdout(out);
        return 0;
    }
    return 0;
}

} // namespace

int main(int argc, char** argv) {
    try {
        return real_main(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
