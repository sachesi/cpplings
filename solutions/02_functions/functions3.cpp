#include <iostream>

void call_me(int num) {
    for (int i = 0; i < num; ++i) {
        std::cout << "Ring! Call number " << i + 1 << '\n';
    }
}

int main() {
    // `call_me` expects an argument. Another way would be to give the parameter a
    // default value: `void call_me(int num = 3)`.
    call_me(5);
}
