#include "cpplings_test.hpp"

bool is_vowel(char letter) {
    // TODO: Only 'a' is recognized. Several `case` labels can share the same
    // statements. Handle the other vowels, lowercase and uppercase.
    switch (letter) {
    case 'a':
        return true;
    default:
        return false;
    }
}

// Don't change the tests!
TEST(lowercase_vowels) {
    CHECK(is_vowel('a'));
    CHECK(is_vowel('e'));
    CHECK(is_vowel('i'));
    CHECK(is_vowel('o'));
    CHECK(is_vowel('u'));
}

TEST(uppercase_vowels) {
    CHECK(is_vowel('A'));
    CHECK(is_vowel('E'));
    CHECK(is_vowel('U'));
}

TEST(consonants_and_others) {
    CHECK(!is_vowel('b'));
    CHECK(!is_vowel('Z'));
    CHECK(!is_vowel('?'));
}
