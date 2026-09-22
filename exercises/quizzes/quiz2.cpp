// This is a quiz for the following sections:
// - Strings
// - Enums
// - Namespaces
// - Maps
//
// Let's build a little machine in the form of a function. As input, we're going
// to give a list of strings and commands. These commands determine what action
// is going to be applied to the string. It can either be:
// - Uppercase the string
// - Trim the string
// - Append "bar" to the string a specified amount of times
//
// The exact form of this will be:
// - The input is going to be a vector of pairs, each pair containing a string
//   and a command.
// - The output element is going to be a vector of strings.

#include "cpplings_test.hpp"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

enum class CommandKind { Uppercase, Trim, Append };

struct Command {
    CommandKind kind;
    // How often "bar" is appended. Only used by `Append`.
    std::size_t count = 0;
};

namespace my_module {

// TODO: Complete the function as described above.
// std::vector<std::string> transformer(const std::vector<std::pair<std::string, Command>>& input) {}

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
