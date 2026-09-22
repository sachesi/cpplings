#include <iostream>

// TODO: This function compiles with only a warning, but running it is undefined
// behavior. Read the warning, then fix the function.
int square(int num) {
    num * num;
}

int main() {
    int answer = square(3);
    std::cout << "The square of 3 is " << answer << '\n';
}
