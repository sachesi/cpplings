#include "cpplings_test.hpp"

#include <utility>
#include <vector>

std::vector<int> fill_vec(std::vector<int> vec) {
    vec.push_back(88);
    return vec;
}

TEST(move_semantics1) {
    std::vector<int> vec0 = {22, 44, 66};

    // Passing `vec0` copies it into the parameter.
    std::vector<int> vec1 = fill_vec(vec0);

    CHECK_EQ(vec0, (std::vector<int>{22, 44, 66}));
    CHECK_EQ(vec1, (std::vector<int>{22, 44, 66, 88}));
}
