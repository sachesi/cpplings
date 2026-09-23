#include "cpplings_test.hpp"

#include <string>
#include <string_view>

// TODO: The returned view points to the characters of `text`, which is destroyed
// when the function returns. Fix the function by changing its return type.
std::string_view welcome(std::string_view name) {
    std::string text = "Welcome back to the workshop, ";
    text += name;
    return text;
}

TEST(welcome_message) {
    CHECK_EQ(welcome("Ferris"), "Welcome back to the workshop, Ferris");
}
