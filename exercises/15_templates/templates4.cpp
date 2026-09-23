#include "cpplings_test.hpp"

#include <string>
#include <type_traits>

// Describes a value depending on its type.
template <typename T>
std::string describe(const T& value) {
    // TODO: Fix the compiler errors. A normal `if` still compiles every branch,
    // even the ones that can't be taken for `T`. `std::to_string` doesn't accept
    // a `std::string`, for example.
    if (std::is_integral_v<T>) {
        return "integer " + std::to_string(value);
    } else if (std::is_floating_point_v<T>) {
        return "floating-point number";
    } else if (std::is_same_v<T, std::string>) {
        return "text \"" + value + "\"";
    } else {
        return "something else";
    }
}

struct Point {
    int x;
    int y;
};

TEST(describes_integers) {
    CHECK_EQ(describe(42), "integer 42");
    CHECK_EQ(describe(7L), "integer 7");
}

TEST(describes_floating_point_numbers) {
    CHECK_EQ(describe(1.5), "floating-point number");
}

TEST(describes_text) {
    CHECK_EQ(describe(std::string("hi")), "text \"hi\"");
}

TEST(describes_other_things) {
    CHECK_EQ(describe(Point{1, 2}), "something else");
}
