#include <iostream>

int main() {
    // TODO: Fix the compiler error. Should `x` really be a constant?
    const int x = 3;
    std::cout << "Number " << x << '\n';

    x = 5;
    std::cout << "Number " << x << '\n';
}
