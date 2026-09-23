#include "cpplings_test.hpp"

#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> fruit_basket() {
    std::unordered_map<std::string, int> basket;

    basket["banana"] = 2;
    basket["apple"] = 3;
    basket["mango"] = 1;

    return basket;
}

TEST(at_least_three_types_of_fruits) {
    auto basket = fruit_basket();
    CHECK(basket.size() >= 3);
}

TEST(at_least_five_fruits) {
    int total = 0;
    for (const auto& [fruit, count] : fruit_basket()) {
        total += count;
    }
    CHECK(total >= 5);
}
