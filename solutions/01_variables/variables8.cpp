#include "cpplings_test.hpp"

TEST(swapping_two_variables) {
    int left = 1;
    int right = 2;

    // The first assignment overwrites `left`, so its value is saved beforehand.
    int saved = left;
    left = right;
    right = saved;

    CHECK_EQ(left, 2);
    CHECK_EQ(right, 1);
}
