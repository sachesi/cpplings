// The warnings of this exercise are treated as errors.

#include "cpplings_test.hpp"

#include <cmath>

// Applies a discount in percent and rounds to the nearest cent.
// TODO: Fix the compiler error. The conversion is intended here, but it should
// round instead of cutting off the fractional part, and it should be explicit.
long apply_discount(long price_in_cents, double percent) {
    return price_in_cents * (1.0 - percent / 100.0);
}

TEST(discounts) {
    CHECK_EQ(apply_discount(1000, 10.0), 900);
    CHECK_EQ(apply_discount(199, 15.0), 169);
    CHECK_EQ(apply_discount(999, 33.0), 669);
    CHECK_EQ(apply_discount(1995, 10.0), 1796);
}
