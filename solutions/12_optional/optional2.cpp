#include "cpplings_test.hpp"

#include <optional>
#include <string>
#include <string_view>
#include <vector>

std::optional<std::string> find_nickname(std::string_view name) {
    if (name == "Robert") {
        return "Bob";
    }
    if (name == "Margaret") {
        return "Maggie";
    }
    return std::nullopt;
}

std::string greeting(std::string_view name) {
    std::string nickname = find_nickname(name).value_or(std::string(name));
    return "Hi, " + nickname + "!";
}

int count_nicknames(const std::vector<std::string>& names) {
    int count = 0;
    for (const std::string& name : names) {
        // An `if` with an initializer keeps `nickname` local to the `if`.
        if (std::optional<std::string> nickname = find_nickname(name); nickname.has_value()) {
            ++count;
        }
    }
    return count;
}

TEST(greets_by_nickname) {
    CHECK_EQ(greeting("Robert"), "Hi, Bob!");
    CHECK_EQ(greeting("Margaret"), "Hi, Maggie!");
}

TEST(greets_by_name) {
    CHECK_EQ(greeting("Linus"), "Hi, Linus!");
}

TEST(counts_nicknames) {
    CHECK_EQ(count_nicknames({"Robert", "Linus", "Margaret", "Ken"}), 2);
}
