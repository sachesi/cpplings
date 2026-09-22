# Warnings

C++ compilers accept a lot of code that is legal but almost certainly wrong, and
they report it as warnings. Warnings are free bug reports: many teams turn them
into errors with `-Werror`.

The exercises in this section are compiled with `-Werror` and a few extra warnings
that aren't part of `-Wall -Wextra`:

- `-Wconversion` reports implicit conversions that may change a value, like
  `double` to `int`.
- `-Wshadow` reports variables that hide another variable with the same name.

Fix the code instead of silencing the warning: a cast is fine when a conversion
is intended, but it should say so explicitly.

## Further information

- [GCC warning options](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
- [Configuring compiler warnings](https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-warning-and-error-levels/)
- [Implicit conversions](https://en.cppreference.com/w/cpp/language/implicit_conversion)
