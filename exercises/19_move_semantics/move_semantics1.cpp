#include "cpplings_test.hpp"

#include <utility>
#include <vector>

std::vector<int> fill_vec(std::vector<int> vec) {
    vec.push_back(88);
    return vec;
}

TEST(move_semantics1) {
    std::vector<int> vec0 = {22, 44, 66};

    // TODO: `vec0` should keep its elements. Fix the line below.
    std::vector<int> vec1 = fill_vec(std::move(vec0));

    CHECK_EQ(vec0, (std::vector<int>{22, 44, 66}));
    CHECK_EQ(vec1, (std::vector<int>{22, 44, 66, 88}));
}
