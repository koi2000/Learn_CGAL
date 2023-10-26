//
// Created by DELL on 2023/10/26.
//
#include <iostream>
#include <vector>

struct Point {
    double x, y;

    Point(double x, double y) : x(x), y(y) {}
};

struct QuadTreeNode {
    double x, y, width, height;
    Point* point;
    QuadTreeNode* children[4]; // Four children

    QuadTreeNode(double x, double y, double width, double height) : x(x), y(y), width(width), height(height), point(nullptr) {
        for (int i = 0; i < 4; i++) {
            children[i] = nullptr;
        }
    }
};

class QuadTree {
public:
    QuadTree(double x, double y, double width, double height, int maxDepth) : maxDepth(maxDepth) {
        root = new QuadTreeNode(x, y, width, height);
    }

    ~QuadTree() {
        clear(root);
    }

    void insert(Point* point) {
        insert(root, point, 0);
    }

    // Perform a range query within a given rectangle
    void queryRange(const double x, const double y, const double width, const double height, std::vector<Point*>& result) {
        queryRange(root, x, y, width, height, result);
    }

    // Perform collision detection between a point and the tree's contents
    bool isColliding(double x, double y) {
        return isColliding(root, x, y);
    }

private:
    QuadTreeNode* root;
    int maxDepth;

    void clear(QuadTreeNode* node) {
        if (node == nullptr) return;
        for (int i = 0; i < 4; i++) {
            clear(node->children[i]);
        }
        delete node;
    }

    void insert(QuadTreeNode* node, Point* point, int depth) {
        // Insertion logic, as shown in the previous response
    }

    void queryRange(QuadTreeNode* node, double qx, double qy, double qw, double qh, std::vector<Point*>& result) {
        // Range query logic, checks for intersections and adds points to the result vector
    }

    bool isColliding(QuadTreeNode* node, double x, double y) {
        if (node == nullptr) {
            return false;
        }

        if (node->point != nullptr) {
            // Check collision with the point stored in the node
            double px = node->point->x;
            double py = node->point->y;
            return (px >= x && px <= x + 1.0 && py >= y && py <= y + 1.0);
        }

        double subWidth = node->width / 2.0;
        double subHeight = node->height / 2.0;

        if (x < node->x + subWidth) {
            if (y < node->y + subHeight) {
                return isColliding(node->children[0], x, y);
            } else {
                return isColliding(node->children[1], x, y);
            }
        } else {
            if (y < node->y + subHeight) {
                return isColliding(node->children[2], x, y);
            } else {
                return isColliding(node->children[3], x, y);
            }
        }
    }
};

int main() {
    QuadTree quadtree(0, 0, 100, 100, 4);

    std::vector<Point> points = {Point(10, 10), Point(20, 20), Point(30, 30)};
    for (const Point& point : points) {
        quadtree.insert(new Point(point.x, point.y));
    }

    // Query range example
    std::vector<Point*> result;
    quadtree.queryRange(15, 15, 10, 10, result);

    for (Point* point : result) {
        std::cout << "Point found in query range: (" << point->x << ", " << point->y << ")" << std::endl;
    }

    // Collision detection example
    bool collision = quadtree.isColliding(22, 22);
    std::cout << "Collision detected: " << (collision ? "Yes" : "No") << std::endl;

    return 0;
}
