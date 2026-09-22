#include "cpplings_test.hpp"

#include <format>
#include <string>
#include <string_view>

// TODO: Implement the functions with `std::format`. The format specification
// after the `:` inside the braces controls alignment, width and precision:
// https://en.cppreference.com/w/cpp/utility/format/spec

// Formats the price with a dollar sign and exactly two decimal places.
std::string format_price(double price) {
    return std::to_string(price);
}

// The name is left-aligned in a column of 10 characters and the quantity is
// right-aligned in a column of 4 characters.
std::string format_row(std::string_view name, int quantity) {
    return std::string(name) + " " + std::to_string(quantity);
}

TEST(prices) {
    CHECK_EQ(format_price(12.5), "$12.50");
    CHECK_EQ(format_price(0.999), "$1.00");
    CHECK_EQ(format_price(3.0), "$3.00");
}

TEST(rows) {
    CHECK_EQ(format_row("apple", 3), "apple        3");
    CHECK_EQ(format_row("watermelon", 1024), "watermelon1024");
}
