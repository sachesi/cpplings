#include "cpplings_test.hpp"

struct Color {
    // TODO: Add the fields `red`, `green` and `blue`, each an `int`.
};

struct Point {
    // TODO: Add the fields `x` and `y`, each a `double`.
};

TEST(color_struct) {
    // TODO: Instantiate a `Color` with the values 0, 255, 0.
    // Color green = ???;

    CHECK_EQ(green.red, 0);
    CHECK_EQ(green.green, 255);
    CHECK_EQ(green.blue, 0);
}

TEST(point_struct) {
    // TODO: Instantiate a `Point` at x = 1.5, y = -2.0.
    // Point point = ???;

    CHECK_NEAR(point.x, 1.5, 1e-9);
    CHECK_NEAR(point.y, -2.0, 1e-9);
}
