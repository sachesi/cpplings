#include "cpplings_test.hpp"

#include <concepts>

// The greatest common divisor only makes sense for integers.
// TODO: Constrain the template with a concept from the standard library, so
// that calling it with floating-point numbers doesn't compile.
template <typename T>
T gcd(T a, T b) {
    while (b != 0) {
        T rest = a % b;
        a = b;
        b = rest;
    }
    return a;
}

TEST(integers) {
    CHECK_EQ(gcd(12, 18), 6);
    CHECK_EQ(gcd(17L, 5L), 1L);
}

// A `requires` expression checks whether its content would compile.
template <typename T>
concept HasGcd = requires(T a, T b) { gcd(a, b); };

TEST(no_floating_point_numbers) {
    static_assert(HasGcd<int>);
    static_assert(!HasGcd<double>);
}
