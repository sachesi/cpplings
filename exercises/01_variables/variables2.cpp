#include <iostream>

int main() {
    // TODO: The compiler can deduce the type of an `auto` variable only from
    // its initializer. Give `x` a value.
    auto x;

    if (x == 10) {
        std::cout << "x is ten!\n";
    } else {
        std::cout << "x is not ten!\n";
    }
}
