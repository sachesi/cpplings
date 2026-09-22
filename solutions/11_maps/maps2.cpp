#include "cpplings_test.hpp"

#include <map>

enum class Fruit { Apple, Banana, Mango, Lychee, Pineapple };

void fruit_basket(std::map<Fruit, int>& basket) {
    const Fruit fruit_kinds[] = {Fruit::Apple, Fruit::Banana, Fruit::Mango, Fruit::Lychee, Fruit::Pineapple};

    for (Fruit fruit : fruit_kinds) {
        // Inserts only if the key is missing. `insert` would work as well.
        basket.try_emplace(fruit, 1);
    }
}

std::map<Fruit, int> get_fruit_basket() {
    return {{Fruit::Apple, 4}, {Fruit::Mango, 2}, {Fruit::Lychee, 5}};
}

TEST(existing_fruits_unchanged) {
    auto basket = get_fruit_basket();
    fruit_basket(basket);
    CHECK_EQ(basket[Fruit::Apple], 4);
    CHECK_EQ(basket[Fruit::Mango], 2);
    CHECK_EQ(basket[Fruit::Lychee], 5);
}

TEST(all_fruit_types_in_basket) {
    auto basket = get_fruit_basket();
    fruit_basket(basket);
    CHECK_EQ(basket.size(), 5);
    for (const auto& [fruit, count] : basket) {
        CHECK(count > 0);
    }
}
