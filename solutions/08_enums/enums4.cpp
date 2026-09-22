#include "cpplings_test.hpp"

#include <cstdint>
#include <utility>

enum class Priority : std::uint8_t {
    Low = 1,
    Normal = 5,
    Urgent = 10,
};

int to_byte(Priority priority) {
    // Or `static_cast<int>(priority)`.
    return std::to_underlying(priority);
}

TEST(priorities_as_bytes) {
    CHECK_EQ(to_byte(Priority::Low), 1);
    CHECK_EQ(to_byte(Priority::Normal), 5);
    CHECK_EQ(to_byte(Priority::Urgent), 10);
}

TEST(size_of_priority) {
    // The same size as its underlying type `std::uint8_t`.
    CHECK_EQ(sizeof(Priority), 1);
}
