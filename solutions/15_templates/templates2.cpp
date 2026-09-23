#include "cpplings_test.hpp"

#include <string>

template <typename T>
struct Wrapper {
    T value;
};

TEST(store_int_in_wrapper) {
    CHECK_EQ(Wrapper<int>{42}.value, 42);
}

TEST(store_string_in_wrapper) {
    CHECK_EQ(Wrapper<std::string>{"Foo"}.value, "Foo");
}
