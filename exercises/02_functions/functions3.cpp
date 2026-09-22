#include <iostream>

void call_me(int num) {
    for (int i = 0; i < num; ++i) {
        std::cout << "Ring! Call number " << i + 1 << '\n';
    }
}

int main() {
    // TODO: Fix the function call.
    call_me();
}
