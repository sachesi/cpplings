#include <iostream>

int main() {
    // The compiler deduces `int` from the initializer.
    auto x = 42;

    if (x == 10) {
        std::cout << "x is ten!\n";
    } else {
        std::cout << "x is not ten!\n";
    }
}
