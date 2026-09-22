#include "cpplings_test.hpp"

#include <string_view>

int animal_habitat(std::string_view animal) {
    // TODO: Fix the compiler error in the statement below. Both alternatives of
    // the conditional operator must have a common type.
    int identifier = animal == "crab"     ? 1
                     : animal == "gopher" ? 2
                     : animal == "snake"  ? 3
                                          : "Unknown";

    // Don't change the expression below!
    if (identifier == 1) {
        return 1; // "Beach"
    }
    if (identifier == 2) {
        return 2; // "Burrow"
    }
    if (identifier == 3) {
        return 3; // "Desert"
    }
    return 0; // "Unknown"
}

// Don't change the tests!
TEST(gopher_lives_in_burrow) {
    CHECK_EQ(animal_habitat("gopher"), 2);
}

TEST(snake_lives_in_desert) {
    CHECK_EQ(animal_habitat("snake"), 3);
}

TEST(crab_lives_on_beach) {
    CHECK_EQ(animal_habitat("crab"), 1);
}

TEST(unknown_animal) {
    CHECK_EQ(animal_habitat("dinosaur"), 0);
}
