#include "cpplings_test.hpp"

#include <cstddef>
#include <vector>

int sum(const std::vector<int>& numbers) {
    int total = 0;
    // Valid indices go from 0 to size() - 1.
    for (std::size_t i = 0; i < numbers.size(); ++i) {
        total += numbers[i];
    }
    // A range-based for loop avoids indices altogether:
    // for (int number : numbers) { total += number; }
    return total;
}

TEST(sum_of_numbers) {
    CHECK_EQ(sum({1, 2, 3, 4}), 10);
}

TEST(sum_of_nothing) {
    CHECK_EQ(sum({}), 0);
}
