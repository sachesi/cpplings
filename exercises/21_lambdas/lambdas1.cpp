#include "cpplings_test.hpp"

#include <string>

TEST(square) {
    // TODO: Define `square` as a lambda that returns its argument multiplied by
    // itself.
    auto square = ???;

    CHECK_EQ(square(4), 16);
    CHECK_EQ(square(-3), 9);
}

TEST(capturing) {
    std::size_t limit = 5;

    // TODO: Define a lambda that checks whether a string has more characters
    // than `limit`. It needs to capture `limit`.
    auto is_too_long = ???;

    CHECK(is_too_long(std::string("cpplings")));
    CHECK(!is_too_long(std::string("c++")));
}
