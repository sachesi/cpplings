#include "cpplings_test.hpp"

struct Color {
    int red;
    int green;
    int blue;
};

struct Point {
    double x;
    double y;
};

TEST(color_struct) {
    Color green{0, 255, 0};

    CHECK_EQ(green.red, 0);
    CHECK_EQ(green.green, 255);
    CHECK_EQ(green.blue, 0);
}

TEST(point_struct) {
    // Naming the members makes the intent clearer.
    Point point{.x = 1.5, .y = -2.0};

    CHECK_NEAR(point.x, 1.5, 1e-9);
    CHECK_NEAR(point.y, -2.0, 1e-9);
}
