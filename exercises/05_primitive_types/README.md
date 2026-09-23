# Primitive Types

C++ has a handful of basic types built into the language:

- `bool` is `true` or `false`.
- `char` holds one byte, usually a character. It is a small integer underneath.
- `int`, `long`, `long long` and their `unsigned` variants hold whole numbers.
  Their sizes depend on the platform; `<cstdint>` offers exact sizes like
  `std::int64_t`.
- `float` and `double` hold floating-point numbers.

Two things catch many newcomers: arithmetic on integers stays integral (`7 / 2`
is `3`), and unsigned numbers never go below zero, they wrap around. Overflowing
a *signed* integer is undefined behavior. Floating-point numbers are rarely
exact, so compare them with a tolerance instead of `==`. The bitwise operators
`&`, `|`, `^`, `~`, `<<` and `>>` work on the individual bits of integers.

Arrays inherited from C (`int numbers[3];`) have a fixed size. `std::pair` and
`std::tuple` group a few values of different types.

## Further information

- [Fundamental data types](https://www.learncpp.com/cpp-tutorial/introduction-to-fundamental-data-types/)
- [Unsigned integers, and why to avoid them](https://www.learncpp.com/cpp-tutorial/unsigned-integers-and-why-to-avoid-them/)
- [Floating-point numbers](https://www.learncpp.com/cpp-tutorial/floating-point-numbers/)
- [Bitwise operators](https://www.learncpp.com/cpp-tutorial/bitwise-operators/)
- [Fixed-width integers](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/)
- [Structured bindings](https://en.cppreference.com/w/cpp/language/structured_binding)
