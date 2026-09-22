#include "cpplings_test.hpp"

#include <tuple>

TEST(indexing_tuple) {
    std::tuple<int, int, int> numbers = {1, 2, 3};

    int second = std::get<1>(numbers);

    CHECK_EQ(second, 2);
}
