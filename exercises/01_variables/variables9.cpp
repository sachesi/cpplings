#include "cpplings_test.hpp"

double total_distance() {
    // TODO: The tests fail. What type does the compiler deduce for `distance`?
    auto distance = 0;
    distance += 2.5;
    distance += 1.25;
    return distance;
}

TEST(distances_add_up) {
    CHECK_NEAR(total_distance(), 3.75, 1e-9);
}
