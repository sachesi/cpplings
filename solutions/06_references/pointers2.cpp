#include "cpplings_test.hpp"

#include <cstddef>
#include <string>

std::size_t name_length(const std::string* name) {
    if (name == nullptr) {
        return 0;
    }
    return name->size();
}

TEST(existing_name) {
    std::string name = "Grace";
    CHECK_EQ(name_length(&name), 5);
}

TEST(no_name) {
    CHECK_EQ(name_length(nullptr), 0);
}
