#include "cpplings_test.hpp"

#include <cstddef>
#include <string>

// Returns the length of the name, or 0 if there is no name.
// TODO: Dereferencing a null pointer crashes the program. Fix the function.
std::size_t name_length(const std::string* name) {
    return name->size();
}

TEST(existing_name) {
    std::string name = "Grace";
    CHECK_EQ(name_length(&name), 5);
}

TEST(no_name) {
    CHECK_EQ(name_length(nullptr), 0);
}
