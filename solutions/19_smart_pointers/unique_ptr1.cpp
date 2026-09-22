#include "cpplings_test.hpp"

#include <memory>

// A pointer has a fixed size, no matter what it points to.
struct Node {
    int value;
    std::unique_ptr<Node> next;
};

std::unique_ptr<Node> create_empty_list() {
    return nullptr;
}

std::unique_ptr<Node> create_non_empty_list() {
    auto third = std::make_unique<Node>(3, nullptr);
    auto second = std::make_unique<Node>(2, std::move(third));
    return std::make_unique<Node>(1, std::move(second));
}

int sum(const Node* list) {
    int total = 0;
    for (const Node* node = list; node != nullptr; node = node->next.get()) {
        total += node->value;
    }
    return total;
}

TEST(empty_list) {
    CHECK(create_empty_list() == nullptr);
}

TEST(non_empty_list) {
    std::unique_ptr<Node> list = create_non_empty_list();
    CHECK(list != nullptr);
    CHECK_EQ(list->value, 1);
    CHECK_EQ(sum(list.get()), 6);
}
