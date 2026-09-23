#include "cpplings_test.hpp"

#include <vector>

std::vector<int> squares(int count) {
    std::vector<int> result;
    // `reserve` allocates memory for the elements, but the vector stays empty.
    result.reserve(count);
    for (int i = 0; i < count; ++i) {
        result.push_back(i * i);
    }
    return result;
}

TEST(some_squares) {
    std::vector<int> expected = {0, 1, 4, 9};
    CHECK_EQ(squares(4), expected);
}

TEST(no_squares) {
    CHECK(squares(0).empty());
}
