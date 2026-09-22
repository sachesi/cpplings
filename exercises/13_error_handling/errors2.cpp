#include "cpplings_test.hpp"

#include <exception>
#include <stdexcept>
#include <string>

// Checks the quantity typed into an order form.
// TODO: Some tests fail. Read the compiler warnings, then fix the function.
std::string check_quantity(const std::string& text) {
    try {
        int quantity = std::stoi(text);
        return "ok: " + std::to_string(quantity);
    } catch (const std::exception&) {
        return "unexpected error";
    } catch (const std::invalid_argument&) {
        return "not a number";
    } catch (const std::out_of_range&) {
        return "too large";
    }
}

TEST(valid_quantity) {
    CHECK_EQ(check_quantity("12"), "ok: 12");
}

TEST(not_a_number) {
    CHECK_EQ(check_quantity("beep boop"), "not a number");
}

TEST(too_large) {
    CHECK_EQ(check_quantity("99999999999999999999"), "too large");
}
