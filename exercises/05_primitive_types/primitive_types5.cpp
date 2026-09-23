// Unsigned integers

#include "cpplings_test.hpp"

// TODO: The last test fails. Why? Read the compiler warning, then fix the function.
bool can_afford(unsigned int balance, unsigned int price) {
    return balance - price >= 0;
}

TEST(enough_money) {
    CHECK(can_afford(100, 30));
}

TEST(exactly_enough_money) {
    CHECK(can_afford(30, 30));
}

TEST(not_enough_money) {
    CHECK(!can_afford(20, 30));
}
