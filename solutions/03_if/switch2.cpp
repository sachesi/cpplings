#include "cpplings_test.hpp"

bool is_vowel(char letter) {
    switch (letter) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
        return true;
    default:
        return false;
    }
}

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
