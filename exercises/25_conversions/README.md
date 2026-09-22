# Conversions

C++ converts between many types implicitly: `int` to `double`, `double` to `int`,
signed to unsigned, and to any class with a constructor taking one argument.
Some of these conversions are surprising, especially between signed and unsigned
integers.

Use `static_cast<T>(value)` to convert on purpose; it stands out when reading the
code. Avoid C-style casts like `(int)value`, which can silently do much more
dangerous conversions.

Your own classes can take part in conversions: constructors with a single
argument convert *to* the class, and conversion operators (`operator double()`)
convert *from* it. Mark both `explicit` unless the conversion is obvious and
lossless.

## Further information

- [Implicit type conversion](https://www.learncpp.com/cpp-tutorial/implicit-type-conversion/)
- [Explicit type conversion and static_cast](https://www.learncpp.com/cpp-tutorial/explicit-type-conversion-casting-and-static-cast/)
- [Converting constructors and the explicit keyword](https://www.learncpp.com/cpp-tutorial/converting-constructors-and-the-explicit-keyword/)
- [Overloading typecasts](https://www.learncpp.com/cpp-tutorial/overloading-typecasts/)
