// This exercise is compiled with warnings treated as errors.

#include "cpplings_test.hpp"

#include <string_view>

enum class Direction { North, East, South, West };

// TODO: Fix the compiler errors by handling every direction.
std::string_view to_string(Direction direction) {
    switch (direction) {
    case Direction::North:
        return "north";
    case Direction::East:
        return "east";
    case Direction::South:
        return "south";
    }
}

Direction turn_right(Direction direction) {
    // TODO: Return the direction after turning right by 90 degrees.
    return direction;
}

TEST(names) {
    CHECK_EQ(to_string(Direction::North), "north");
    CHECK_EQ(to_string(Direction::West), "west");
}

TEST(turning_right) {
    CHECK_EQ(to_string(turn_right(Direction::North)), "east");
    CHECK_EQ(to_string(turn_right(Direction::East)), "south");
    CHECK_EQ(to_string(turn_right(Direction::South)), "west");
    CHECK_EQ(to_string(turn_right(Direction::West)), "north");
}
