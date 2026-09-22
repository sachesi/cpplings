#include "cpplings_test.hpp"

#include <ostream>

struct Vec2 {
    double x = 0.0;
    double y = 0.0;

    // TODO: Let the compiler generate `==`, which compares the members one by one.
};

// TODO: Implement `+` for two vectors and `*` for a vector and a number.

// Used by the tests to print vectors.
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
