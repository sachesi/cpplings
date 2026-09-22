#pragma once

#include <vector>

struct ExerciseInfo;
class Toolchain;

// Creates the `cpplings/` directory with the exercises.
void init();

// Writes compile_commands.json so clangd and other tools find the compiler flags.
void write_compile_commands(const Toolchain& toolchain, const std::vector<ExerciseInfo>& exercises);
