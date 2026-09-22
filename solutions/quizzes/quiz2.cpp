#include "cpplings_test.hpp"

#include <cctype>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

enum class CommandKind { Uppercase, Trim, Append };

struct Command {
    CommandKind kind;
    std::size_t count = 0;
};

namespace my_module {

std::vector<std::string> transformer(const std::vector<std::pair<std::string, Command>>& input) {
    std::vector<std::string> output;
    output.reserve(input.size());

    for (const auto& [text, command] : input) {
        std::string result = text;
        switch (command.kind) {
        case CommandKind::Uppercase:
            for (char& c : result) {
                // `std::toupper` expects values that fit into `unsigned char`.
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            }
            break;
        case CommandKind::Trim: {
            std::size_t first = result.find_first_not_of(" \t\n");
            std::size_t last = result.find_last_not_of(" \t\n");
            result = first == std::string::npos ? "" : result.substr(first, last - first + 1);
            break;
        }
        case CommandKind::Append:
            for (std::size_t i = 0; i < command.count; ++i) {
                result += "bar";
            }
            break;
        }
        output.push_back(std::move(result));
    }

    return output;
}

} // namespace my_module

TEST(it_works) {
    std::vector<std::pair<std::string, Command>> input = {
        {"hello", {CommandKind::Uppercase}},
        {" all roads lead to rome! ", {CommandKind::Trim}},
        {"foo", {CommandKind::Append, 1}},
        {"bar", {CommandKind::Append, 5}},
    };
    std::vector<std::string> expected = {"HELLO", "all roads lead to rome!", "foobar", "barbarbarbarbarbar"};
    CHECK_EQ(my_module::transformer(input), expected);
}
