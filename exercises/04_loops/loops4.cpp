#include "cpplings_test.hpp"

// The divisor of `n` that is greater than 1 and as small as possible.
int smallest_divisor(int n) {
    int divisor = n;
    for (int candidate = 2; candidate < n; ++candidate) {
        if (n % candidate == 0) {
            divisor = candidate;
            // TODO: The loop keeps going and finds bigger divisors. Stop it here.
        }
    }
    return divisor;
}

// The sum of all numbers from 1 to `n` that aren't divisible by 3.
int sum_skipping_threes(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0) {
            // TODO: Skip the rest of this iteration.
        }
        sum += i;
    }
    return sum;
}

// Don't change the tests!
TEST(smallest_divisors) {
    CHECK_EQ(smallest_divisor(12), 2);
    CHECK_EQ(smallest_divisor(35), 5);
    CHECK_EQ(smallest_divisor(13), 13);
}

TEST(skipping_threes) {
    CHECK_EQ(sum_skipping_threes(2), 3);
    CHECK_EQ(sum_skipping_threes(7), 19);
}
