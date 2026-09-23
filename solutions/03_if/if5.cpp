#include "cpplings_test.hpp"

#include <string_view>

std::string_view inbox_status(int unread) {
    // `=` assigns, `==` compares.
    if (unread == 0) {
        return "all read";
    }
    return "new messages";
}

TEST(empty_inbox) {
    CHECK_EQ(inbox_status(0), "all read");
}

TEST(unread_messages) {
    CHECK_EQ(inbox_status(3), "new messages");
}
