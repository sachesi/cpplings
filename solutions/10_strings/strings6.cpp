#include "cpplings_test.hpp"

#include <cstddef>
#include <string_view>
#include <utility>

std::pair<std::string_view, std::string_view> split_setting(std::string_view line) {
    std::size_t equals = line.find('=');
    if (equals == std::string_view::npos) {
        return {line, ""};
    }
    return {line.substr(0, equals), line.substr(equals + 1)};
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
