#include <iostream>

int main() {
    bool is_morning = true;
    if (is_morning) {
        std::cout << "Good morning!\n";
    }

    bool is_evening = !is_morning;
    if (is_evening) {
        std::cout << "Good evening!\n";
    }
}
