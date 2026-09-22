#include <iostream>

// TODO: Add the missing type of the parameter `num`.
void call_me(num) {
    for (int i = 0; i < num; ++i) {
        std::cout << "Ring! Call number " << i + 1 << '\n';
    }
}

int main() {
    call_me(3);
}
