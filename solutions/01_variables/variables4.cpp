#include <iostream>

int main() {
    int attempts = 3;
    int bonus = 2;
    {
        std::cout << "Starting with " << attempts << " attempts\n";
    }

    std::cout << "Total attempts: " << attempts + bonus << '\n';
}
