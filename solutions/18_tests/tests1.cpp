#include "cpplings_test.hpp"

bool is_even(int n) {
    return n % 2 == 0;
}

TEST(you_can_check) {
    CHECK(is_even(0));
    CHECK(!is_even(-1));
    // Some checks for the opposite case would be good too.
}
