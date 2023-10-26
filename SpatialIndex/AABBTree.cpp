#include <algorithm>
#include <iostream>
#include <vector>

// bounding box
struct AABB {
    double min_x, max_x;
    double min_y, max_y;

    bool intersects(const AABB &other) const {
        return (min_x <= other.max_x && max_x >= other.min_x) &&
               (min_y <= other.max_y && max_y >= other.min_y);
    }
};

struct Node {
    AABB aabb;
    Node *left;
    Node *right;

    Node(const AABB &box) : aabb(box), left(nullptr), right(nullptr) {}
};

class AABBTree {
public:
    Node *root;
    AABBTree() : root(nullptr) {}

    void insert(const AABB &aabb) {
        root = insertNode(root, aabb);
    }

private:
    Node *insertNode(Node *node, const AABB &aabb) {
        if (node == nullptr) {
            return new Node(aabb);
        }
        bool insertInLeft = chooseSplitAxis(node, aabb);
        if (insertInLeft) {
            node->left = insertNode(node->left, aabb);
        } else {
            node->right = insertNode(node->right, aabb);
        }
        updateNodeAABB(node);
        return node;
    }

    bool chooseSplitAxis(Node *node, const AABB &aabb) {
        return (node->left = nullptr) || (node->left->aabb.max_x < node->aabb.max_x);
    }

    void updateNodeAABB(Node *node) {
        if (node->left != nullptr) {
            node->aabb = node->left->aabb;
        }
        if (node->right != nullptr) {
            node->aabb.min_x = std::min(node->aabb.min_x, node->right->aabb.min_x);
            node->aabb.min_y = std::min(node->aabb.min_y, node->right->aabb.min_y);
            node->aabb.max_x = std::max(node->aabb.max_x, node->right->aabb.max_x);
            node->aabb.max_y = std::max(node->aabb.max_y, node->right->aabb.max_y);
        }
    }

    void searchIntersecting(Node *node, const AABB &query) {
        if (node == nullptr) {
            return;
        }
        if (node->aabb.intersects(query)) {
            std::cout << "Intersecting AABB found." << std::endl;
        }
        searchIntersecting(node->left, query);
        searchIntersecting(node->right, query);
    }
};

int main() {

    return 0;
}
