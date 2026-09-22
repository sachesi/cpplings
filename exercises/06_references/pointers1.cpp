#include "cpplings_test.hpp"

// TODO: Swap the values that `a` and `b` point to.
void swap_values(int* a, int* b) {
}

TEST(swaps_two_values) {
    int x = 1;
    int y = 2;
    swap_values(&x, &y);
    CHECK_EQ(x, 2);
    CHECK_EQ(y, 1);
}

TEST(swaps_array_elements) {
    int numbers[] = {10, 20, 30};
    swap_values(&numbers[0], &numbers[2]);
    CHECK_EQ(numbers[0], 30);
    CHECK_EQ(numbers[2], 10);
}
