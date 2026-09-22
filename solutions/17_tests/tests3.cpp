#include "cpplings_test.hpp"

#include <stdexcept>

class Rectangle {
public:
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
    Rectangle rect(10, 20);
    CHECK_EQ(rect.width(), 10);
    CHECK_EQ(rect.height(), 20);
}

TEST(negative_width) {
    CHECK_THROWS_AS(Rectangle(-10, 10), std::invalid_argument);
}

TEST(negative_height) {
    CHECK_THROWS_AS(Rectangle(10, -10), std::invalid_argument);
}
