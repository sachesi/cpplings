// Tuples

#include "cpplings_test.hpp"

#include <tuple>

TEST(indexing_tuple) {
    std::tuple<int, int, int> numbers = {1, 2, 3};

    // TODO: Use `std::get` to read the second element of `numbers`. Remember that
    // counting starts at 0.
    int second = ???;

    CHECK_EQ(second, 2);
}
