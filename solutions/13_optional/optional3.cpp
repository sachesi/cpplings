#include "cpplings_test.hpp"

#include <charconv>
#include <optional>
#include <string>
#include <string_view>

std::optional<int> parse_int(std::string_view text) {
    int value = 0;
    auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), value);
    if (error != std::errc{} || end != text.data() + text.size()) {
        return std::nullopt;
    }
    return value;
}

std::optional<int> half(int number) {
    if (number % 2 != 0) {
        return std::nullopt;
    }
    return number / 2;
}

std::optional<std::string> describe_half(std::string_view text) {
    return parse_int(text).and_then(half).transform([](int n) { return "half is " + std::to_string(n); });
}

TEST(even_number) {
    CHECK_EQ(describe_half("10"), "half is 5");
    CHECK_EQ(describe_half("-4"), "half is -2");
}

TEST(odd_number) {
    CHECK_EQ(describe_half("7"), std::nullopt);
}

TEST(not_a_number) {
    CHECK_EQ(describe_half("ten"), std::nullopt);
    CHECK_EQ(describe_half("10 apples"), std::nullopt);
}
