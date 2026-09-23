#include "cpplings_test.hpp"

#include <string_view>

std::string_view inbox_status(int unread) {
    // TODO: Every inbox is reported as having new messages. Read the compiler
    // warning about this condition.
    if (unread = 0) {
        return "all read";
    }
    return "new messages";
}

// Don't change the tests!
TEST(empty_inbox) {
    CHECK_EQ(inbox_status(0), "all read");
}

TEST(unread_messages) {
    CHECK_EQ(inbox_status(3), "new messages");
}
