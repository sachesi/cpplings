#include "cpplings_test.hpp"

#include <string>

std::string stock_status(int stock) {
    // `=` assigns, `==` compares.
    if (stock == 0) {
        return "sold out";
    }
    if (stock < 10) {
        return "only a few left";
    }
    return "in stock";
}

TEST(status) {
    CHECK_EQ(stock_status(0), "sold out");
    CHECK_EQ(stock_status(3), "only a few left");
    CHECK_EQ(stock_status(50), "in stock");
}
