#include "cpplings_test.hpp"

#include <stdexcept>
#include <string>

std::string generate_nametag_text(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Empty names aren't allowed");
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
