#include <iostream>
#include <string>

int main() {
    std::string number = "T-H-R-E-E";
    std::cout << "Spell a number: " << number << '\n';

    // A nested block is a new scope, so it may declare its own `number` which
    // hides the outer one. Choosing a different name would be clearer, though.
    {
        int number = 3;
        std::cout << "Number plus two is: " << number + 2 << '\n';
    }
}
