// This is a program that is trying to use a completed version of the
// `total_cost` function from the previous exercise. It's not working though!
// Why not? What should we do to fix it?

#include <iostream>
#include <string>

int total_cost(const std::string& item_quantity) {
    const int processing_fee = 1;
    const int cost_per_item = 5;
    // Throws `std::invalid_argument` if the text isn't a number.
    int quantity = std::stoi(item_quantity);
    return quantity * cost_per_item + processing_fee;
}

int main() {
    int tokens = 100;
    std::string pretend_user_input = "8";

    // TODO: Don't let an exception end the program. If the input isn't a number,
    // print an error message and leave the tokens unchanged. Then try it with
    // `pretend_user_input = "beep boop"`.
    int cost = total_cost(pretend_user_input);
    pretend_user_input = "beep boop";
    cost += total_cost(pretend_user_input);

    if (cost > tokens) {
        std::cout << "You can't afford that many!\n";
    } else {
        tokens -= cost;
        std::cout << "You now have " << tokens << " tokens.\n";
    }
}
