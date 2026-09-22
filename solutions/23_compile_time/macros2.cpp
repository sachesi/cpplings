#include "cpplings_test.hpp"

int next_id_calls = 0;

int next_id() {
    ++next_id_calls;
    return 100 + next_id_calls;
}

// Function arguments are evaluated exactly once, before the call.
template <typename T>
constexpr T max_of(T a, T b) {
    return a > b ? a : b;
}

TEST(max_of_numbers) {
    CHECK_EQ(max_of(3, 7), 7);
}

TEST(arguments_are_evaluated_once) {
    int id = max_of(next_id(), 50);
    CHECK_EQ(id, 101);
    CHECK_EQ(next_id_calls, 1);
}
