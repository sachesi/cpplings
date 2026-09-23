# Templates

Templates let you write a function or class once and use it with many types. The
compiler generates a separate version for every set of template arguments it's
used with, so templated code is as fast as code written for one specific type.

Template parameters are usually types (`template <typename T>`), but they can
also be values known at compile time, like the size in `std::array<int, 3>`.

Inside a template, `if constexpr` chooses a branch while compiling. The branch
that isn't taken is discarded, so it may contain code that wouldn't compile for
the current type.

## Further information

- [Function templates](https://www.learncpp.com/cpp-tutorial/function-templates/)
- [Class templates](https://www.learncpp.com/cpp-tutorial/class-templates/)
- [Non-type template parameters](https://www.learncpp.com/cpp-tutorial/non-type-template-parameters/)
- [if constexpr](https://en.cppreference.com/w/cpp/language/if#Constexpr_if)
