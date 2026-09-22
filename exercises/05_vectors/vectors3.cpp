#include "cpplings_test.hpp"

#include <cstddef>
#include <vector>

// TODO: This function reads past the end of the vector, which is undefined
// behavior. The checked standard library catches it. Fix the loop.
int sum(const std::vector<int>& numbers) {
    int total = 0;
    for (std::size_t i = 0; i <= numbers.size(); ++i) {
        total += numbers[i];
    }
    return total;
}

TEST(sum_of_numbers) {
    CHECK_EQ(sum({1, 2, 3, 4}), 10);
}

TEST(sum_of_nothing) {
    CHECK_EQ(sum({}), 0);
}
