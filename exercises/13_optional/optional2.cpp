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

// Greets people by their nickname if they have one, otherwise by their name.
std::string greeting(std::string_view name) {
    // TODO: `*` doesn't check whether the optional holds a value. Reading from an
    // empty optional is undefined behavior; the checked standard library aborts.
    std::string nickname = *find_nickname(name);
    return "Hi, " + nickname + "!";
}

// Returns the number of people who have a nickname.
int count_nicknames(const std::vector<std::string>& names) {
    int count = 0;
    for (const std::string& name : names) {
        // TODO: Only count the names that have a nickname.
        std::optional<std::string> nickname = find_nickname(name);
        ++count;
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
