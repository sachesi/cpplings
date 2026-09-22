#include "cpplings_test.hpp"

#include <string>

std::string light_meaning(int light) {
    std::string meaning;
    // Without `break`, execution continues with the next case ("falls through").
    switch (light) {
    case 0:
        meaning = "stop";
        break;
    case 1:
        meaning = "slow down";
        break;
    case 2:
        meaning = "go";
        break;
    default:
        meaning = "broken";
    }
    return meaning;
}

TEST(red_means_stop) {
    CHECK_EQ(light_meaning(0), "stop");
}

TEST(yellow_means_slow_down) {
    CHECK_EQ(light_meaning(1), "slow down");
}

TEST(green_means_go) {
    CHECK_EQ(light_meaning(2), "go");
}

TEST(anything_else_is_broken) {
    CHECK_EQ(light_meaning(7), "broken");
}
