#include "cpplings_test.hpp"

#include <span>

// A span is a pointer together with a length. Arrays, `std::array` and
// `std::vector` all convert to it.
int sum(std::span<const int> numbers) {
    int total = 0;
    for (int number : numbers) {
        total += number;
    }
    return total;
}

TEST(sum_of_five) {
    int numbers[] = {1, 2, 3, 4, 5};
    CHECK_EQ(sum(numbers), 15);
}

TEST(sum_of_one) {
    int numbers[] = {42};
    CHECK_EQ(sum(numbers), 42);
}
