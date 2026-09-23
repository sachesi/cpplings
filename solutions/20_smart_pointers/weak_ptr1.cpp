#include "cpplings_test.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

int alive_nodes = 0;

struct TreeNode {
    std::string name;
    std::weak_ptr<TreeNode> parent;
    std::vector<std::shared_ptr<TreeNode>> children;

    explicit TreeNode(std::string n) : name(std::move(n)) { ++alive_nodes; }
    ~TreeNode() { --alive_nodes; }
};

std::string parent_name(const TreeNode& node) {
    // `lock` returns a `shared_ptr` that keeps the parent alive while it's used,
    // or an empty one if the parent doesn't exist (anymore).
    std::shared_ptr<TreeNode> parent = node.parent.lock();
    if (parent == nullptr) {
        return "(none)";
    }
    return parent->name;
}

TEST(tree_nodes_are_freed) {
    {
        auto root = std::make_shared<TreeNode>("root");
        auto leaf = std::make_shared<TreeNode>("leaf");
        leaf->parent = root;
        root->children.push_back(leaf);

        CHECK_EQ(parent_name(*leaf), "root");
        CHECK_EQ(parent_name(*root), "(none)");
        CHECK_EQ(alive_nodes, 2);
    }
    CHECK_EQ(alive_nodes, 0);
}
