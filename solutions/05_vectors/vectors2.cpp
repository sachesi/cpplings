#include "cpplings_test.hpp"

#include <vector>

std::vector<int> doubled(const std::vector<int>& input) {
    std::vector<int> output;
    // Allocating once up front avoids repeated growth.
    output.reserve(input.size());

    for (int element : input) {
        output.push_back(element * 2);
    }

    return output;
}

void double_in_place(std::vector<int>& numbers) {
    // `auto&` refers to the element itself instead of a copy of it.
    for (auto& element : numbers) {
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
