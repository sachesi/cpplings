#include "cpplings_test.hpp"

#include <optional>

// This function returns how much ice cream there is left in the fridge.
// If it's before 22:00 (24-hour system), then 5 scoops are left. At 22:00,
// someone eats it all, so no ice cream is left (value 0). Return `std::nullopt`
// if `hour_of_day` is higher than 23.
std::optional<int> maybe_ice_cream(int hour_of_day) {
    // TODO: Complete the function body.
}

TEST(raw_value) {
    // TODO: Fix this test. How do you get the value contained in the optional?
    int ice_creams = maybe_ice_cream(12);

    CHECK_EQ(ice_creams, 5);
}

TEST(check_ice_cream) {
    CHECK_EQ(maybe_ice_cream(0), 5);
    CHECK_EQ(maybe_ice_cream(9), 5);
    CHECK_EQ(maybe_ice_cream(18), 5);
    CHECK_EQ(maybe_ice_cream(22), 0);
    CHECK_EQ(maybe_ice_cream(23), 0);
    CHECK_EQ(maybe_ice_cream(24), std::nullopt);
    CHECK_EQ(maybe_ice_cream(25), std::nullopt);
}
