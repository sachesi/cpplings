#include "cpplings_test.hpp"

#include <optional>

std::optional<int> maybe_ice_cream(int hour_of_day) {
    if (hour_of_day < 22) {
        return 5;
    }
    if (hour_of_day < 24) {
        return 0;
    }
    return std::nullopt;
}

TEST(raw_value) {
    // `value()` throws `std::bad_optional_access` if there is no value.
    int ice_creams = maybe_ice_cream(12).value();

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
