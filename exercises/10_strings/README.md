# Strings

C++ has several ways to deal with text:

- A string literal like `"hello"` is an array of `const char`, inherited from C.
  It decays to a `const char*` pointer, so `==` compares addresses, not text.
- `std::string` owns its characters, can grow, and has the operations you'd
  expect: `+`, `==`, `find`, `substr`, `replace`, ...
- `std::string_view` is a cheap, read-only view into characters owned by
  something else. It's the usual type for string parameters that are only read.
  A view must not outlive the string it points into.

`std::format` (C++20) builds strings from a format string with `{}` placeholders,
and `std::println` (C++23) prints the result directly.

## Further information

- [Introduction to std::string](https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/)
- [Introduction to std::string_view](https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring_view/)
- [std::basic_string on cppreference](https://en.cppreference.com/w/cpp/string/basic_string)
- [std::format](https://en.cppreference.com/w/cpp/utility/format/format)
- [Format specification](https://en.cppreference.com/w/cpp/utility/format/spec)
