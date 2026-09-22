#include "cpplings_test.hpp"

int next_id_calls = 0;

int next_id() {
    ++next_id_calls;
    return 100 + next_id_calls;
}

// TODO: A macro repeats its arguments, so `next_id()` is called twice. Replace
// the macro with a function template (or `std::max` from <algorithm>).
#define MAX(a, b) ((a) > (b) ? (a) : (b))

TEST(max_of_numbers) {
    CHECK_EQ(MAX(3, 7), 7);
}

TEST(arguments_are_evaluated_once) {
    int id = MAX(next_id(), 50);
    CHECK_EQ(id, 101);
    CHECK_EQ(next_id_calls, 1);
}
