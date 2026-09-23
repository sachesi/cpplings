#include "cpplings_test.hpp"

// TODO: The macro gives wrong results. Find out what the preprocessor turns
// `SQUARE(1 + 2)` into, then fix the macro.
#define SQUARE(x) x * x

TEST(square_of_a_number) {
    CHECK_EQ(SQUARE(3), 9);
}

TEST(square_of_a_sum) {
    CHECK_EQ(SQUARE(1 + 2), 9);
}

TEST(half_of_a_square) {
    CHECK_EQ(SQUARE(4) / SQUARE(2), 4);
}
