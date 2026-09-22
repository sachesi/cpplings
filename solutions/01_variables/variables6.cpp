#include <iostream>

constexpr int number_of_slots() {
    return 4 * 8;
}

int main() {
    constexpr int slots = number_of_slots();
    std::cout << "The table has " << slots << " slots\n";
}
