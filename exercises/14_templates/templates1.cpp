#include "cpplings_test.hpp"

#include <string>

// TODO: Turn this function into a function template so that it works for any
// type that can be compared with `<`.
int largest(int a, int b) {
    if (a < b) {
        return b;
    }
    return a;
}

TEST(integers) {
    CHECK_EQ(largest(3, 7), 7);
}

TEST(floating_point_numbers) {
    CHECK_NEAR(largest(2.5, 1.5), 2.5, 1e-9);
}

TEST(strings) {
    CHECK_EQ(largest(std::string("apple"), std::string("banana")), "banana");
}
