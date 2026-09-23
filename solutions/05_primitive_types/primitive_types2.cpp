#include "cpplings_test.hpp"

char to_upper(char letter) {
    if (letter >= 'a' && letter <= 'z') {
        // The arithmetic happens on `int`, so the result is converted back.
        return static_cast<char>(letter - 'a' + 'A');
    }
    return letter;
}

TEST(lowercase_letters) {
    CHECK_EQ(to_upper('a'), 'A');
    CHECK_EQ(to_upper('m'), 'M');
    CHECK_EQ(to_upper('z'), 'Z');
}

TEST(other_characters) {
    CHECK_EQ(to_upper('Q'), 'Q');
    CHECK_EQ(to_upper('7'), '7');
    CHECK_EQ(to_upper('{'), '{');
}
