#include "cpplings_test.hpp"

int bigger(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

TEST(ten_is_bigger_than_eight) {
    CHECK_EQ(bigger(10, 8), 10);
}

TEST(fortytwo_is_bigger_than_thirtytwo) {
    CHECK_EQ(bigger(32, 42), 42);
}

TEST(equal_numbers) {
    CHECK_EQ(bigger(42, 42), 42);
}
