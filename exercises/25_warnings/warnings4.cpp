// The warnings of this exercise are treated as errors.

#include "cpplings_test.hpp"

#include <string>

// TODO: Fix the compiler error. The compiler suggests a way to silence the
// warning, but that's not the right fix here.
std::string stock_status(int stock) {
    if (stock = 0) {
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
