//
// Created by DELL on 2023/10/28.
//
#include <iostream>
#include <vector>

struct Point {
    double x, y, z;
    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
};

struct OctreeNode {
    Point minCorner;
    Point maxCorner;
    std::vector<Point> points;
    OctreeNode *children[8];

    OctreeNode(const Point &minCorner, const Point &maxCorner) : minCorner(minCorner), maxCorner(maxCorner) {
        for (int i = 0; i < 8; i++) {
            children[i] = nullptr;
        }
    }

    bool isLeaf() const {
        return points.size() <= 1;
    }
};

class Octree {
public:
    Octree(const Point &minCorner, const Point &maxCorner, int maxDepth) {
        root = new OctreeNode(minCorner, maxCorner);
        this->maxDepth = maxDepth;
    }

    void insert(const Point &point) {
        insert(root, point, 0);
    }

    std::vector<Point> search(const Point &min, const Point &max) {
        std::vector<Point> result;
        search(root, min, max, result);
        return result;
    }

private:
    OctreeNode *root;
    int maxDepth;

    void insert(OctreeNode *node, const Point &point, int depth) {
        if (node->isLeaf() || depth >= maxDepth) {
            node->points.push_back(point);
        } else {
            int octant = getOctant(node, point);
            if (node->children[octant] == nullptr) {
                splitNode(node, octant);
            }
            insert(node->children[octant], point, depth + 1);
        }
    }

    int getOctant(OctreeNode *node, const Point &point) {
        int octant = 0;
        Point midpoint((node->minCorner.x + node->maxCorner.x) / 2,
                       (node->minCorner.y + node->maxCorner.y) / 2,
                       (node->minCorner.z + node->maxCorner.z) / 2);
        if (point.x >= midpoint.x) octant |= 1;
        if (point.y >= midpoint.y) octant |= 2;
        if (point.z >= midpoint.z) octant |= 4;
        return octant;
    }

    void splitNode(OctreeNode *node, int octant) {
        Point midpoint((node->minCorner.x + node->maxCorner.x) / 2,
                       (node->minCorner.y + node->maxCorner.y) / 2,
                       (node->minCorner.z + node->maxCorner.z) / 2);

        for (int i = 0; i < 8; i++) {
            Point minCorner, maxCorner;
            if (i & 1) {
                minCorner.x = midpoint.x;
                maxCorner.x = node->maxCorner.x;
            } else {
                minCorner.x = node->minCorner.x;
                maxCorner.x = midpoint.x;
            }
            if (i & 2) {
                minCorner.y = midpoint.y;
                maxCorner.y = node->maxCorner.y;
            } else {
                minCorner.y = node->minCorner.y;
                maxCorner.y = midpoint.y;
            }
            if (i & 4) {
                minCorner.z = midpoint.z;
                maxCorner.z = node->maxCorner.z;
            } else {
                minCorner.z = node->minCorner.z;
                maxCorner.z = midpoint.z;
            }
            node->children[i] = new OctreeNode(minCorner, maxCorner);
        }

        // Move the points from the parent to the appropriate child
        for (const Point &point : node->points) {
            int childOctant = getOctant(node, point);
            node->children[childOctant]->points.push_back(point);
        }

        // Clear the parent node's points
        node->points.clear();
    }

    void search(OctreeNode *node, const Point &min, const Point &max, std::vector<Point> &result) {
        if (node == nullptr) {
            return;
        }

        // Check if the node intersects with the search region
        if (node->maxCorner.x < min.x || node->minCorner.x > max.x ||
            node->maxCorner.y < min.y || node->minCorner.y > max.y ||
            node->maxCorner.z < min.z || node->minCorner.z > max.z) {
            return;
        }

        // Check if the node is a leaf and contains points
        if (node->isLeaf()) {
            for (const Point &point : node->points) {
                if (point.x >= min.x && point.x <= max.x &&
                    point.y >= min.y && point.y <= max.y &&
                    point.z >= min.z && point.z <= max.z) {
                    result.push_back(point);
                }
            }
            return;
        }

        // Recursively search child nodes
        for (int i = 0; i < 8; i++) {
            search(node->children[i], min, max, result);
        }
    }
};

int main() {
    // Create an Octree with a specified bounding box and maximum depth
    Point minCorner(0, 0, 0);
    Point maxCorner(10, 10, 10);
    Octree octree(minCorner, maxCorner, 4);// Specify the maximum depth

    // Insert points into the Octree
    Point point1(2, 2, 2);
    Point point2(7, 7, 7);
    octree.insert(point1);
    octree.insert(point2);

    // You can continue inserting more points and perform queries as needed

    return 0;
}