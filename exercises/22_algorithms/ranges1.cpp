#include "cpplings_test.hpp"

#include <cctype>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

// "hello" -> "Hello"
std::string capitalize_first(std::string_view input) {
    if (input.empty()) {
        return "";
    }
    // TODO: Return the first character in uppercase followed by the rest.
    // `std::toupper` expects an `unsigned char` value and returns an `int`.
    return std::string(input);
}

// Applies `capitalize_first` to every word.
// ["hello", "world"] -> ["Hello", "World"]
std::vector<std::string> capitalize_words_vector(const std::vector<std::string>& words) {
    // TODO: Use `std::views::transform` and collect the result with
    // `std::ranges::to<std::vector>()`.
    return {};
}

// Applies `capitalize_first` to every word and joins them.
// ["hello", " ", "world"] -> "Hello World"
std::string capitalize_words_string(const std::vector<std::string>& words) {
    // TODO: Like above, but join the words with `std::views::join` and collect
    // the characters into a `std::string`.
    return {};
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
