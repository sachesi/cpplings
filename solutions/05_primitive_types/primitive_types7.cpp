#include <iostream>
#include <string>
#include <utility>

int main() {
    std::pair<std::string, double> cat = {"Furry McFurson", 3.5};

    auto [name, age] = cat;

    std::cout << name << " is " << age << " years old\n";
}
