#include "cpplings_test.hpp"

unsigned int power_of_2(unsigned int n) {
    return 1u << n;
}

TEST(you_can_check_eq) {
    CHECK_EQ(power_of_2(0), 1u);
    CHECK_EQ(power_of_2(1), 2u);
    CHECK_EQ(power_of_2(2), 4u);
    CHECK_EQ(power_of_2(3), 8u);
}
