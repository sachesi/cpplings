#include "cpplings_test.hpp"

#include <algorithm>
#include <vector>

void remove_odd(std::vector<int>& numbers) {
    // `std::remove_if` can't change the size of a container; it only moves the
    // kept elements to the front and returns where they end. `std::erase_if`
    // (C++20) also erases the rest. Before C++20, this was written as
    // numbers.erase(std::remove_if(...), numbers.end());
    std::erase_if(numbers, [](int n) { return n % 2 != 0; });
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
