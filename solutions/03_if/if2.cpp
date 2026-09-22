#include "cpplings_test.hpp"

#include <string_view>

std::string_view picky_eater(std::string_view food) {
    if (food == "strawberry") {
        return "Yummy!";
    } else if (food == "potato") {
        return "I guess I can eat that.";
    } else {
        return "No thanks!";
    }
}

TEST(yummy_food) {
    CHECK_EQ(picky_eater("strawberry"), "Yummy!");
}

TEST(neutral_food) {
    CHECK_EQ(picky_eater("potato"), "I guess I can eat that.");
}

TEST(default_disliked_food) {
    CHECK_EQ(picky_eater("broccoli"), "No thanks!");
    CHECK_EQ(picky_eater("gummy bears"), "No thanks!");
    CHECK_EQ(picky_eater("literally anything"), "No thanks!");
}
