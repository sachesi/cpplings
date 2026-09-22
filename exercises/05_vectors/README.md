# Vectors

`std::vector` is the container you should reach for first: a resizable array
whose elements are stored next to each other in memory. `std::array` is its
fixed-size sibling, a safer replacement for C arrays.

Loops over containers usually use the range-based `for`. Pay attention to whether
the loop variable is a copy (`auto x`) or a reference (`auto& x`).

A vector moves its elements to a bigger buffer when it grows. Iterators,
references and pointers to the old elements then point to freed memory and must
not be used anymore. cpplings compiles with the checked debug mode of the
standard library, which aborts the program when this happens and when an index
is out of bounds.

## Further information

- [Introduction to std::vector](https://www.learncpp.com/cpp-tutorial/introduction-to-stdvector-and-list-constructors/)
- [Range-based for loops](https://www.learncpp.com/cpp-tutorial/range-based-for-loops-for-each/)
- [std::vector on cppreference](https://en.cppreference.com/w/cpp/container/vector)
- [Iterator invalidation](https://en.cppreference.com/w/cpp/container#Iterator_invalidation)
