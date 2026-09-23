#include "cpplings_test.hpp"

#include <string>

std::string countdown(int from) {
    std::string text;
    // TODO: Replace the `???` so that the loop counts down from `from` to 1.
    for (int i = from; ???; ???) {
        text += std::to_string(i);
        text += ' ';
    }
    text += "liftoff!";
    return text;
}

// Don't change the tests!
TEST(countdown_from_three) {
    CHECK_EQ(countdown(3), "3 2 1 liftoff!");
}

TEST(countdown_from_one) {
    CHECK_EQ(countdown(1), "1 liftoff!");
}

TEST(nothing_to_count) {
    CHECK_EQ(countdown(0), "liftoff!");
}
