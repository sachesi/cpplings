# Structs and Classes

A `struct` groups related values into one type. Structs with only public data
members can be initialized directly from a braced list, optionally naming the
members: `Point p{.x = 1, .y = 2};`

Member functions operate on the object they are called on. A member function
marked `const` promises not to change the object, and only `const` member
functions can be called on `const` objects or through `const` references.

`class` and `struct` are the same thing except for one detail: members of a
`class` are private unless an access specifier says otherwise. Classes usually
keep their data private and offer member functions instead, so they can maintain
rules about their data (invariants). Constructors set up a new object.

## Further information

- [Introduction to structs](https://www.learncpp.com/cpp-tutorial/introduction-to-structs-members-and-member-selection/)
- [Struct aggregate initialization](https://www.learncpp.com/cpp-tutorial/struct-aggregate-initialization/)
- [Member functions](https://www.learncpp.com/cpp-tutorial/member-functions/)
- [Const class objects and const member functions](https://www.learncpp.com/cpp-tutorial/const-class-objects-and-const-member-functions/)
- [Public and private members](https://www.learncpp.com/cpp-tutorial/public-and-private-members-and-access-specifiers/)
- [Operator overloading](https://www.learncpp.com/cpp-tutorial/introduction-to-operator-overloading/)
