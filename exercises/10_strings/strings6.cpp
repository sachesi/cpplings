#include "cpplings_test.hpp"

#include <string_view>
#include <utility>

// Splits a line like "volume=11" at the first '=' into a key and a value. A line
// without '=' is a key with an empty value.
std::pair<std::string_view, std::string_view> split_setting(std::string_view line) {
    // TODO: Use `find` to locate the '=' and `substr` to cut out the two parts.
    // `find` returns `std::string_view::npos` when there is no '='.
    return {line, ""};
}

TEST(key_and_value) {
    auto [key, value] = split_setting("volume=11");
    CHECK_EQ(key, "volume");
    CHECK_EQ(value, "11");
}

TEST(value_containing_equals_sign) {
    auto [key, value] = split_setting("formula=a=b");
    CHECK_EQ(key, "formula");
    CHECK_EQ(value, "a=b");
}

TEST(only_a_key) {
    auto [key, value] = split_setting("verbose");
    CHECK_EQ(key, "verbose");
    CHECK_EQ(value, "");
}

TEST(empty_key) {
    auto [key, value] = split_setting("=x");
    CHECK_EQ(key, "");
    CHECK_EQ(value, "x");
}
