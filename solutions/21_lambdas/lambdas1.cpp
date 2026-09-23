#include "cpplings_test.hpp"

#include <string>

TEST(square) {
    auto square = [](int n) { return n * n; };

    CHECK_EQ(square(4), 16);
    CHECK_EQ(square(-3), 9);
}

TEST(capturing) {
    std::size_t limit = 5;

    auto is_too_long = [limit](const std::string& text) { return text.size() > limit; };

    CHECK(is_too_long(std::string("cpplings")));
    CHECK(!is_too_long(std::string("c++")));
}
