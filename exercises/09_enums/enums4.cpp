#include "cpplings_test.hpp"

#include <cstdint>
#include <utility>

// The values are sent over the network as single bytes.
enum class Priority : std::uint8_t {
    Low = 1,
    Normal = 5,
    Urgent = 10,
};

// TODO: An `enum class` doesn't convert to an integer implicitly. Fix the
// compiler error.
int to_byte(Priority priority) {
    return priority;
}

TEST(priorities_as_bytes) {
    CHECK_EQ(to_byte(Priority::Low), 1);
    CHECK_EQ(to_byte(Priority::Normal), 5);
    CHECK_EQ(to_byte(Priority::Urgent), 10);
}

TEST(size_of_priority) {
    // TODO: How many bytes does a `Priority` take? Replace the 0.
    CHECK_EQ(sizeof(Priority), 0);
}
