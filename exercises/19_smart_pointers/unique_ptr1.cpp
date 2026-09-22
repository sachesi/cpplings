// At compile time, C++ needs to know how much space a type takes up. This
// becomes problematic for recursive types, where a value can have as part of
// itself another value of the same type.
//
// Let's look at a linked list: every node holds a value and the rest of the
// list. The end of the list is marked by an empty pointer.

#include "cpplings_test.hpp"

#include <memory>

// TODO: A struct can't contain itself, it would be infinitely large. Store the
// next node on the heap, owned by a `std::unique_ptr`.
struct Node {
    int value;
    Node next;
};

std::unique_ptr<Node> create_empty_list() {
    return nullptr;
}

std::unique_ptr<Node> create_non_empty_list() {
    // TODO: Create the list 1 -> 2 -> 3.
    return nullptr;
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
