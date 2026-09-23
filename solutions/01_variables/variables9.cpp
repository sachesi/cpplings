#include "cpplings_test.hpp"

double total_distance() {
    // `0` is an `int` literal while `0.0` is a `double` literal.
    auto distance = 0.0;
    distance += 2.5;
    distance += 1.25;
    return distance;
}

TEST(distances_add_up) {
    CHECK_NEAR(total_distance(), 3.75, 1e-9);
}
