#include "cpplings_test.hpp"

#include <cstddef>

// TODO: An array parameter is really a pointer to the first element, so the
// function doesn't know how many elements there are, and `sizeof` gives the size
// of a pointer. Read the compiler warning, then fix the function by taking a
// `std::span<const int>` from <span> instead. It knows its size.
int sum(const int numbers[]) {
    int total = 0;
    std::size_t count = sizeof(numbers) / sizeof(numbers[0]);
    for (std::size_t i = 0; i < count; ++i) {
        total += numbers[i];
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
