// Integer overflow

#include "cpplings_test.hpp"

#include <cstdint>

// TODO: A 32-bit `int` can hold values up to 2'147'483'647. That is only about 24
// days in milliseconds. Fix the function so that it works for longer durations
// by using a type that is guaranteed to be 64 bits wide.
int milliseconds_in_days(int days) {
    return days * 24 * 60 * 60 * 1000;
}

TEST(one_day) {
    CHECK_EQ(milliseconds_in_days(1), 86'400'000);
}

TEST(thirty_days) {
    CHECK_EQ(milliseconds_in_days(30), 2'592'000'000);
}

TEST(one_year) {
    CHECK_EQ(milliseconds_in_days(365), 31'536'000'000);
}
