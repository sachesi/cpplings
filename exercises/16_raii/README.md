# RAII and Lifetimes

Every object in C++ has a lifetime. A local variable is destroyed when its scope
ends, and its destructor runs at exactly that point, even when the scope is left
by `return` or by an exception.

RAII ("Resource Acquisition Is Initialization") builds on this: a class acquires
a resource (memory, a file, a lock) in its constructor and releases it in its
destructor. Then the resource can't be forgotten or leaked. Standard types like
`std::vector`, `std::string`, `std::unique_ptr` and `std::lock_guard` all work
this way.

A class that manages a resource by hand also has to decide what copying means.
The "rule of three" says: if you need a destructor, you also need a copy
constructor and a copy assignment operator (or must forbid copying). Better yet,
follow the "rule of zero" and let members like `std::vector` manage resources.

References, pointers and `std::string_view` don't extend the lifetime of what
they refer to. Keeping one after the object is gone is a dangling reference.

## Further information

- [Destructors](https://www.learncpp.com/cpp-tutorial/destructors/)
- [RAII on cppreference](https://en.cppreference.com/w/cpp/language/raii)
- [The rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [Dangling references](https://www.learncpp.com/cpp-tutorial/return-by-reference-and-return-by-address/)
