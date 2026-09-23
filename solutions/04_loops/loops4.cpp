#include "cpplings_test.hpp"

int smallest_divisor(int n) {
    int divisor = n;
    for (int candidate = 2; candidate < n; ++candidate) {
        if (n % candidate == 0) {
            divisor = candidate;
            break;
        }
    }
    return divisor;
}

int sum_skipping_threes(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0) {
            continue;
        }
        sum += i;
    }
    return sum;
}

TEST(smallest_divisors) {
    CHECK_EQ(smallest_divisor(12), 2);
    CHECK_EQ(smallest_divisor(35), 5);
    CHECK_EQ(smallest_divisor(13), 13);
}

TEST(skipping_threes) {
    CHECK_EQ(sum_skipping_threes(2), 3);
    CHECK_EQ(sum_skipping_threes(7), 19);
}
