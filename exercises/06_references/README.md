# References and Pointers

By default, C++ passes arguments *by value*: the function gets its own copy. A
reference (`int&`) is another name for an existing object, so a function taking a
reference can change the caller's variable, and nothing is copied. `const T&`
gives read access without copying and also binds to temporary values.

A pointer (`int*`) stores the address of an object. Unlike a reference, it can be
null (`nullptr`) and can be changed to point somewhere else. `&x` takes the
address of `x`, and `*p` gives the object that `p` points to.

Neither references nor pointers keep an object alive. Using one after the object
has been destroyed is undefined behavior; this is called a dangling reference.

## Further information

- [Lvalue references](https://www.learncpp.com/cpp-tutorial/lvalue-references/)
- [Pass by lvalue reference](https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/)
- [Introduction to pointers](https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/)
- [Null pointers](https://www.learncpp.com/cpp-tutorial/null-pointers/)
- [std::span](https://en.cppreference.com/w/cpp/container/span)
