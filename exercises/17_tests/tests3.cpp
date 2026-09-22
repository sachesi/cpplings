#include "cpplings_test.hpp"

#include <stdexcept>

class Rectangle {
public:
    // Don't change this constructor!
    Rectangle(int width, int height) : width_(width), height_(height) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Rectangle width and height must be positive");
        }
    }

    int width() const { return width_; }
    int height() const { return height_; }

private:
    int width_;
    int height_;
};

TEST(correct_width_and_height) {
    // TODO: This test should check if the rectangle has the size that we
    // pass to its constructor.
    Rectangle rect(10, 20);
    CHECK_EQ(???, 10); // Check width
    CHECK_EQ(???, 20); // Check height
}

TEST(negative_width) {
    // TODO: This test should check that the constructor throws a
    // `std::invalid_argument` when we try to create a rectangle with a negative
    // width.
    Rectangle rect(-10, 10);
}

TEST(negative_height) {
    // TODO: This test should check that the constructor throws a
    // `std::invalid_argument` when we try to create a rectangle with a negative
    // height.
    Rectangle rect(10, -10);
}
