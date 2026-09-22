#include "cpplings_test.hpp"

#include <string_view>

// TODO: Fix the compiler error on this function.
std::string_view picky_eater(std::string_view food) {
    if (food == "strawberry") {
        return "Yummy!";
    } else {
        return 1;
    }
}

// TODO: Read the tests to understand the desired behavior. Make all tests pass
// without changing them.
TEST(yummy_food) {
    // This means that calling `picky_eater` with the argument "strawberry" should
    // return "Yummy!".
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
