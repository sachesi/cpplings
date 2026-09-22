# cpplings

Small exercises to get you used to reading and writing modern C++ code. It works
like [Rustlings](https://github.com/rust-lang/rustlings), with the same workflow
and the same commands, but for C++23.

Every exercise is a small program that doesn't compile or whose tests fail. You
fix it in your editor, cpplings notices the change, compiles and runs it again,
and moves you on once it passes. The exercises start with variables and
functions and go through references, classes, templates, concepts, RAII, move
semantics, smart pointers, ranges and threads.

## Requirements

- Linux (macOS should work, but is untested)
- A C++23 compiler and standard library. cpplings is tested with GCC 16 and
  Clang 22, both with libstdc++.
- CMake 3.20 or newer to build cpplings itself

Optional, but recommended: the sanitizer runtimes of your compiler (on Fedora
`dnf install libasan libubsan libtsan`, on Debian and Ubuntu they come with GCC).
cpplings checks at startup whether they work and otherwise falls back to a mode
that needs no runtime library.

## Installation

Every [release](https://github.com/sachesi/cpplings/releases) has packages for
Fedora, Debian, Ubuntu and Arch Linux, and a binary for any Linux distribution
with glibc 2.39 or newer. To build it yourself:

```sh
git clone https://github.com/sachesi/cpplings.git cpplings-src
cd cpplings-src
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build --prefix ~/.local
```

The exercises are compiled into the binary, so the source directory isn't needed
afterwards. Make sure that `~/.local/bin` is in your `PATH`.

## Getting started

```sh
cpplings init
cd cpplings
cpplings
```

`cpplings init` creates the directory `cpplings/` with the exercises. Open it in
your editor. Running `cpplings` without arguments starts the watch mode, which
shows the current exercise under the progress bar and reruns it whenever you save
the file. It understands these keys:

- `n` moves on to the next exercise once the current one is done
- `h` shows a hint
- `l` opens the list of all exercises
- `x` resets the current exercise to its original state
- `q` quits

In the list, `j`/`k` or the arrow keys move the selection, `c` or Enter continues
at the selected exercise, `r` resets it, `s` or `/` searches, `d` and `p` show
only done or pending exercises, and `q` goes back.

When you finish an exercise, its solution is written to `solutions/` for
comparison. Your progress is stored in `.cpplings-state.txt`.

Other commands:

```
cpplings run [NAME]     compile and run one exercise, the current one by default
cpplings hint [NAME]    show a hint
cpplings reset NAME     reset an exercise
cpplings check-all      check all exercises and update the progress
```

`--edit-cmd CMD` opens every new exercise with `CMD PATH`; the command must not
block, so it's meant for editors with a client like `code` or `emacsclient -n`.
In the VS Code terminal this happens automatically unless `--no-editor` is given.
If saving a file isn't detected, run `cpplings --manual-run` and press `r` to run
the exercise.

## How exercises are compiled

cpplings uses `c++` unless the `CXX` environment variable names another compiler.
Each exercise is compiled on its own:

```
c++ -std=c++23 -g -O0 -Wall -Wextra -Wpedantic -pthread -Iinclude \
    -D_GLIBCXX_DEBUG -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG \
    -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer
```

The debug mode of the standard library turns out-of-bounds indexing, invalid
iterators and empty `std::optional` access into an immediate abort with a
message. If AddressSanitizer isn't usable, `-fsanitize=undefined
-fsanitize-trap=all` is used instead: undefined behavior still stops the program,
just without the detailed report. The exercises of the warnings section add
`-Werror -Wconversion -Wshadow`. A program that runs longer than 10 seconds is
stopped.

Exercises with tests include `cpplings_test.hpp`, a small test framework in the
`include/` directory that provides `main`.

cpplings writes a `compile_commands.json` with these flags, so clangd and other
tools see exactly what the compiler sees.

## Contributing

The exercises are in `exercises/`, their solutions in `solutions/`, and
`info.toml` lists them in order together with their hints. After changing them,
rebuild and run the checks from the repository root:

```sh
cmake --build build
./build/cpplings dev check
```

`dev check` makes sure that every exercise fails as it is, that every solution
passes without warnings, and that `info.toml` and the files agree. Run it with
both GCC and Clang (`CXX=clang++ ./build/cpplings dev check`).

## Credits

cpplings is modeled on [Rustlings](https://github.com/rust-lang/rustlings) by
Carol Nichols and the Rustlings contributors. The user interface follows
Rustlings closely, and several exercises and texts are adapted from it.

Contact: sachesi <xsachesi@pm.me>

## License

MIT, see [LICENSE](LICENSE).
