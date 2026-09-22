#pragma once

#include <string>
#include <vector>

struct ExerciseInfo;

class Toolchain {
public:
    // Uses $CXX (default `c++`) and probes which sanitizers can be used.
    // The probe result is cached in `.cpplings/`. Throws std::runtime_error if the
    // compiler can't be run.
    static Toolchain detect();

    const std::string& cxx() const { return cxx_; }
    bool has_asan() const { return has_asan_; }

    // Compiler flags without the source and output file.
    std::vector<std::string> flags(const ExerciseInfo& exercise) const;
    std::vector<std::string> compile_command(const ExerciseInfo& exercise, const std::string& source,
                                             const std::string& binary) const;

private:
    std::string cxx_;
    bool has_asan_ = false;
    bool has_tsan_ = false;
};

inline constexpr const char* build_dir = ".cpplings";
