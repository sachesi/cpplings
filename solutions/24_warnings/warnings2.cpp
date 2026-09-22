#include "cpplings_test.hpp"

#include <cmath>

long apply_discount(long price_in_cents, double percent) {
    // `std::lround` rounds to the nearest integer and returns a `long`. The
    // conversion of the price to `double` is written out as well.
    return std::lround(static_cast<double>(price_in_cents) * (1.0 - percent / 100.0));
}

TEST(discounts) {
    CHECK_EQ(apply_discount(1000, 10.0), 900);
    CHECK_EQ(apply_discount(199, 15.0), 169);
    CHECK_EQ(apply_discount(999, 33.0), 669);
    CHECK_EQ(apply_discount(1995, 10.0), 1796);
}
