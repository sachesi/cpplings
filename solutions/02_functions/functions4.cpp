#include <iostream>

bool is_even(int number) {
    return number % 2 == 0;
}

// The return type must be specified. `auto` would also work here.
int sale_price(int price) {
    if (is_even(price)) {
        return price - 10;
    }
    return price - 3;
}

int main() {
    int original_price = 51;
    std::cout << "Your sale price is " << sale_price(original_price) << '\n';
}
