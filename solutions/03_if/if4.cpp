#include "cpplings_test.hpp"

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

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
