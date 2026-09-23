#include "cpplings_test.hpp"

// Counts the decimal digits of a number that isn't negative.
int digit_count(int n) {
    int digits = 0;
    // TODO: The number 0 has one digit, but this loop never runs for it. Turn it
    // into a `do`-`while` loop, which checks its condition after the body.
    while (n > 0) {
        n /= 10;
        ++digits;
    }
    return digits;
}

// Don't change the tests!
TEST(several_digits) {
    CHECK_EQ(digit_count(7), 1);
    CHECK_EQ(digit_count(42), 2);
    CHECK_EQ(digit_count(1'000'000), 7);
}

TEST(zero_has_one_digit) {
    CHECK_EQ(digit_count(0), 1);
}
