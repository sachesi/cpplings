#include "cpplings_test.hpp"

#include <string>

// Taking `const T&` avoids copying types like `std::string`.
template <typename T>
const T& largest(const T& a, const T& b) {
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
