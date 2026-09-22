#include "cpplings_test.hpp"

#include <string>
#include <string_view>

std::string full_name(const std::string& first, const std::string& last) {
    return first + " " + last;
}

TEST(full_name_of_a_mathematician) {
    // The variable owns the characters now.
    std::string name = full_name("Katherine", "Johnson-Coleman-Goble");

    CHECK_EQ(name, "Katherine Johnson-Coleman-Goble");
}
