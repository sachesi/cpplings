// C arrays

#include <iostream>
#include <iterator>

int main() {
    // TODO: Create an array called `a` with at least 100 elements in it.
    // int a[] = ???

    static_assert(std::size(a) >= 100, "Wait, that's not a big array!");
    std::cout << "Wow, that's a big array!\n";
}
