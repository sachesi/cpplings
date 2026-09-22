#include "cpplings_test.hpp"

#include <algorithm>
#include <array>
#include <utility>
#include <vector>

std::pair<std::array<int, 4>, std::vector<int>> array_and_vector() {
    std::array<int, 4> a = {10, 20, 30, 40};

    std::vector<int> v = {10, 20, 30, 40};
    // Or copy the elements of the array:
    // std::vector<int> v(a.begin(), a.end());

    return {a, v};
}

TEST(array_and_vector_similarity) {
    auto [a, v] = array_and_vector();
    CHECK_EQ(a[0], 10);
    CHECK_EQ(v.size(), 4);
    CHECK(std::ranges::equal(a, v));
}
