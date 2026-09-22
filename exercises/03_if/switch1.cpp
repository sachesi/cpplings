#include "cpplings_test.hpp"

#include <string>

// Returns how a traffic light should be read by drivers.
// 0 = red, 1 = yellow, 2 = green
std::string light_meaning(int light) {
    std::string meaning;
    // TODO: The tests fail although every case is handled. Find out why. The
    // compiler warnings give a clue.
    switch (light) {
    case 0:
        meaning = "stop";
    case 1:
        meaning = "slow down";
    case 2:
        meaning = "go";
        break;
    default:
        meaning = "broken";
    }
    return meaning;
}

// Don't change the tests!
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
