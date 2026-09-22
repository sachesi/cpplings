# Algorithms and Ranges

The headers `<algorithm>` and `<numeric>` contain dozens of well-tested functions
for common loops: sorting, searching, counting, summing, transforming, removing.
Using them makes the intent clear and avoids off-by-one mistakes. Most take a
lambda to customize what they do.

C++20 added *ranges*: the algorithms in `std::ranges` take a whole container
instead of two iterators, and *views* in `std::views` form lazy pipelines with
`|`, e.g. `numbers | std::views::filter(...) | std::views::transform(...)`.
Nothing is computed until the view is iterated. `std::ranges::to` (C++23)
collects a view into a container.

## Further information

- [Introduction to standard library algorithms](https://www.learncpp.com/cpp-tutorial/introduction-to-standard-library-algorithms/)
- [Algorithms library](https://en.cppreference.com/w/cpp/algorithm)
- [Ranges library](https://en.cppreference.com/w/cpp/ranges)
- [Erase-remove idiom and std::erase_if](https://en.cppreference.com/w/cpp/container/vector/erase2)
