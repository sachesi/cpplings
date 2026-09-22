#include "cpplings_test.hpp"

#include <array>

constexpr int fibonacci(int n) {
    int a = 0;
    int b = 1;
    for (int i = 0; i < n; ++i) {
        int next = a + b;
        a = b;
        b = next;
    }
    return a;
}

static_assert(fibonacci(0) == 0);
static_assert(fibonacci(1) == 1);
static_assert(fibonacci(10) == 55);

TEST(sizes_from_compile_time_values) {
    std::array<int, fibonacci(6)> buffer{};
    CHECK_EQ(buffer.size(), 8);
}

TEST(also_works_at_runtime) {
    int n = 20;
    CHECK_EQ(fibonacci(n), 6765);
}
