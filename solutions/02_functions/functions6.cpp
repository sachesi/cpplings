#include <iostream>

// A declaration tells the compiler that the function exists. It is defined below.
void greet(const char* name);

int main() {
    greet("Ferris");
    greet("Bjarne");
}

void greet(const char* name) {
    std::cout << "Hello, " << name << "!\n";
}
