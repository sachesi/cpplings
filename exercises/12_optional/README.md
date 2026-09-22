# Optional

`std::optional<T>` either holds a value of type `T` or holds nothing
(`std::nullopt`). It makes "there might not be a value" part of the type, instead
of using special values like `-1` or a null pointer.

Check whether there is a value with `has_value()` or by using the optional as a
condition. `*opt` and `opt->member` access the value without checking, which is
undefined behavior when it's empty. `value()` throws when it's empty, and
`value_or(fallback)` returns the fallback instead.

C++23 added `transform`, `and_then` and `or_else` to chain steps that might not
produce a value.

## Further information

- [Introduction to std::optional](https://www.learncpp.com/cpp-tutorial/stdoptional/)
- [std::optional on cppreference](https://en.cppreference.com/w/cpp/utility/optional)
