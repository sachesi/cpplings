#include "cpplings_test.hpp"

#include <cmath>

long whole_points(double points) {
    return std::lround(points);
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
