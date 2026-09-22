// Pairs and structured bindings

#include <iostream>
#include <string>
#include <utility>

int main() {
    std::pair<std::string, double> cat = {"Furry McFurson", 3.5};

    // TODO: Unpack `cat` into the two variables `name` and `age` in a single
    // statement using a structured binding.
    // auto /* your pattern here */ = cat;

    std::cout << name << " is " << age << " years old\n";
}
