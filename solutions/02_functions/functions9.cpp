#include "cpplings_test.hpp"

long long factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

TEST(factorial_of_zero) {
    CHECK_EQ(factorial(0), 1);
}

TEST(factorial_of_five) {
    CHECK_EQ(factorial(5), 120);
}

TEST(factorial_of_twenty) {
    CHECK_EQ(factorial(20), 2'432'902'008'176'640'000);
}
