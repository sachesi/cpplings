#include <iostream>
#include <stdexcept>
#include <string>

int total_cost(const std::string& item_quantity) {
    const int processing_fee = 1;
    const int cost_per_item = 5;
    int quantity = std::stoi(item_quantity);
    return quantity * cost_per_item + processing_fee;
}

int main() {
    int tokens = 100;
    std::string pretend_user_input = "beep boop";

    try {
        int cost = total_cost(pretend_user_input);
        if (cost > tokens) {
            std::cout << "You can't afford that many!\n";
        } else {
            tokens -= cost;
            std::cout << "You now have " << tokens << " tokens.\n";
        }
    } catch (const std::invalid_argument& error) {
        std::cout << "Invalid quantity \"" << pretend_user_input << "\", you still have " << tokens
                  << " tokens.\n";
    }
}
