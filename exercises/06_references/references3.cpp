#include "cpplings_test.hpp"

#include <string>

// TODO: This function returns a reference to `greeting`, but `greeting` is
// destroyed when the function returns. The caller gets a dangling reference.
// Read the compiler warning, then fix the function.
const std::string& make_greeting(const std::string& name) {
    std::string greeting = "Hello, " + name + ", nice to meet you!";
    return greeting;
}

TEST(greets_by_name) {
    std::string greeting = make_greeting("Ada Lovelace");
    CHECK_EQ(greeting, "Hello, Ada Lovelace, nice to meet you!");
}
