#include <iostream>

// This store is having a sale where if the price is an even number, you get 10
// dollars off, but if it's an odd number, it's 3 dollars off.

bool is_even(int number) {
    return number % 2 == 0;
}

// TODO: Fix the function signature.
sale_price(int price) {
    if (is_even(price)) {
        return price - 10;
    }
    return price - 3;
}

int main() {
    int original_price = 51;
    std::cout << "Your sale price is " << sale_price(original_price) << '\n';
}
