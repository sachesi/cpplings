#include "cpplings_test.hpp"

#include <ostream>

struct Vec2 {
    double x = 0.0;
    double y = 0.0;

    // A defaulted `==` also provides `!=`.
    bool operator==(const Vec2&) const = default;
};

Vec2 operator+(Vec2 a, Vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

Vec2 operator*(Vec2 v, double factor) {
    return {v.x * factor, v.y * factor};
}

std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    return os << '(' << v.x << ", " << v.y << ')';
}

TEST(adding_vectors) {
    Vec2 a{1.0, 2.0};
    Vec2 b{3.0, 4.0};
    CHECK_EQ(a + b, (Vec2{4.0, 6.0}));
}

TEST(scaling_vectors) {
    Vec2 a{1.0, -2.0};
    CHECK_EQ(a * 3.0, (Vec2{3.0, -6.0}));
}

TEST(comparing_vectors) {
    CHECK((Vec2{1.0, 2.0} == Vec2{1.0, 2.0}));
    CHECK((Vec2{1.0, 2.0} != Vec2{2.0, 1.0}));
}
