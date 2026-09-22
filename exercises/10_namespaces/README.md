# Namespaces

Namespaces group names and prevent collisions between them: the standard library
lives in the namespace `std`, which is why it's `std::string` and not just
`string`. Names inside a namespace are reached with the scope resolution operator
`::`.

`using` declarations bring single names into the current scope, and namespace
aliases give long namespace names a shorter one. `using namespace` imports a whole
namespace; it's handy for things like literal suffixes, but avoid it at the top
of headers.

## Further information

- [User-defined namespaces](https://www.learncpp.com/cpp-tutorial/user-defined-namespaces-and-the-scope-resolution-operator/)
- [Using declarations and using directives](https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/)
- [Namespace aliases](https://en.cppreference.com/w/cpp/language/namespace_alias)
- [std::chrono](https://en.cppreference.com/w/cpp/chrono)
