// This is a quiz for the following sections:
// - Variables
// - Functions
// - If
//
// Mary is buying apples. The price of an apple is calculated as follows:
// - An apple costs 2 dollars.
// - However, if Mary buys more than 40 apples, the price of each apple in the
//   entire order is reduced to only 1 dollar!

#include "cpplings_test.hpp"

// TODO: Write a function `calculate_price_of_apples` that takes the amount of
// apples and returns the total price.

// Don't change the tests!
TEST(verify_calculate_price_of_apples) {
    CHECK_EQ(calculate_price_of_apples(35), 70);
    CHECK_EQ(calculate_price_of_apples(40), 80);
    CHECK_EQ(calculate_price_of_apples(41), 41);
    CHECK_EQ(calculate_price_of_apples(65), 65);
}
