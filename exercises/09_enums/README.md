# Enums

An `enum class` defines a type with a fixed set of named values. Unlike the older
plain `enum`, its values must be written with the type name (`Color::Red`) and
don't convert to integers on their own. The underlying integer is available with
`std::to_underlying` from `<utility>`.

A `switch` over an enum can handle every value. With warnings enabled, the
compiler reports values that aren't handled, which is a good reason to not add a
`default` case.

When different alternatives carry different data, `std::variant` holds exactly
one of several types, and `std::visit` calls the right code for the alternative
it currently holds. `std::holds_alternative` checks for an alternative, and
`std::get` throws when asked for the wrong one.

## Further information

- [Scoped enumerations (enum classes)](https://www.learncpp.com/cpp-tutorial/scoped-enumerations-enum-classes/)
- [std::variant](https://en.cppreference.com/w/cpp/utility/variant)
- [std::visit](https://en.cppreference.com/w/cpp/utility/variant/visit)
