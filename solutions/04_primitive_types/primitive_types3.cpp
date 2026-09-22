#include <iostream>
#include <iterator>

int main() {
    // An array with 100 elements, all initialized to zero.
    int a[100] = {};

    static_assert(std::size(a) >= 100, "Wait, that's not a big array!");
    std::cout << "Wow, that's a big array!\n";
}
