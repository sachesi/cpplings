#include "init.hpp"

#include "cmd.hpp"
#include "embedded.hpp"
#include "info_file.hpp"
#include "term.hpp"
#include "toolchain.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace {

constexpr std::string_view init_solution_file = R"(// DON'T EDIT THIS SOLUTION FILE!
// It will be automatically filled after you finish the exercise.

int main() {}
)";

constexpr std::string_view gitignore = ".cpplings/\n"
                                       "compile_commands.json\n"
                                       ".cache/\n";

constexpr std::string_view readme = "# cpplings\n"
                                    "\n"
                                    "This is your space to solve cpplings exercises.\n"
                                    "Simply run `cpplings` in this directory to get started!\n";

constexpr std::string_view vs_code_extensions_json = R"({"recommendations":["llvm-vs-code-extensions.vscode-clangd"]})";

constexpr std::string_view in_initialized_dir_err =
    "It looks like cpplings is already initialized in this directory.\n"
    "\n"
    "If you already initialized cpplings, run the command `cpplings` for instructions on getting started with "
    "the exercises.\n"
    "Otherwise, please run `cpplings init` again in a different directory.";

constexpr std::string_view dir_already_exists_err =
    "A directory with the name `cpplings` already exists in the current directory.\n"
    "You probably already initialized cpplings.\n"
    "Run `cd cpplings`\n"
    "Then run `cpplings` again";

constexpr std::string_view post_init_msg = "Run `cd cpplings` to go into the generated directory.\n"
                                           "Then run `cpplings` to get started.\n";

void write_file(const fs::path& path, std::string_view content) {
    if (path.has_parent_path()) {
        fs::create_directories(path.parent_path());
    }
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out << content;
    if (!out) {
        throw std::runtime_error(std::format("Failed to create the file {}", path.string()));
    }
}

std::string json_string(std::string_view s) {
    std::string out = "\"";
    for (char c : s) {
        if (c == '"' || c == '\\') {
            out += '\\';
        }
        out += c;
    }
    out += '"';
    return out;
}

bool inside_vcs_repository() {
    for (fs::path dir = fs::current_path();; dir = dir.parent_path()) {
        if (fs::exists(dir / ".git") || fs::exists(dir / ".jj")) {
            return true;
        }
        if (dir == dir.parent_path()) {
            return false;
        }
    }
}

} // namespace

void write_compile_commands(const Toolchain& toolchain, const std::vector<ExerciseInfo>& exercises) {
    std::string root = fs::current_path().string();
    std::string json = "[\n";
    bool first = true;
    for (const ExerciseInfo& exercise : exercises) {
        std::vector<std::string> args = {toolchain.cxx()};
        std::vector<std::string> flags = toolchain.flags(exercise);
        args.insert(args.end(), flags.begin(), flags.end());

        for (const std::string& file : {exercise.path(), exercise.sol_path()}) {
            json += first ? "" : ",\n";
            first = false;
            json += std::format("  {{\n    \"directory\": {},\n    \"file\": {},\n    \"arguments\": [",
                                json_string(root), json_string(root + "/" + file));
            for (const std::string& arg : args) {
                json += json_string(arg);
                json += ", ";
            }
            json += std::format("\"-c\", {}]\n  }}", json_string(file));
        }
    }
    json += "\n]\n";

    std::ifstream in("compile_commands.json");
    std::stringstream existing;
    existing << in.rdbuf();
    if (existing.str() != json) {
        write_file("compile_commands.json", json);
    }
}

void init() {
    if (fs::exists("cpplings")) {
        throw std::runtime_error(std::string(dir_already_exists_err));
    }
    if (fs::is_directory("exercises") && fs::is_directory("solutions")) {
        throw std::runtime_error(std::string(in_initialized_dir_err));
    }

    term::write_stdout("This command will create the directory `cpplings/` which will contain the exercises.\n"
                       "Press ENTER to continue ");
    term::press_enter_prompt();

    bool init_git = !inside_vcs_repository();

    fs::create_directory("cpplings");
    fs::current_path("cpplings");

    InfoFile info = InfoFile::parse(*embedded_file("info.toml"));

    for (std::size_t i = 0; i < embedded_files_count; ++i) {
        const EmbeddedFile& file = embedded_files[i];
        if (file.path.starts_with("exercises/") || file.path.starts_with("include/")) {
            write_file(std::string(file.path), file.content);
        }
    }

    write_file("solutions/README.md", *embedded_file("solutions/README.md"));
    for (const ExerciseInfo& exercise : info.exercises) {
        write_file(exercise.sol_path(), init_solution_file);
    }

    write_file(".gitignore", gitignore);
    write_file("README.md", readme);
    write_file(".vscode/extensions.json", vs_code_extensions_json);

    try {
        write_compile_commands(Toolchain::detect(), info.exercises);
    } catch (const std::exception&) {
        // Written again on every start once a compiler is available.
    }

    if (init_git) {
        try {
            run_cmd({"git", "init"}, nullptr);
        } catch (const std::exception&) {
            // Git is optional.
        }
    }

    std::string out;
    out += term::green;
    out += "Initialization done ✓";
    out += term::reset;
    out += "\n\n";
    out += term::bold;
    out += post_init_msg;
    out += term::reset;
    term::write_stdout(out);
}
