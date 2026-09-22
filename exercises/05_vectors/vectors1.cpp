#include "cpplings_test.hpp"

#include <algorithm>
#include <array>
#include <utility>
#include <vector>

std::pair<std::array<int, 4>, std::vector<int>> array_and_vector() {
    // TODO: Fill the array `a` with the values 10, 20, 30, 40.
    std::array<int, 4> a = {};

    // TODO: Create a vector `v` which contains the same elements as the array `a`.
    // std::vector<int> v = ???;

    return {a, v};
}

TEST(array_and_vector_similarity) {
    auto [a, v] = array_and_vector();
    CHECK_EQ(a[0], 10);
    CHECK_EQ(v.size(), 4);
    CHECK(std::ranges::equal(a, v));
}
