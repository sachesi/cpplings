#include <iostream>
#include <string>

int main() {
    // TODO: Fix the compiler error. String literals are arrays of characters,
    // and two arrays can't be added.
    std::string greeting = "Hello, " + "world!";

    std::cout << greeting << '\n';
}
