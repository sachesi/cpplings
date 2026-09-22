#include <iostream>

// The type of function parameters must always be written out.
void call_me(int num) {
    for (int i = 0; i < num; ++i) {
        std::cout << "Ring! Call number " << i + 1 << '\n';
    }
}

int main() {
    call_me(3);
}
