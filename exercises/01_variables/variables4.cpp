#include <iostream>

int main() {
    int attempts = 3;
    {
        // TODO: `bonus` only exists inside these braces, its scope. Move the
        // declaration so that the line after the block can use it.
        int bonus = 2;
        std::cout << "Starting with " << attempts << " attempts\n";
    }

    std::cout << "Total attempts: " << attempts + bonus << '\n';
}
