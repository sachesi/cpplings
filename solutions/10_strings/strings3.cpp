#include "cpplings_test.hpp"

#include <string>
#include <string_view>

std::string trim_me(std::string_view input) {
    constexpr std::string_view whitespace = " \t\n\r";
    std::size_t first = input.find_first_not_of(whitespace);
    if (first == std::string_view::npos) {
        return "";
    }
    std::size_t last = input.find_last_not_of(whitespace);
    return std::string(input.substr(first, last - first + 1));
}

std::string compose_me(std::string_view input) {
    return std::string(input) + " world!";
}

std::string replace_me(std::string_view input) {
    std::string result(input);
    constexpr std::string_view from = "cars";
    constexpr std::string_view to = "balloons";
    for (std::size_t pos = result.find(from); pos != std::string::npos; pos = result.find(from, pos + to.size())) {
        result.replace(pos, from.size(), to);
    }
    return result;
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
