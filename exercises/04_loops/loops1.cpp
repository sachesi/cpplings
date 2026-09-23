#include "cpplings_test.hpp"

// Counts the steps it takes to reach 1 when an even `n` is halved and an odd
// `n` is replaced by `3 * n + 1`.
int steps_to_one(int n) {
    int steps = 0;
    // TODO: Use a `while` loop that repeats as long as `n` isn't 1. In every
    // iteration, change `n` as described above and count the step.
    return steps;
}

// Don't change the tests!
TEST(already_one) {
    CHECK_EQ(steps_to_one(1), 0);
}

TEST(powers_of_two) {
    CHECK_EQ(steps_to_one(2), 1);
    CHECK_EQ(steps_to_one(16), 4);
}

TEST(odd_numbers_on_the_way) {
    CHECK_EQ(steps_to_one(6), 8);
    CHECK_EQ(steps_to_one(27), 111);
}
