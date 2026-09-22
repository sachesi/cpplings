#include "cpplings_test.hpp"

#include <cctype>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

std::string capitalize_first(std::string_view input) {
    if (input.empty()) {
        return "";
    }
    char first = static_cast<char>(std::toupper(static_cast<unsigned char>(input.front())));
    return first + std::string(input.substr(1));
}

std::vector<std::string> capitalize_words_vector(const std::vector<std::string>& words) {
    return words | std::views::transform(capitalize_first) | std::ranges::to<std::vector>();
}

std::string capitalize_words_string(const std::vector<std::string>& words) {
    return words | std::views::transform(capitalize_first) | std::views::join | std::ranges::to<std::string>();
}

TEST(success) {
    CHECK_EQ(capitalize_first("hello"), "Hello");
}

TEST(empty) {
    CHECK_EQ(capitalize_first(""), "");
}

TEST(iterate_string_vec) {
    std::vector<std::string> words = {"hello", "world"};
    CHECK_EQ(capitalize_words_vector(words), (std::vector<std::string>{"Hello", "World"}));
}

TEST(iterate_into_string) {
    std::vector<std::string> words = {"hello", " ", "world"};
    CHECK_EQ(capitalize_words_string(words), "Hello World");
}
