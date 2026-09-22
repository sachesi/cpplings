#include "cpplings_test.hpp"

int calculate_price_of_apples(int n_apples) {
    if (n_apples > 40) {
        return n_apples;
    }
    return n_apples * 2;
}

TEST(verify_calculate_price_of_apples) {
    CHECK_EQ(calculate_price_of_apples(35), 70);
    CHECK_EQ(calculate_price_of_apples(40), 80);
    CHECK_EQ(calculate_price_of_apples(41), 41);
    CHECK_EQ(calculate_price_of_apples(65), 65);
}
