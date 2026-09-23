// Converting floating-point numbers to integers

#include "cpplings_test.hpp"

#include <cmath>

// TODO: Converting a `double` to `long` cuts off the fractional part. Round to
// the nearest whole number instead, with halves rounded away from zero.
long whole_points(double points) {
    return static_cast<long>(points);
}

TEST(rounding_down) {
    CHECK_EQ(whole_points(7.2), 7);
    CHECK_EQ(whole_points(-7.2), -7);
}

TEST(rounding_up) {
    CHECK_EQ(whole_points(7.8), 8);
    CHECK_EQ(whole_points(-7.8), -8);
}

TEST(halves) {
    CHECK_EQ(whole_points(2.5), 3);
    CHECK_EQ(whole_points(-2.5), -3);
}
