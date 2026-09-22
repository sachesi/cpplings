// Calculates the power of 2 using a bit shift.
// `1 << n` is equivalent to "2 to the power of n".

#include "cpplings_test.hpp"

unsigned int power_of_2(unsigned int n) {
    return 1u << n;
}

TEST(you_can_check_eq) {
    // TODO: Test the function `power_of_2` with some values.
    CHECK_EQ(???, ???);
    CHECK_EQ(???, ???);
    CHECK_EQ(???, ???);
    CHECK_EQ(???, ???);
}
