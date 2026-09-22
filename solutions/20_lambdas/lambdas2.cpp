#include "cpplings_test.hpp"

TEST(counter) {
    int count = 0;

    // Captured by reference: the lambda changes the original variable.
    auto increment = [&count] { ++count; };

    increment();
    increment();
    increment();
    CHECK_EQ(count, 3);
}

TEST(snapshot) {
    int price = 100;

    // Captured by value: the lambda has its own copy from when it was created.
    auto get_original_price = [price] { return price; };

    price = 80;
    CHECK_EQ(get_original_price(), 100);
    CHECK_EQ(price, 80);
}
