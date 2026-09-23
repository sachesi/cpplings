#include "cpplings_test.hpp"

#include <stdexcept>
#include <string>

// TODO: This function refuses to generate text to be printed on a nametag if you
// pass it an empty string. It'd be nicer if it explained what the problem was
// instead of just returning an empty string. Throw a `std::invalid_argument`
// with the message "Empty names aren't allowed" instead.
std::string generate_nametag_text(const std::string& name) {
    if (name.empty()) {
        // Empty names aren't allowed.
        return "";
    }
    return "Hi! My name is " + name;
}

TEST(generates_nametag_text_for_a_nonempty_name) {
    CHECK_EQ(generate_nametag_text("Beyoncé"), "Hi! My name is Beyoncé");
}

TEST(explains_why_generating_nametag_text_fails) {
    CHECK_THROWS_AS(generate_nametag_text(""), std::invalid_argument);

    try {
        generate_nametag_text("");
    } catch (const std::invalid_argument& error) {
        CHECK_EQ(std::string(error.what()), "Empty names aren't allowed");
    }
}
