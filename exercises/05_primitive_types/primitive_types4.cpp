// Integer division

#include "cpplings_test.hpp"

// TODO: Fix the function so that the tests pass.
double average(int a, int b) {
    return (a + b) / 2;
}

TEST(average_of_even_sum) {
    CHECK_NEAR(average(2, 4), 3.0, 1e-9);
}

TEST(average_of_odd_sum) {
    CHECK_NEAR(average(2, 3), 2.5, 1e-9);
    CHECK_NEAR(average(-7, 0), -3.5, 1e-9);
}
