#include "cpplings_test.hpp"

#include <vector>

bool is_odd(int number) {
    return number % 2 != 0;
}

void remove_odd(std::vector<int>& numbers) {
    // TODO: `erase` invalidates the iterator to the erased element, so `++it`
    // afterwards is undefined behavior. Fix the function. The standard library
    // has a function that erases all elements for which a function returns true.
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (is_odd(*it)) {
            numbers.erase(it);
        }
    }
}

TEST(removes_odd_numbers) {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    remove_odd(numbers);
    std::vector<int> expected = {2, 4, 6};
    CHECK_EQ(numbers, expected);
}

TEST(odd_numbers_next_to_each_other) {
    std::vector<int> numbers = {1, 3, 5, 8};
    remove_odd(numbers);
    std::vector<int> expected = {8};
    CHECK_EQ(numbers, expected);
}
