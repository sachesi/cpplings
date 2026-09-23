#include "cpplings_test.hpp"

#include <vector>

std::vector<int> squares(int count) {
    std::vector<int> result;
    result.reserve(count);
    // TODO: The checked standard library stops the program in this loop. Find out
    // what `reserve` does, then fix the loop. Keep the call to `reserve`.
    for (int i = 0; i < count; ++i) {
        result[i] = i * i;
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
