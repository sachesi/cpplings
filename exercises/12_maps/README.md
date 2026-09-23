# Maps

A map stores values under keys. The standard library has two main kinds:

- `std::unordered_map` is a hash table: fast lookups, no particular order.
- `std::map` keeps its keys sorted, which is handy when you need to iterate in
  order.

Be careful with `map[key]`: if the key doesn't exist yet, it *inserts* a
default-constructed value. That's convenient for counting, but it's also why
`operator[]` isn't available on a `const` map. Use `find`, `contains` or `at`
to look things up without inserting.

## Further information

- [std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map)
- [std::map](https://en.cppreference.com/w/cpp/container/map)
- [try_emplace](https://en.cppreference.com/w/cpp/container/map/try_emplace)
