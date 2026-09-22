// Characters (`char`)

#include "cpplings_test.hpp"

// A `char` is a small integer, and the letters 'a' to 'z' as well as 'A' to 'Z'
// have consecutive values.
char to_upper(char letter) {
    // TODO: Return the uppercase version of `letter` if it is a lowercase letter.
    // Return any other character unchanged. Compute it without `std::toupper`.
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
