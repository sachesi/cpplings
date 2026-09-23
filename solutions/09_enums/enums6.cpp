#include "cpplings_test.hpp"

#include <format>
#include <string>
#include <variant>

using Reading = std::variant<double, std::string>;

std::string describe(const Reading& reading) {
    if (std::holds_alternative<std::string>(reading)) {
        return "error: " + std::get<std::string>(reading);
    }
    return std::format("{:.1f} degrees", std::get<double>(reading));
}

TEST(temperatures) {
    CHECK_EQ(describe(21.5), "21.5 degrees");
    CHECK_EQ(describe(-3.0), "-3.0 degrees");
}

TEST(errors) {
    CHECK_EQ(describe(std::string("sensor offline")), "error: sensor offline");
}
