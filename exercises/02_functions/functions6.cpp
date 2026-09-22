#include <iostream>

// TODO: `main` calls `greet`, but at that point the compiler hasn't seen `greet`
// yet. Fix this without moving `main` or `greet`.

int main() {
    greet("Ferris");
    greet("Bjarne");
}

void greet(const char* name) {
    std::cout << "Hello, " << name << "!\n";
}
