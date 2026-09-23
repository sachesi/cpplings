# Threads

A thread runs code at the same time as the rest of the program. `std::thread`
starts one; before the `std::thread` object is destroyed, you must either wait
for it with `join()` or let it run on its own with `detach()`. `std::jthread`
(C++20) joins automatically in its destructor.

When threads share data and at least one of them writes to it, every access must
be synchronized. Otherwise it's a *data race*, which is undefined behavior.
Protect shared data with a `std::mutex` (locked through `std::lock_guard` or
`std::unique_lock`), or use `std::atomic` for single values.

A `std::condition_variable` lets a thread sleep until another thread tells it that
something changed, for example that new work is available.

## Further information

- [std::thread](https://en.cppreference.com/w/cpp/thread/thread)
- [std::jthread](https://en.cppreference.com/w/cpp/thread/jthread)
- [std::mutex](https://en.cppreference.com/w/cpp/thread/mutex)
- [std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic)
- [std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)
