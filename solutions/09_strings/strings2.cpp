#include "cpplings_test.hpp"

#include <string>
#include <string_view>

// Comparing two `const char*` compares the addresses. `std::string_view`
// compares the characters.
bool is_a_color_word(std::string_view word) {
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
