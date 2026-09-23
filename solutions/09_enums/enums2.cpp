#include "cpplings_test.hpp"

#include <string_view>
#include <utility>

enum class Direction { North, East, South, West };

std::string_view to_string(Direction direction) {
    switch (direction) {
    case Direction::North:
        return "north";
    case Direction::East:
        return "east";
    case Direction::South:
        return "south";
    case Direction::West:
        return "west";
    }
    // An enum object can hold values without a name, e.g. from a cast. Marks
    // this line as impossible to reach.
    std::unreachable();
}

Direction turn_right(Direction direction) {
    switch (direction) {
    case Direction::North:
        return Direction::East;
    case Direction::East:
        return Direction::South;
    case Direction::South:
        return Direction::West;
    case Direction::West:
        return Direction::North;
    }
    std::unreachable();
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
