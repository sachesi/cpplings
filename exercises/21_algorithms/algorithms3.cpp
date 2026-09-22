#include "cpplings_test.hpp"

#include <algorithm>
#include <vector>

// Removes all odd numbers from the vector.
// TODO: The vector keeps its size. Read the compiler warning and find out what
// `std::remove_if` really does. Then fix the function.
void remove_odd(std::vector<int>& numbers) {
    std::remove_if(numbers.begin(), numbers.end(), [](int n) { return n % 2 != 0; });
}

TEST(removes_odd_numbers) {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7};
    remove_odd(numbers);
    CHECK_EQ(numbers, (std::vector<int>{2, 4, 6}));
}

TEST(keeps_even_numbers) {
    std::vector<int> numbers = {8, 10};
    remove_odd(numbers);
    CHECK_EQ(numbers, (std::vector<int>{8, 10}));
}
