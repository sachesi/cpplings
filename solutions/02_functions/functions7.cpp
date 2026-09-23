#include "cpplings_test.hpp"

int add(int a, int b) {
    return a + b;
}

// The compiler picks the overload whose parameters match the arguments best.
double add(double a, double b) {
    return a + b;
}

TEST(adding_integers) {
    CHECK_EQ(add(2, 3), 5);
}

TEST(adding_doubles) {
    CHECK_NEAR(add(1.5, 2.25), 3.75, 1e-9);
}
