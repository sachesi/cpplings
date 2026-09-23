#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono_literals;

    auto timeout = 1500ms;
    auto interval = 2s;

    auto total = timeout + interval;
    std::cout << "Waiting for " << total.count() << " milliseconds\n";
    std::cout << "That's " << std::chrono::duration<double>(total).count() << " seconds\n";
}
