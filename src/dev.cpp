#include "dev.hpp"

#include "exercise.hpp"
#include "info_file.hpp"
#include "term.hpp"
#include "toolchain.hpp"

#include <algorithm>
#include <atomic>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <mutex>
#include <set>
#include <sstream>
#include <thread>

namespace fs = std::filesystem;

namespace {

struct Problem {
    std::string message;
    std::string output;
};

std::string read_file(const fs::path& path) {
    std::ifstream in(path, std::ios::binary);
    std::stringstream content;
    content << in.rdbuf();
    return content.str();
}

std::vector<std::string> check_files(const InfoFile& info) {
    std::vector<std::string> problems;
    std::set<std::string> listed;
    std::set<std::string> dirs;
    for (const ExerciseInfo& exercise : info.exercises) {
        listed.insert(exercise.path());
        dirs.insert(exercise.dir);
        if (!fs::is_regular_file(exercise.path())) {
            problems.push_back(std::format("{} is missing", exercise.path()));
        }
        if (!fs::is_regular_file(exercise.sol_path())) {
            problems.push_back(std::format("{} is missing", exercise.sol_path()));
        }
        if (exercise.hint.empty()) {
            problems.push_back(std::format("The exercise `{}` has no hint", exercise.name));
        }
        if (!exercise.sanitizer.empty() && exercise.sanitizer != "thread") {
            problems.push_back(std::format("The exercise `{}` has the unknown sanitizer `{}`", exercise.name,
                                           exercise.sanitizer));
        }
    }
    for (const std::string& dir : dirs) {
        if (!fs::is_regular_file(fs::path("exercises") / dir / "README.md")) {
            problems.push_back(std::format("exercises/{}/README.md is missing", dir));
        }
    }
    for (const fs::directory_entry& entry : fs::recursive_directory_iterator("exercises")) {
        if (entry.path().extension() == ".cpp" && !listed.contains(entry.path().string())) {
            problems.push_back(std::format("{} isn't listed in info.toml", entry.path().string()));
        }
    }
    return problems;
}

} // namespace

int dev_check() {
    if (!fs::is_regular_file("info.toml")) {
        std::cerr << "Error: `cpplings dev check` must be run in the directory containing info.toml\n";
        return 1;
    }
    InfoFile info = InfoFile::parse(read_file("info.toml"));

    std::vector<std::string> file_problems = check_files(info);
    for (const std::string& problem : file_problems) {
        std::cout << term::red << "ERROR" << term::reset << ' ' << problem << '\n';
    }
    if (!file_problems.empty()) {
        return 1;
    }

    Toolchain toolchain = Toolchain::detect();
    if (!toolchain.has_asan()) {
        std::cout << term::yellow << "WARNING" << term::reset
                  << " AddressSanitizer isn't available; exercises are checked with trapping UBSan only\n";
    }

    std::vector<Problem> problems;
    std::mutex mutex;
    std::atomic<std::size_t> next = 0;
    std::atomic<std::size_t> checked = 0;
    const std::size_t total = info.exercises.size();

    {
        std::vector<std::jthread> workers;
        for (unsigned t = 0; t < std::max(1u, std::thread::hardware_concurrency()); ++t) {
            workers.emplace_back([&] {
                while (true) {
                    std::size_t ind = next.fetch_add(1);
                    if (ind >= total) {
                        return;
                    }
                    const ExerciseInfo& exercise = info.exercises[ind];
                    std::vector<Problem> found;

                    std::string output;
                    if (!exercise.skip_check_unsolved && run_exercise(exercise, toolchain, false, &output)) {
                        found.push_back({std::format("The exercise `{}` passes without changes. Consider setting "
                                                     "`skip_check_unsolved = true`",
                                                     exercise.name),
                                         output});
                    }
                    output.clear();
                    if (!run_exercise(exercise, toolchain, true, &output)) {
                        found.push_back({std::format("The solution of `{}` fails", exercise.name), output});
                    } else if (output.find("warning:") != std::string::npos) {
                        found.push_back({std::format("The solution of `{}` has warnings", exercise.name), output});
                    }

                    std::lock_guard lock(mutex);
                    problems.insert(problems.end(), found.begin(), found.end());
                    std::cout << std::format("\rChecked {}/{}", ++checked, total) << std::flush;
                }
            });
        }
    }
    std::cout << "\n\n";

    for (const Problem& problem : problems) {
        std::cout << term::red << "ERROR" << term::reset << ' ' << problem.message << '\n'
                  << problem.output << '\n';
    }
    if (!problems.empty()) {
        std::cout << problems.size() << " problem(s) found\n";
        return 1;
    }
    std::cout << term::green << "Everything looks fine ✓" << term::reset << '\n';
    return 0;
}
