#include "cpplings_test.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <ranges>
#include <vector>

std::uint64_t factorial(std::uint64_t num) {
    // TODO: Complete this function to return the factorial of `num` which is
    // defined as `1 * 2 * 3 * … * num`.
    // https://en.wikipedia.org/wiki/Factorial
    //
    // Do not use:
    // - early returns
    // - imperative style loops (for/while)
    // - additional variables
    // - recursion
    //
    // Use `std::views::iota` and `std::ranges::fold_left`.
    return 0;
}

// Returns the squares of the even numbers, but at most `limit` of them.
std::vector<int> even_squares(const std::vector<int>& numbers, std::size_t limit) {
    // TODO: Build a pipeline of `std::views::filter`, `std::views::transform` and
    // `std::views::take`, then collect it with `std::ranges::to<std::vector>()`.
    return {};
}

TEST(factorial_of_0) {
    CHECK_EQ(factorial(0), 1u);
}

TEST(factorial_of_1) {
    CHECK_EQ(factorial(1), 1u);
}

TEST(factorial_of_2) {
    CHECK_EQ(factorial(2), 2u);
}

TEST(factorial_of_4) {
    CHECK_EQ(factorial(4), 24u);
}

TEST(squares_of_even_numbers) {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};
    CHECK_EQ(even_squares(numbers, 3), (std::vector<int>{4, 16, 36}));
    CHECK_EQ(even_squares(numbers, 10), (std::vector<int>{4, 16, 36, 64}));
    CHECK_EQ(even_squares({1, 3}, 2), std::vector<int>{});
}
