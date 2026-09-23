#include "cpplings_test.hpp"

#include <array>
#include <cstddef>

template <typename T, std::size_t N>
T sum(const std::array<T, N>& values) {
    T total{};
    for (const T& value : values) {
        total += value;
    }
    return total;
}

TEST(three_ints) {
    CHECK_EQ(sum(std::array<int, 3>{1, 2, 3}), 6);
}

TEST(five_ints) {
    CHECK_EQ(sum(std::array<int, 5>{1, 2, 3, 4, 5}), 15);
}

TEST(two_doubles) {
    CHECK_NEAR(sum(std::array<double, 2>{0.5, 0.25}), 0.75, 1e-9);
}
