#include "cpplings_test.hpp"

#include <functional>
#include <map>
#include <string>

std::function<int(int)> make_multiplier(int factor) {
    // TODO: Return a lambda that multiplies its argument by `factor`.
    return nullptr;
}

std::map<std::string, std::function<int(int, int)>> make_calculator() {
    // TODO: Add the operations "-" and "*".
    return {
        {"+", [](int a, int b) { return a + b; }},
    };
}

TEST(multiplier) {
    std::function<int(int)> triple = make_multiplier(3);
    std::function<int(int)> negate = make_multiplier(-1);
    CHECK_EQ(triple(5), 15);
    CHECK_EQ(negate(7), -7);
}

TEST(calculator) {
    auto operations = make_calculator();
    CHECK_EQ(operations.at("+")(6, 3), 9);
    CHECK_EQ(operations.at("-")(6, 3), 3);
    CHECK_EQ(operations.at("*")(6, 3), 18);
}
