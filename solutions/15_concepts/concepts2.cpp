#include "cpplings_test.hpp"

#include <concepts>

template <std::integral T>
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

template <typename T>
concept HasGcd = requires(T a, T b) { gcd(a, b); };

TEST(no_floating_point_numbers) {
    static_assert(HasGcd<int>);
    static_assert(!HasGcd<double>);
}
