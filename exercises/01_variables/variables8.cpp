#include "cpplings_test.hpp"

TEST(swapping_two_variables) {
    int left = 1;
    int right = 2;

    // TODO: After these two lines, both variables hold the same value. Swap the
    // values with the help of a third variable. Don't use `std::swap`.
    left = right;
    right = left;

    CHECK_EQ(left, 2);
    CHECK_EQ(right, 1);
}
