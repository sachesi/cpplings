#include "cpplings_test.hpp"

bool can_afford(unsigned int balance, unsigned int price) {
    // `balance - price` is unsigned too. It can't be negative; it wraps around to a
    // huge number instead. Comparing first avoids the subtraction.
    return balance >= price;
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
