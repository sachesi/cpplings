#include "cpplings_test.hpp"

TEST(counter) {
    int count = 0;

    // TODO: The lambda should increase `count` every time it's called, but it
    // only changes its own copy. Fix the capture.
    auto increment = [count]() mutable { ++count; };

    increment();
    increment();
    increment();
    CHECK_EQ(count, 3);
}

TEST(snapshot) {
    int price = 100;

    // TODO: `get_original_price` should return the price at the time the lambda
    // was created, not the current one. Fix the capture.
    auto get_original_price = [&price] { return price; };

    price = 80;
    CHECK_EQ(get_original_price(), 100);
    CHECK_EQ(price, 80);
}
