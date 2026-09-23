// Comparing floating-point numbers

#include "cpplings_test.hpp"

#include <cmath>

// TODO: `0.1 + 0.2` is not exactly `0.3` because most decimal fractions can't
// be represented exactly in binary. Treat two numbers as equal when their
// difference is smaller than 1e-9.
bool nearly_equal(double a, double b) {
    return a == b;
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
