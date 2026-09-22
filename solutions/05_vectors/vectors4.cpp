#include "cpplings_test.hpp"

#include <cstddef>
#include <vector>

void append_doubles(std::vector<int>& numbers) {
    // Indices stay valid when the vector reallocates. The size is read once, so
    // the new elements aren't visited.
    const std::size_t original_size = numbers.size();
    for (std::size_t i = 0; i < original_size; ++i) {
        numbers.push_back(numbers[i] * 2);
    }
}

TEST(appends_doubles) {
    std::vector<int> numbers = {1, 2, 3};
    append_doubles(numbers);
    std::vector<int> expected = {1, 2, 3, 2, 4, 6};
    CHECK_EQ(numbers, expected);
}

TEST(empty_stays_empty) {
    std::vector<int> numbers;
    append_doubles(numbers);
    CHECK(numbers.empty());
}
