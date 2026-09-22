#include "cpplings_test.hpp"

int bigger(int a, int b) {
    // TODO: Complete this function to return the bigger number!
    // If both numbers are equal, any of them can be returned.
    // Do not use:
    // - `std::max`
    // - the conditional operator `? :`
}

// Don't change the tests!
TEST(ten_is_bigger_than_eight) {
    CHECK_EQ(bigger(10, 8), 10);
}

TEST(fortytwo_is_bigger_than_thirtytwo) {
    CHECK_EQ(bigger(32, 42), 42);
}

TEST(equal_numbers) {
    CHECK_EQ(bigger(42, 42), 42);
}
