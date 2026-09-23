#include "cpplings_test.hpp"

// Every use of the parameter and the whole expansion need parentheses. A
// `constexpr` function doesn't have this problem at all:
// constexpr int square(int x) { return x * x; }
#define SQUARE(x) ((x) * (x))

TEST(square_of_a_number) {
    CHECK_EQ(SQUARE(3), 9);
}

TEST(square_of_a_sum) {
    CHECK_EQ(SQUARE(1 + 2), 9);
}

TEST(half_of_a_square) {
    CHECK_EQ(SQUARE(4) / SQUARE(2), 4);
}
