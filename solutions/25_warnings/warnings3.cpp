#include "cpplings_test.hpp"

class Rectangle {
public:
    // A member initializer list initializes the members directly. The trailing
    // underscore keeps the members apart from the parameters.
    Rectangle(int width, int height) : width_(width), height_(height) {}

    int area() const { return width_ * height_; }

private:
    int width_ = 0;
    int height_ = 0;
};

TEST(area) {
    Rectangle rectangle(3, 4);
    CHECK_EQ(rectangle.area(), 12);
}
