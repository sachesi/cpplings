// Bitwise operators

#include "cpplings_test.hpp"

// Each permission is one bit of an unsigned integer.
constexpr unsigned read_permission = 1u << 0;
constexpr unsigned write_permission = 1u << 1;
constexpr unsigned execute_permission = 1u << 2;

// TODO: Return `permissions` with the bits of `extra` turned on.
unsigned grant(unsigned permissions, unsigned extra) {
    return permissions;
}

// TODO: Return whether all bits of `wanted` are turned on in `permissions`.
bool has(unsigned permissions, unsigned wanted) {
    return permissions == wanted;
}

TEST(granting) {
    CHECK_EQ(grant(0, read_permission), read_permission);
    CHECK_EQ(grant(read_permission, write_permission), 3u);
    CHECK_EQ(grant(write_permission, write_permission), write_permission);
}

TEST(checking) {
    unsigned permissions = read_permission | execute_permission;
    CHECK(has(permissions, read_permission));
    CHECK(has(permissions, execute_permission));
    CHECK(!has(permissions, write_permission));
    CHECK(has(permissions, read_permission | execute_permission));
    CHECK(!has(permissions, read_permission | write_permission));
}
