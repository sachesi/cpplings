#include "cpplings_test.hpp"

#include <string>
#include <string_view>

// The caller receives its own `std::string` that owns the characters.
std::string welcome(std::string_view name) {
    std::string text = "Welcome back to the workshop, ";
    text += name;
    return text;
}

TEST(welcome_message) {
    CHECK_EQ(welcome("Ferris"), "Welcome back to the workshop, Ferris");
}
