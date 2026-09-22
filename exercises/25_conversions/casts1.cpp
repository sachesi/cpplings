#include "cpplings_test.hpp"

#include <vector>

// TODO: The average is wrong, and for negative numbers it's completely off.
// `values.size()` is an unsigned `std::size_t`. What happens when an `int` is
// divided by it? Fix the calculation using `static_cast`.
double average(const std::vector<int>& values) {
    int total = 0;
    for (int value : values) {
        total += value;
    }
    return total / values.size();
}

TEST(positive_numbers) {
    CHECK_NEAR(average({1, 2, 3, 4}), 2.5, 1e-9);
}

TEST(negative_numbers) {
    CHECK_NEAR(average({-1, -2, -6}), -3.0, 1e-9);
}
