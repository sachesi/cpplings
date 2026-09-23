#include "cpplings_test.hpp"

#include <string>
#include <string_view>

std::string full_name(const std::string& first, const std::string& last) {
    return first + " " + last;
}

TEST(full_name_of_a_mathematician) {
    // TODO: A `std::string_view` doesn't own its characters. Here they belong to
    // the temporary string returned by `full_name`, which is destroyed at the
    // end of the statement. Fix the test.
    std::string_view name = full_name("Katherine", "Johnson-Coleman-Goble");

    CHECK_EQ(name, "Katherine Johnson-Coleman-Goble");
}
