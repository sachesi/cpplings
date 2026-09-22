#include "cpplings_test.hpp"

#include <vector>

double average(const std::vector<int>& values) {
    int total = 0;
    for (int value : values) {
        total += value;
    }
    // Dividing an `int` by a `std::size_t` converts the `int` to `std::size_t`.
    // A negative total becomes a huge positive number, and the division is an
    // integer division. Converting both to `double` avoids both problems.
    return static_cast<double>(total) / static_cast<double>(values.size());
}

TEST(positive_numbers) {
    CHECK_NEAR(average({1, 2, 3, 4}), 2.5, 1e-9);
}

TEST(negative_numbers) {
    CHECK_NEAR(average({-1, -2, -6}), -3.0, 1e-9);
}
