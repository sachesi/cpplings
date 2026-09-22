# Concepts and Polymorphism

There are two ways in C++ to write code that works with different types that
share some behavior.

**Concepts** (C++20) constrain templates at compile time. A concept is a named
set of requirements, e.g. "has a member function `area()` returning a number". A
template constrained by a concept can only be used with types that satisfy it,
and the compiler reports a readable error otherwise. The standard library brings
many concepts, like `std::integral` or `std::copyable`.

**Virtual functions** give runtime polymorphism. A base class declares
`virtual` member functions, derived classes `override` them, and a call through a
base class reference or pointer runs the version of the actual object. Base
classes used this way need a virtual destructor.

## Further information

- [Constraints and concepts](https://en.cppreference.com/w/cpp/language/constraints)
- [Standard library concepts](https://en.cppreference.com/w/cpp/concepts)
- [Virtual functions and polymorphism](https://www.learncpp.com/cpp-tutorial/virtual-functions/)
- [The override and final specifiers](https://www.learncpp.com/cpp-tutorial/the-override-and-final-specifiers-and-covariant-return-types/)
- [Virtual destructors](https://www.learncpp.com/cpp-tutorial/virtual-destructors-virtual-assignment-and-overriding-virtualization/)
