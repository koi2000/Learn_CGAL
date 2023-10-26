#include <iostream>
#include <vector>
#define MIN_SIZE 4
struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    // 重载加法运算符+
    Point operator+(const Point &other) const {
        return Point(x + other.x, y + other.y);
    }

    // 重载除法运算符/（整数）
    Point operator/(int divisor) const {
        if (divisor != 0) {
            return Point(x / divisor, y / divisor);
        } else {
            throw std::exception();
        }
    }

    // 重载除法运算符/（浮点数）
    Point operator/(double divisor) const {
        if (divisor != 0.0) {
            return Point(x / divisor, y / divisor);
        } else {
            throw std::exception();
        }
    }

    bool operator==(const Point &other) const {
        return (this->x == other.x) && (this->y == other.y);
    }
};

class Rect {
public:
    double xMin, xMax, yMin, yMax;
    double width, height;
    Point center;
    Rect() {}
    Rect(double xMin, double xMax, double yMin, double yMax)
        : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {
        width = xMax - xMin;
        height = yMax - yMin;
        center = Point((xMax - xMin) / 2, (yMax - yMin) / 2);
    }

    // 定义静态函数 MinMaxRect，用于创建新的矩形区域
    static Rect MinMaxRect(double xMin, double yMin, double xMax, double yMax) {
        return Rect(xMin, xMax, yMin, yMax);
    }

    bool Contains(Point p) {
        return (p.x >= xMin && p.x <= xMax) && (p.y >= yMin && p.y <= yMax);
    }
};


class TriangleShape {
public:
    std::vector<Point> vertices;
    int a, b, c;

    Point pA() const { return vertices[a]; }
    Point pB() const { return vertices[b]; }
    Point pC() const { return vertices[c]; }

    Point GetCenter() const {
        return (vertices[a] + vertices[b] + vertices[c]) / 3.0;
    }

    // 重载相等运算符==
    bool operator==(const TriangleShape &other) const {
        return (vertices == other.vertices) && (a == other.a) && (b == other.b) && (c == other.c);
    }
};

class QuadTreeNode {
public:
    QuadTreeNode *mChildren[4];
    std::vector<TriangleShape> mContent;
    Rect mArea;

    QuadTreeNode() {
        for (int i = 0; i < 4; i++) {
            mChildren[i] = nullptr;
        }
    }

    QuadTreeNode(Rect area) : mArea(area) {
        for (int i = 0; i < 4; i++) {
            mChildren[i] = nullptr;
        }
    }

    void SetArea(Rect area) {
        mArea = area;
    }

    Rect GetArea() const {
        return mArea;
    }

    QuadTreeNode **GetChildren() {
        return mChildren;
    }

    std::vector<TriangleShape> GetContent() {
        return mContent;
    }

    int GetShapeCnt() {
        return mContent.size();
    }

    bool Insert(TriangleShape shape) {
        if (!Contains(shape)) {
            return false;
        }

        if (mArea.width <= MIN_SIZE) {
            mContent.push_back(shape);
            return true;
        }

        int index = getIndex(shape);
        if (index >= 0) {
            if (mChildren[index] == nullptr) {
                mChildren[index] = CreateChild(index);
            }
            bool success = mChildren[index]->Insert(shape);
            if (success) return true;
        }

        mContent.push_back(shape);
        return true;
    }


    bool Contains(TriangleShape shape) {
        return mArea.Contains(shape.pA()) && mArea.Contains(shape.pB()) && mArea.Contains(shape.pC());
    }

    QuadTreeNode *CreateChild(int index) {
        if (index < 0 || index > 3) {
            throw std::invalid_argument("index must be in [0, 3], now it is " + std::to_string(index));
        }

        QuadTreeNode *child = new QuadTreeNode();
        switch (index) {
            case 0:
                child->SetArea(Rect::MinMaxRect(mArea.xMin, mArea.yMin, mArea.center.x, mArea.center.y));
                break;
            case 1:
                child->SetArea(Rect::MinMaxRect(mArea.center.x, mArea.yMin, mArea.xMax, mArea.center.y));
                break;
            case 2:
                child->SetArea(Rect::MinMaxRect(mArea.xMin, mArea.center.y, mArea.center.x, mArea.yMax));
                break;
            case 3:
                child->SetArea(Rect::MinMaxRect(mArea.center.x, mArea.center.y, mArea.xMax, mArea.yMax));
                break;
        }
        return child;
    }

    void Remove(TriangleShape shape) {
        if (Contains(shape)) {
            int index = getIndex(shape);
            if (index >= 0 && mChildren[index] != nullptr) {
                mChildren[index]->Remove(shape);
                return;
            }

            for (size_t i = 0; i < mContent.size(); i++) {
                if (mContent[i] == shape) {
                    mContent.erase(mContent.begin() + i);
                    break;
                }
            }
        }
    }

    int getIndex(TriangleShape shape) {
        int i1 = getIndex(shape.pA());
        int i2 = getIndex(shape.pB());
        if (i1 != i2) {
            return -1;
        }
        int i3 = getIndex(shape.pC());
        if (i2 != i3) {
            return -1;
        }
        return i1;
    }

    int getIndex(Point point) {
        if (!mArea.Contains(point)) {
            return -1;
        }
        int index = 0;
        if (point.x > mArea.center.x) {
            index += 1;
        }
        if (point.y > mArea.center.y) {
            index += 2;
        }
        return index;
    }

    void GetTriangleShapes(std::vector<TriangleShape> &list) {
        if (mChildren != nullptr) {
            for (int i = 0; i < 4; i++) {
                if (mChildren[i] != nullptr) {
                    mChildren[i]->GetTriangleShapes(list);
                }
            }
        }
        list.insert(list.end(), mContent.begin(), mContent.end());
    }

    QuadTreeNode *GetMinContainsNode(Point pos) {
        if (!mArea.Contains(pos)) {
            return nullptr;
        }
        QuadTreeNode *result = nullptr;
        if (mChildren != nullptr) {
            for (int i = 0; i < 4; i++) {
                if (mChildren[i] != nullptr) {
                    QuadTreeNode *node = mChildren[i]->GetMinContainsNode(pos);
                    if (node != nullptr && node->GetShapeCnt() > 0) {
                        result = node;
                        break;
                    }
                }
            }
        }
        if (result == nullptr) {
            result = this;
        }
        return result;
    }

    QuadTreeNode *GetMinContainsNode(const TriangleShape &triangle) {
        if (!Intersects(triangle)) {
            return nullptr;
        }
        // 如果有子节点，继续查找
        if (mChildren != nullptr) {
            for (int i = 0; i < 4; i++) {
                if (mChildren[i] != nullptr) {
                    QuadTreeNode *childResult = mChildren[i]->GetMinContainsNode(triangle);
                    if (childResult != nullptr) {
                        return childResult;
                    }
                }
            }
        }
        // 如果没有子节点或子节点中没有包含三角形的，返回当前节点
        return this;
    }

    bool Intersects(const TriangleShape &triangle) {
        // 获取三角形的顶点
        Point p1 = triangle.pA();
        Point p2 = triangle.pB();
        Point p3 = triangle.pC();
        // 获取节点区域的边界
        double minX = mArea.xMin;
        double maxX = mArea.xMax;
        double minY = mArea.yMin;
        double maxY = mArea.yMax;
        // 检查三角形的边是否与节点区域相交
        if (LineIntersectsRectangle(p1, p2, minX, maxX, minY, maxY) ||
            LineIntersectsRectangle(p2, p3, minX, maxX, minY, maxY) ||
            LineIntersectsRectangle(p3, p1, minX, maxX, minY, maxY)) {
            return true;
        }
        return false;
    }

    // 检查线段和矩形是否相交
    bool LineIntersectsRectangle(const Point &p1, const Point &p2, double rectMinX, double rectMaxX, double rectMinY, double rectMaxY) {
        double minX = std::min(p1.x, p2.x);
        double maxX = std::max(p1.x, p2.x);
        double minY = std::min(p1.y, p2.y);
        double maxY = std::max(p1.y, p2.y);
        // 线段与矩形不相交的情况
        if (maxX < rectMinX || minX > rectMaxX || maxY < rectMinY || minY > rectMaxY) {
            return false;
        }
        // 线段与矩形相交
        return true;
    }
};

int main() {
    return 0;
}
