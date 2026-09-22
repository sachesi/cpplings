#include <iostream>

int main() {
    // TODO: Brace initialization refuses conversions that lose data. Instead of
    // switching to `=`, pick a type for `price` that can hold 19.99.
    int price{19.99};

    std::cout << "The price is " << price << '\n';
}
