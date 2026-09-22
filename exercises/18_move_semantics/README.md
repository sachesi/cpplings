# Move Semantics

Copying a `std::vector` or `std::string` copies all of its elements. Often the
source isn't needed afterwards, and the contents could simply be handed over.
That's what moving does: a move constructor steals the internal buffer of the
source and leaves the source in a valid but unspecified state (usually empty).

`std::move(x)` doesn't move anything by itself. It's a cast that says "I don't
need `x` anymore", which lets the compiler pick a move constructor or move
assignment operator. Some types, like `std::unique_ptr`, can only be moved, not
copied.

Containers like `std::vector` only move elements when reallocating if the move
constructor is `noexcept`; otherwise they copy to stay safe from exceptions.

## Further information

- [Introduction to smart pointers and move semantics](https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/)
- [Move constructors and move assignment](https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/)
- [std::move](https://www.learncpp.com/cpp-tutorial/stdmove/)
- [std::forward](https://en.cppreference.com/w/cpp/utility/forward)
