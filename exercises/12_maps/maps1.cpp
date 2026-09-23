// A basket of fruits in the form of a map needs to be defined. The key
// represents the name of the fruit and the value represents how many of that
// particular fruit is in the basket. You have to put at least 3 different
// types of fruits (e.g. apple, banana, mango) in the basket and the total count
// of all the fruits should be at least 5.

#include "cpplings_test.hpp"

#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> fruit_basket() {
    // TODO: Declare the map.
    // std::unordered_map<???, ???> basket;

    // Two bananas are already given for you :)
    basket["banana"] = 2;

    // TODO: Put more fruits in your basket.

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
