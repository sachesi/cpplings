#include "cpplings_test.hpp"

int sum_of_squares(int n) {
    int sum = 0;
    // The loop runs for every `i` from 1 up to and including `n`.
    for (int i = 1; i <= n; ++i) {
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
