#include "cpplings_test.hpp"

#include <string>
#include <string_view>

// TODO: Most callers want an exclamation mark. Give `punctuation` the default
// value "!" so that it can be left out.
std::string greeting(std::string_view name, std::string_view punctuation) {
    std::string text = "Hello, ";
    text += name;
    text += punctuation;
    return text;
}

// Don't change the tests!
TEST(default_punctuation) {
    CHECK_EQ(greeting("Ferris"), "Hello, Ferris!");
}

TEST(custom_punctuation) {
    CHECK_EQ(greeting("Bjarne", "?"), "Hello, Bjarne?");
}
