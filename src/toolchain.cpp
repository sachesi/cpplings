#include "toolchain.hpp"

#include "cmd.hpp"
#include "info_file.hpp"

#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <system_error>

namespace fs = std::filesystem;

namespace {

constexpr const char* cache_file = ".cpplings/toolchain";

// Running the probe matters: LeakSanitizer links fine but fails at exit where
// ptrace isn't permitted, e.g. in some containers.
bool can_use(const std::string& cxx, const std::string& sanitizer) {
    fs::path source = fs::path(build_dir) / ".probe.cpp";
    fs::path binary = fs::path(build_dir) / ".probe";
    std::ofstream(source) << "int main() {}\n";
    bool usable = run_cmd({cxx, "-fsanitize=" + sanitizer, source.string(), "-o", binary.string()}, nullptr).success() &&
                  run_cmd({binary.string()}, nullptr, std::chrono::seconds(10)).success();
    std::error_code ec;
    fs::remove(source, ec);
    fs::remove(binary, ec);
    return usable;
}

} // namespace

Toolchain Toolchain::detect() {
    Toolchain tc;
    const char* env_cxx = std::getenv("CXX");
    tc.cxx_ = env_cxx != nullptr && *env_cxx != '\0' ? env_cxx : "c++";

    std::string version;
    try {
        CmdResult result = run_cmd({tc.cxx_, "--version"}, &version);
        if (!result.success()) {
            throw std::runtime_error("");
        }
    } catch (const std::exception&) {
        throw std::runtime_error(std::format(
            "Failed to run the C++ compiler `{0} --version`.\n"
            "Did you install a C++ compiler (GCC or Clang)?\n"
            "cpplings uses `c++` by default; set the CXX environment variable to use another one.",
            tc.cxx_));
    }
    version = version.substr(0, version.find('\n'));

    fs::create_directories(build_dir);
    std::string key = tc.cxx_ + '\n' + version + '\n';
    {
        std::ifstream in(cache_file);
        std::stringstream cached;
        cached << in.rdbuf();
        std::string content = cached.str();
        if (content.starts_with(key)) {
            tc.has_asan_ = content.find("asan=1") != std::string::npos;
            tc.has_tsan_ = content.find("tsan=1") != std::string::npos;
            return tc;
        }
    }

    tc.has_asan_ = can_use(tc.cxx_, "address,undefined");
    tc.has_tsan_ = can_use(tc.cxx_, "thread");
    std::ofstream(cache_file) << key << "asan=" << tc.has_asan_ << "\ntsan=" << tc.has_tsan_ << '\n';
    return tc;
}

std::vector<std::string> Toolchain::flags(const ExerciseInfo& exercise) const {
    std::vector<std::string> flags = {
        "-std=c++23",
        "-g",
        "-O0",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-pthread",
        "-Iinclude",
        // Checked iterators and bounds checks in the standard library.
        "-D_GLIBCXX_DEBUG",
        "-D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG",
    };

    if (exercise.strict) {
        flags.insert(flags.end(), {"-Werror", "-Wconversion", "-Wshadow"});
    }

    if (exercise.sanitizer == "thread" && has_tsan_) {
        flags.emplace_back("-fsanitize=thread");
    } else if (exercise.sanitizer != "thread" && has_asan_) {
        flags.insert(flags.end(),
                     {"-fsanitize=address,undefined", "-fno-sanitize-recover=all", "-fno-omit-frame-pointer"});
    } else {
        // Trapping on undefined behavior needs no runtime library.
        flags.insert(flags.end(), {"-fsanitize=undefined", "-fsanitize-trap=all"});
    }
    return flags;
}

std::vector<std::string> Toolchain::compile_command(const ExerciseInfo& exercise, const std::string& source,
                                                    const std::string& binary) const {
    std::vector<std::string> cmd = {cxx_, "-fdiagnostics-color=always"};
    std::vector<std::string> exercise_flags = flags(exercise);
    cmd.insert(cmd.end(), exercise_flags.begin(), exercise_flags.end());
    cmd.insert(cmd.end(), {source, "-o", binary});
    return cmd;
}
