#include "cpplings_test.hpp"

#include <string>
#include <string_view>

std::string greeting(std::string_view name, std::string_view punctuation = "!") {
    std::string text = "Hello, ";
    text += name;
    text += punctuation;
    return text;
}

TEST(default_punctuation) {
    CHECK_EQ(greeting("Ferris"), "Hello, Ferris!");
}

TEST(custom_punctuation) {
    CHECK_EQ(greeting("Bjarne", "?"), "Hello, Bjarne?");
}
