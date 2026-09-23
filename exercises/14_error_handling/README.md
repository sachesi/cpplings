# Error handling

C++ has two main ways to report errors.

Exceptions are thrown with `throw` and caught further up the call stack with
`try` / `catch`, skipping everything in between. The standard library throws
types derived from `std::exception`, e.g. `std::invalid_argument` or
`std::out_of_range`. Throw by value and catch by (const) reference. An exception
that nobody catches ends the program.

`std::expected<T, E>` (C++23) returns either a value or an error as a normal
return value. The caller has to look at it, and nothing is skipped silently. It
has the same `and_then` / `transform` chaining as `std::optional`, plus
`transform_error` for the error side.

## Further information

- [Basic exception handling](https://www.learncpp.com/cpp-tutorial/basic-exception-handling/)
- [Exceptions, classes and inheritance](https://www.learncpp.com/cpp-tutorial/exceptions-classes-and-inheritance/)
- [std::exception hierarchy](https://en.cppreference.com/w/cpp/error/exception)
- [std::expected](https://en.cppreference.com/w/cpp/utility/expected)
