#include "cpplings_test.hpp"

#include <string>

// A non-const reference can't bind to a temporary like the string created from
// "pointer". A const reference can. `std::string_view` would work as well.
int count_vowels(const std::string& text) {
    int count = 0;
    for (char c : text) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            ++count;
        }
    }
    return count;
}

TEST(vowels_in_a_variable) {
    std::string word = "reference";
    CHECK_EQ(count_vowels(word), 4);
}

TEST(vowels_in_a_temporary) {
    CHECK_EQ(count_vowels("pointer"), 3);
}
