#include "cpplings_test.hpp"

#include <string>

struct Order {
    std::string name;
    int year = 0;
    bool made_by_phone = false;
    bool made_by_mobile = false;
    bool made_by_email = false;
    int item_number = 0;
    int count = 0;
};

Order create_order_template() {
    // TODO: Fix the compiler error. Designated initializers must follow the order
    // in which the members are declared in the struct.
    return Order{
        .name = "Bob",
        .year = 2019,
        .item_number = 123,
        .made_by_email = true,
        .count = 0,
    };
}

TEST(your_order) {
    Order order_template = create_order_template();

    // TODO: Create your own order based on the template: copy it and change only
    // what differs. Your order is for "Hacker in C++" and has a count of 1.
    // Order your_order = ???

    CHECK_EQ(your_order.name, "Hacker in C++");
    CHECK_EQ(your_order.year, order_template.year);
    CHECK_EQ(your_order.made_by_phone, order_template.made_by_phone);
    CHECK_EQ(your_order.made_by_mobile, order_template.made_by_mobile);
    CHECK_EQ(your_order.made_by_email, order_template.made_by_email);
    CHECK_EQ(your_order.item_number, order_template.item_number);
    CHECK_EQ(your_order.count, 1);
}
