#include "cpplings_test.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

int alive_nodes = 0;

struct TreeNode {
    std::string name;
    // TODO: A parent owns its children and a child owns its parent. This cycle
    // keeps both alive forever. A child should only refer to its parent without
    // owning it.
    std::shared_ptr<TreeNode> parent;
    std::vector<std::shared_ptr<TreeNode>> children;

    explicit TreeNode(std::string n) : name(std::move(n)) { ++alive_nodes; }
    ~TreeNode() { --alive_nodes; }
};

// Returns the name of the parent, or "(none)" for a root node.
std::string parent_name(const TreeNode& node) {
    // TODO: Update this function to the new type of `parent`.
    if (node.parent == nullptr) {
        return "(none)";
    }
    return node.parent->name;
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
