#include <iostream>
#include <string>

int main() {
    std::string number = "T-H-R-E-E";
    std::cout << "Spell a number: " << number << '\n';

    // TODO: Fix the compiler error by changing the line below without renaming
    // the variable `number` above. A name can only be declared once per scope.
    int number = 3;
    std::cout << "Number plus two is: " << number + 2 << '\n';
}
