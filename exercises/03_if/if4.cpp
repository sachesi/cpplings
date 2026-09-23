#include "cpplings_test.hpp"

// A year is a leap year if it is divisible by 4, except for years divisible by
// 100. Those are only leap years if they are also divisible by 400.
bool is_leap_year(int year) {
    // TODO: The rule about 400 is missing. Complete the condition with `&&`
    // (and), `||` (or) and parentheses.
    return year % 4 == 0 && year % 100 != 0;
}

// Don't change the tests!
TEST(ordinary_years) {
    CHECK(!is_leap_year(2023));
    CHECK(!is_leap_year(2025));
}

TEST(divisible_by_four) {
    CHECK(is_leap_year(2024));
    CHECK(is_leap_year(1996));
}

TEST(centuries) {
    CHECK(!is_leap_year(1900));
    CHECK(!is_leap_year(2100));
}

TEST(divisible_by_four_hundred) {
    CHECK(is_leap_year(2000));
    CHECK(is_leap_year(1600));
}
