#include <iostream>

// TODO: A `constexpr` variable needs a value that is known at compile time.
// Tell the compiler that this function can be evaluated at compile time.
int number_of_slots() {
    return 4 * 8;
}

int main() {
    constexpr int slots = number_of_slots();
    std::cout << "The table has " << slots << " slots\n";
}
