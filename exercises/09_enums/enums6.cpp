#include "cpplings_test.hpp"

#include <format>
#include <string>
#include <variant>

// A sensor reports either a temperature or an error message.
using Reading = std::variant<double, std::string>;

std::string describe(const Reading& reading) {
    // TODO: `std::get` throws `std::bad_variant_access` when the variant holds
    // another alternative. Check which alternative `reading` holds first, and
    // describe errors as "error: " followed by the message.
    return std::format("{:.1f} degrees", std::get<double>(reading));
}

TEST(temperatures) {
    CHECK_EQ(describe(21.5), "21.5 degrees");
    CHECK_EQ(describe(-3.0), "-3.0 degrees");
}

TEST(errors) {
    CHECK_EQ(describe(std::string("sensor offline")), "error: sensor offline");
}
