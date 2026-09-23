#include "cpplings_test.hpp"

#include <string>
#include <string_view>

std::string trim_me(std::string_view input) {
    // TODO: Remove whitespace (spaces, tabs and newlines) from both ends of a
    // string.
}

std::string compose_me(std::string_view input) {
    // TODO: Add " world!" to the string!
}

std::string replace_me(std::string_view input) {
    // TODO: Replace all occurrences of "cars" in the input with "balloons".
}

TEST(trim_a_string) {
    CHECK_EQ(trim_me("Hello!     "), "Hello!");
    CHECK_EQ(trim_me("  What's up!"), "What's up!");
    CHECK_EQ(trim_me("   Hola!  "), "Hola!");
    CHECK_EQ(trim_me("\t Hi!\n"), "Hi!");
    CHECK_EQ(trim_me("    "), "");
}

TEST(compose_a_string) {
    CHECK_EQ(compose_me("Hello"), "Hello world!");
    CHECK_EQ(compose_me("Goodbye"), "Goodbye world!");
}

TEST(replace_a_string) {
    CHECK_EQ(replace_me("I think cars are cool"), "I think balloons are cool");
    CHECK_EQ(replace_me("I love to look at cars"), "I love to look at balloons");
    CHECK_EQ(replace_me("cars, cars, cars!"), "balloons, balloons, balloons!");
}
