#include "cpplings_test.hpp"

#include <string>

std::string countdown(int from) {
    std::string text;
    for (int i = from; i > 0; --i) {
        text += std::to_string(i);
        text += ' ';
    }
    text += "liftoff!";
    return text;
}

TEST(countdown_from_three) {
    CHECK_EQ(countdown(3), "3 2 1 liftoff!");
}

TEST(countdown_from_one) {
    CHECK_EQ(countdown(1), "1 liftoff!");
}

TEST(nothing_to_count) {
    CHECK_EQ(countdown(0), "liftoff!");
}
