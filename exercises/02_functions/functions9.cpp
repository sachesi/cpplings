#include "cpplings_test.hpp"

// n! = n * (n - 1) * ... * 1, and 0! = 1.
long long factorial(int n) {
    // TODO: A function may call itself, but it needs a case where it stops.
    // Without one, it keeps calling itself until the program crashes.
    return n * factorial(n - 1);
}

// Don't change the tests!
TEST(factorial_of_zero) {
    CHECK_EQ(factorial(0), 1);
}

TEST(factorial_of_five) {
    CHECK_EQ(factorial(5), 120);
}

TEST(factorial_of_twenty) {
    CHECK_EQ(factorial(20), 2'432'902'008'176'640'000);
}
