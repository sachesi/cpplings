#include <iostream>

int square(int num) {
    // Flowing off the end of a function that returns a value is undefined
    // behavior. The value must be returned explicitly.
    return num * num;
}

int main() {
    int answer = square(3);
    std::cout << "The square of 3 is " << answer << '\n';
}
