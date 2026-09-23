#include "cpplings_test.hpp"

#include <cmath>

bool nearly_equal(double a, double b) {
    return std::abs(a - b) < 1e-9;
}

TEST(same_numbers) {
    CHECK(nearly_equal(1.5, 1.5));
}

TEST(rounding_errors) {
    CHECK(nearly_equal(0.1 + 0.2, 0.3));
    CHECK(nearly_equal(0.3 - 0.1, 0.2));
}

TEST(different_numbers) {
    CHECK(!nearly_equal(0.1, 0.2));
    CHECK(!nearly_equal(0.3, 0.1 + 0.2 + 0.001));
}
