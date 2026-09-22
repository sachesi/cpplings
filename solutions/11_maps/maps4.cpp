#include "cpplings_test.hpp"

#include <map>
#include <string>

int stock_of(const std::map<std::string, int>& inventory, const std::string& item) {
    auto it = inventory.find(item);
    if (it == inventory.end()) {
        return 0;
    }
    return it->second;
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
