#include "cpplings_test.hpp"

#include <concepts>
#include <vector>

template <typename T>
concept Shape = requires(const T& shape) {
    { shape.area() } -> std::convertible_to<double>;
};

template <Shape S>
double total_area(const std::vector<S>& shapes) {
    double total = 0.0;
    for (const S& shape : shapes) {
        total += shape.area();
    }
    return total;
}

struct Square {
    double side;
    double area() const { return side * side; }
};

struct Circle {
    double radius;
    double area() const { return 3.0 * radius * radius; }
};

struct Line {
    double length;
};

TEST(shapes_satisfy_the_concept) {
    static_assert(Shape<Square>);
    static_assert(Shape<Circle>);
}

TEST(other_types_dont_satisfy_it) {
    static_assert(!Shape<Line>);
    static_assert(!Shape<int>);
}

TEST(total_area_of_squares) {
    std::vector<Square> squares = {{1.0}, {2.0}};
    CHECK_NEAR(total_area(squares), 5.0, 1e-9);
}
