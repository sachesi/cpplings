#include "cpplings_test.hpp"

#include <vector>

// A range-based for loop avoids mixing the signed `int` with the unsigned
// `size()`. `std::ranges::count_if` would be another option.
int count_above(const std::vector<int>& values, int threshold) {
    int count = 0;
    for (int value : values) {
        if (value > threshold) {
            ++count;
        }
    }
    return count;
}

TEST(counts_values_above_the_threshold) {
    CHECK_EQ(count_above({1, 5, 10, 15}, 5), 2);
    CHECK_EQ(count_above({}, 0), 0);
}
