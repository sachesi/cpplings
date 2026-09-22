#include "cpplings_test.hpp"

#include <vector>

std::vector<int> doubled(const std::vector<int>& input) {
    std::vector<int> output;

    for (int element : input) {
        // TODO: Multiply each element in the `input` vector by 2 and append it to
        // the `output` vector.
    }

    return output;
}

void double_in_place(std::vector<int>& numbers) {
    // TODO: This loop doesn't change `numbers`. Why not?
    for (auto element : numbers) {
        element *= 2;
    }
}

TEST(test_doubled) {
    std::vector<int> input = {2, 4, 6, 8, 10};
    std::vector<int> expected = {4, 8, 12, 16, 20};
    CHECK_EQ(doubled(input), expected);
}

TEST(test_double_in_place) {
    std::vector<int> numbers = {2, 4, 6, 8, 10};
    double_in_place(numbers);
    std::vector<int> expected = {4, 8, 12, 16, 20};
    CHECK_EQ(numbers, expected);
}
