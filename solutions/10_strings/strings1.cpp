#include <iostream>
#include <string>

int main() {
    // Adding a string literal to a `std::string` works.
    std::string greeting = std::string("Hello, ") + "world!";
    // Other ways:
    // using namespace std::string_literals;
    // std::string greeting = "Hello, "s + "world!";
    //
    // Adjacent string literals are joined by the compiler:
    // std::string greeting = "Hello, " "world!";

    std::cout << greeting << '\n';
}
