#include "cpplings_test.hpp"

int steps_to_one(int n) {
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        ++steps;
    }
    return steps;
}

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
