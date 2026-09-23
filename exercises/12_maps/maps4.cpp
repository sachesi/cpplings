#include "cpplings_test.hpp"

#include <map>
#include <string>

// Returns how many of `item` are in stock, or 0 if the item is unknown.
// TODO: Fix the compiler error. The inventory must not be modified.
int stock_of(const std::map<std::string, int>& inventory, const std::string& item) {
    return inventory[item];
}

TEST(known_items) {
    const std::map<std::string, int> inventory = {{"hammer", 3}, {"nails", 250}};
    CHECK_EQ(stock_of(inventory, "hammer"), 3);
    CHECK_EQ(stock_of(inventory, "nails"), 250);
}

TEST(unknown_item) {
    const std::map<std::string, int> inventory = {{"hammer", 3}};
    CHECK_EQ(stock_of(inventory, "saw"), 0);
    CHECK_EQ(inventory.size(), 1);
}
