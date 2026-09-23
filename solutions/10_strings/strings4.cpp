#include "cpplings_test.hpp"

#include <format>
#include <string>
#include <string_view>

std::string format_price(double price) {
    return std::format("${:.2f}", price);
}

std::string format_row(std::string_view name, int quantity) {
    return std::format("{:<10}{:>4}", name, quantity);
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
