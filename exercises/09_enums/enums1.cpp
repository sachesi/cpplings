#include <iostream>
#include <string_view>

enum class Message {
    // TODO: Define a few kinds of messages as used below.
};

std::string_view describe(Message message) {
    switch (message) {
    case Message::Resize:
        return "Resize";
    case Message::Move:
        return "Move";
    case Message::Echo:
        return "Echo";
    case Message::ChangeColor:
        return "ChangeColor";
    case Message::Quit:
        return "Quit";
    }
    return "?";
}

int main() {
    std::cout << describe(Message::Resize) << '\n';
    std::cout << describe(Message::Move) << '\n';
    std::cout << describe(Message::Echo) << '\n';
    std::cout << describe(Message::ChangeColor) << '\n';
    std::cout << describe(Message::Quit) << '\n';
}
