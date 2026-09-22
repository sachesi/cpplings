// The warnings of this exercise are treated as errors.

#include "cpplings_test.hpp"

#include <vector>

// Counts the values that are greater than `threshold`.
// TODO: Fix the compiler error.
int count_above(const std::vector<int>& values, int threshold) {
    int count = 0;
    for (int i = 0; i < values.size(); ++i) {
        if (values[i] > threshold) {
            ++count;
        }
    }
    return count;
}

TEST(counts_values_above_the_threshold) {
    CHECK_EQ(count_above({1, 5, 10, 15}, 5), 2);
    CHECK_EQ(count_above({}, 0), 0);
}
