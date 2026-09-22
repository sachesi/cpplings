#include "cpplings_test.hpp"

#include <string>
#include <variant>

struct Resize {
    int width;
    int height;
};
struct Move {
    int x;
    int y;
};
struct Echo {
    std::string text;
};
struct ChangeColor {
    int red;
    int green;
    int blue;
};
struct Quit {};

// A message is exactly one of these alternatives.
using Message = std::variant<Resize, Move, Echo, ChangeColor, Quit>;

// Lets `std::visit` pick a lambda by the type of the alternative.
template <typename... Lambdas>
struct Overloaded : Lambdas... {
    using Lambdas::operator()...;
};

struct State {
    int width = 0;
    int height = 0;
    int x = 0;
    int y = 0;
    std::string last_message;
    int red = 0;
    int green = 0;
    int blue = 0;
    bool quit = false;

    void process(const Message& message) {
        // TODO: Update the state depending on the message:
        // - Resize: change width and height (already done)
        // - Move: change x and y
        // - Echo: store the text in last_message
        // - ChangeColor: change the color
        // - Quit: set quit to true
        // Then remove the catch-all lambda at the end. Without it, the compiler
        // makes sure that every alternative is handled.
        std::visit(Overloaded{
                       [&](const Resize& resize) {
                           width = resize.width;
                           height = resize.height;
                       },
                       [&](const auto&) {},
                   },
                   message);
    }
};

TEST(match_message_call) {
    State state;
    state.process(Resize{10, 30});
    state.process(Move{10, 15});
    state.process(Echo{"Hello world!"});
    state.process(ChangeColor{255, 0, 255});
    state.process(Quit{});

    CHECK_EQ(state.width, 10);
    CHECK_EQ(state.height, 30);
    CHECK_EQ(state.x, 10);
    CHECK_EQ(state.y, 15);
    CHECK_EQ(state.last_message, "Hello world!");
    CHECK_EQ(state.red, 255);
    CHECK_EQ(state.green, 0);
    CHECK_EQ(state.blue, 255);
    CHECK(state.quit);
}
