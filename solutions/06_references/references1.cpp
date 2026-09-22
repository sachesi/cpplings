#include "cpplings_test.hpp"

#include <vector>

// The reference refers to the caller's vector instead of a copy.
void add_bonus(std::vector<int>& scores) {
    for (int& score : scores) {
        score += 10;
    }
}

TEST(bonus_is_added) {
    std::vector<int> scores = {50, 70, 90};
    add_bonus(scores);
    std::vector<int> expected = {60, 80, 100};
    CHECK_EQ(scores, expected);
}
