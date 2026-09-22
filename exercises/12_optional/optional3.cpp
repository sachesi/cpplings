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

// Parses the text, halves the number and describes the result, e.g. "10"
// becomes "half is 5". Returns nothing if the text isn't a number or the number
// is odd.
std::optional<std::string> describe_half(std::string_view text) {
    // TODO: Implement this without `if` statements, by chaining the steps with
    // the member functions `and_then` and `transform` of `std::optional`:
    // - `and_then(f)` calls `f` with the value; `f` returns an optional itself.
    // - `transform(f)` calls `f` with the value and wraps the result.
    // Both return an empty optional if there's no value to call `f` with.
    return std::nullopt;
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
