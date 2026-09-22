#include "cpplings_test.hpp"

#include <string>

// Returning by value gives the caller its own string. This doesn't copy: the
// local variable is moved out or constructed directly in the caller's object.
std::string make_greeting(const std::string& name) {
    std::string greeting = "Hello, " + name + ", nice to meet you!";
    return greeting;
}

TEST(greets_by_name) {
    std::string greeting = make_greeting("Ada Lovelace");
    CHECK_EQ(greeting, "Hello, Ada Lovelace, nice to meet you!");
}
