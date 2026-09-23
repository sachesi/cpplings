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

using Message = std::variant<Resize, Move, Echo, ChangeColor, Quit>;

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
        // Leaving out an alternative is a compiler error.
        std::visit(Overloaded{
                       [&](const Resize& resize) {
                           width = resize.width;
                           height = resize.height;
                       },
                       [&](const Move& move) {
                           x = move.x;
                           y = move.y;
                       },
                       [&](const Echo& echo) { last_message = echo.text; },
                       [&](const ChangeColor& color) {
                           red = color.red;
                           green = color.green;
                           blue = color.blue;
                       },
                       [&](const Quit&) { quit = true; },
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
