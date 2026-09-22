#include "cpplings_test.hpp"

#include <array>
#include <cstddef>

// TODO: Make `sum` work for arrays with any element type and any size. The size
// of a `std::array` is a template parameter too.
int sum(const std::array<int, 3>& values) {
    int total = 0;
    for (int value : values) {
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
