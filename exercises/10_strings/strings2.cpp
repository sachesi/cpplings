#include "cpplings_test.hpp"

#include <string>

// TODO: The test fails although "green" is a color. Read the compiler warning,
// then fix the function by changing its parameter type.
bool is_a_color_word(const char* word) {
    return word == "green" || word == "blue" || word == "red";
}

TEST(recognizes_colors) {
    std::string input = "green";
    CHECK(is_a_color_word(input.c_str()));
}

TEST(rejects_other_words) {
    std::string input = "grass";
    CHECK(!is_a_color_word(input.c_str()));
}
