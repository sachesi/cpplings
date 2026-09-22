# Compile-Time Programming

Before the compiler sees your code, the *preprocessor* handles lines starting with
`#`: it pastes headers in with `#include` and replaces macros defined with
`#define`. Macros are plain text substitution; they know nothing about types,
scopes or evaluation order, which makes function-like macros surprisingly easy to
get wrong. Modern C++ rarely needs them.

The replacement for most macros is `constexpr`: functions and variables that the
compiler can evaluate while compiling, with all the normal rules of the language.
A `consteval` function goes further and *must* be evaluated at compile time, so
mistakes in its arguments become compiler errors.

## Further information

- [Introduction to the preprocessor](https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/)
- [Constexpr functions](https://www.learncpp.com/cpp-tutorial/constexpr-functions/)
- [Consteval functions](https://www.learncpp.com/cpp-tutorial/constexpr-functions-part-4/)
- [static_assert](https://en.cppreference.com/w/cpp/language/static_assert)
