#include "cpplings_test.hpp"

int digit_count(int n) {
    int digits = 0;
    do {
        n /= 10;
        ++digits;
    } while (n > 0);
    return digits;
}

TEST(several_digits) {
    CHECK_EQ(digit_count(7), 1);
    CHECK_EQ(digit_count(42), 2);
    CHECK_EQ(digit_count(1'000'000), 7);
}

TEST(zero_has_one_digit) {
    CHECK_EQ(digit_count(0), 1);
}
