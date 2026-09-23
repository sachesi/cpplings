// This powerful wrapper provides the ability to store a positive integer value.
// TODO: Rewrite it using a class template so that it supports wrapping ANY type.

#include "cpplings_test.hpp"

#include <string>

struct Wrapper {
    unsigned int value;
};

TEST(store_int_in_wrapper) {
    CHECK_EQ(Wrapper<int>{42}.value, 42);
}

TEST(store_string_in_wrapper) {
    CHECK_EQ(Wrapper<std::string>{"Foo"}.value, "Foo");
}
