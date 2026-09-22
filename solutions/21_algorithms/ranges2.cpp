#include "cpplings_test.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <ranges>
#include <vector>

std::uint64_t factorial(std::uint64_t num) {
    // The product of an empty range is the initial value 1.
    return std::ranges::fold_left(std::views::iota(std::uint64_t{1}, num + 1), std::uint64_t{1}, std::multiplies{});
}

std::vector<int> even_squares(const std::vector<int>& numbers, std::size_t limit) {
    return numbers | std::views::filter([](int n) { return n % 2 == 0; }) |
           std::views::transform([](int n) { return n * n; }) |
           std::views::take(static_cast<std::ptrdiff_t>(limit)) | std::ranges::to<std::vector>();
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
