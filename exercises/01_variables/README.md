# Variables

A variable in C++ has a type that is fixed when the variable is declared. You can
spell the type out (`int count = 0;`) or let the compiler deduce it from the
initializer (`auto count = 0;`). Variables can be changed unless they are declared
`const`, and `constexpr` goes one step further: the value must be known while the
program is being compiled.

Prefer initializing variables right where you declare them. The brace form
`int count{0};` also refuses conversions that would lose information.

## Further information

- [Introduction to objects and variables](https://www.learncpp.com/cpp-tutorial/introduction-to-objects-and-variables/)
- [Variable assignment and initialization](https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/)
- [Const variables](https://www.learncpp.com/cpp-tutorial/constant-variables-named-constants/)
- [Constexpr variables](https://www.learncpp.com/cpp-tutorial/constexpr-variables/)
