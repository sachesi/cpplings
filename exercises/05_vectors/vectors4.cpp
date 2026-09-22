#include "cpplings_test.hpp"

#include <vector>

// Appends a doubled copy of every element: {1, 2} becomes {1, 2, 2, 4}.
void append_doubles(std::vector<int>& numbers) {
    // TODO: `push_back` may move all elements to a new, bigger buffer. The loop
    // then keeps reading from the freed old buffer. Loop over the original
    // elements in a way that stays valid while the vector grows.
    for (int number : numbers) {
        numbers.push_back(number * 2);
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
