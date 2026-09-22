# Smart Pointers

Objects created with `new` live until they are destroyed with `delete`. Forgetting
the `delete` leaks memory, doing it twice or too early is undefined behavior.
Smart pointers do the `delete` for you:

- `std::unique_ptr<T>` is the single owner of an object and deletes it when the
  pointer is destroyed. Create one with `std::make_unique<T>(...)`.
- `std::shared_ptr<T>` allows several owners. It counts them, and the object is
  deleted when the last owner is gone. Create one with `std::make_shared<T>(...)`.
- `std::weak_ptr<T>` refers to an object owned by `shared_ptr`s without owning it.
  It's used to break reference cycles, which would otherwise keep each other
  alive forever.

In modern C++, you rarely write `new` or `delete` yourself.

## Further information

- [std::unique_ptr](https://www.learncpp.com/cpp-tutorial/stdunique_ptr/)
- [std::shared_ptr](https://www.learncpp.com/cpp-tutorial/stdshared_ptr/)
- [Circular dependency issues with std::shared_ptr, and std::weak_ptr](https://www.learncpp.com/cpp-tutorial/circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/)
