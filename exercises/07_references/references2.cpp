#include "cpplings_test.hpp"

#include <string>

// TODO: Fix the compiler error by changing only the function signature. The
// function should still not copy the string.
int count_vowels(std::string& text) {
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
