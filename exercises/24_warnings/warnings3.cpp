// The warnings of this exercise are treated as errors.

#include "cpplings_test.hpp"

class Rectangle {
public:
    // TODO: Fix the compiler errors. Which `width` does `width = width` refer to?
    Rectangle(int width, int height) {
        width = width;
        height = height;
    }

    int area() const { return width * height; }

private:
    int width = 0;
    int height = 0;
};

TEST(area) {
    Rectangle rectangle(3, 4);
    CHECK_EQ(rectangle.area(), 12);
}
