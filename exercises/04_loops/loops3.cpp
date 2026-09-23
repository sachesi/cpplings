#include "cpplings_test.hpp"

// Returns 1*1 + 2*2 + ... + n*n.
int sum_of_squares(int n) {
    int sum = 0;
    // TODO: The tests fail. Check the first and the last iteration of the loop.
    for (int i = 1; i < n; ++i) {
        sum += i * i;
    }
    return sum;
}

TEST(one_square) {
    CHECK_EQ(sum_of_squares(1), 1);
}

TEST(several_squares) {
    CHECK_EQ(sum_of_squares(3), 14);
    CHECK_EQ(sum_of_squares(10), 385);
}

TEST(no_squares) {
    CHECK_EQ(sum_of_squares(0), 0);
}
