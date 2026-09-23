#include "cpplings_test.hpp"

int add(int a, int b) {
    return a + b;
}

// TODO: Several functions can share a name as long as their parameters differ.
// Add a second `add` that works with `double` so that all tests pass.

TEST(adding_integers) {
    CHECK_EQ(add(2, 3), 5);
}

TEST(adding_doubles) {
    CHECK_NEAR(add(1.5, 2.25), 3.75, 1e-9);
}
