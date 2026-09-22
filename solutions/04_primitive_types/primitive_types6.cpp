#include "cpplings_test.hpp"

#include <cstdint>

std::int64_t milliseconds_in_days(std::int64_t days) {
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
