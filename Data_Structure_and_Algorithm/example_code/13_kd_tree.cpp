// 13_kd_tree.cpp - k-d Tree: 2D Point Storage, Range Search, Insert
// Knowledge points: k-dimensional BST, median split, range query with pruning

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

struct Point {
    double x, y;
    int id;
    Point(double x = 0, double y = 0, int id = -1) : x(x), y(y), id(id) {}
};

struct KdNode {
    Point point;
    KdNode* left;
    KdNode* right;
    KdNode(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};

class KdTree {
private:
    KdNode* root;

    // Build balanced k-d tree from sorted points
    // depth=0 splits on x, depth=1 splits on y, depth=2 splits on x, ...
    KdNode* build(vector<Point>& points, int start, int end, int depth) {
        if (start >= end) return nullptr;

        int axis = depth % 2;  // 0 = x-axis, 1 = y-axis

        // Sort by current axis and pick median
        int mid = (start + end) / 2;
        nth_element(points.begin() + start, points.begin() + mid, points.begin() + end,
            [axis](const Point& a, const Point& b) {
                return axis == 0 ? a.x < b.x : a.y < b.y;
            });

        KdNode* node = new KdNode(points[mid]);
        node->left = build(points, start, mid, depth + 1);
        node->right = build(points, mid + 1, end, depth + 1);
        return node;
    }

    // Insert a point - O(log n) average
    KdNode* insert(KdNode* node, const Point& p, int depth) {
        if (node == nullptr) return new KdNode(p);

        int axis = depth % 2;
        if (axis == 0) {
            if (p.x < node->point.x)
                node->left = insert(node->left, p, depth + 1);
            else
                node->right = insert(node->right, p, depth + 1);
        } else {
            if (p.y < node->point.y)
                node->left = insert(node->left, p, depth + 1);
            else
                node->right = insert(node->right, p, depth + 1);
        }
        return node;
    }

    // Range search: find all points in rectangle [x1,x2] x [y1,y2]
    void rangeSearch(KdNode* node, double x1, double y1, double x2, double y2,
                     int depth, vector<Point>& result) {
        if (node == nullptr) return;

        double px = node->point.x, py = node->point.y;

        // Check if current point is in range
        if (px >= x1 && px <= x2 && py >= y1 && py <= y2)
            result.push_back(node->point);

        int axis = depth % 2;

        // Decide which subtrees to search based on split line
        if (axis == 0) {
            // Split on x-axis
            if (x1 <= px) rangeSearch(node->left, x1, y1, x2, y2, depth + 1, result);
            if (x2 >= px) rangeSearch(node->right, x1, y1, x2, y2, depth + 1, result);
        } else {
            // Split on y-axis
            if (y1 <= py) rangeSearch(node->left, x1, y1, x2, y2, depth + 1, result);
            if (y2 >= py) rangeSearch(node->right, x1, y1, x2, y2, depth + 1, result);
        }
    }

    // Find nearest neighbor
    void nearestNeighbor(KdNode* node, const Point& target, int depth,
                         Point& best, double& bestDist) {
        if (node == nullptr) return;

        double dist = (node->point.x - target.x) * (node->point.x - target.x) +
                      (node->point.y - target.y) * (node->point.y - target.y);
        if (best.id == -1 || dist < bestDist) {
            bestDist = dist;
            best = node->point;
        }

        int axis = depth % 2;
        double diff = (axis == 0) ? (target.x - node->point.x) : (target.y - node->point.y);

        // Search the side where target falls first
        KdNode* first = (diff < 0) ? node->left : node->right;
        KdNode* second = (diff < 0) ? node->right : node->left;

        nearestNeighbor(first, target, depth + 1, best, bestDist);

        // Check if we need to search the other side
        if (diff * diff < bestDist)
            nearestNeighbor(second, target, depth + 1, best, bestDist);
    }

    void inorder(KdNode* node, int depth) {
        if (node == nullptr) return;
        inorder(node->left, depth + 1);
        string axis = (depth % 2 == 0) ? "split-x" : "split-y";
        cout << "  " << node->point.x << "," << node->point.y
             << " (" << axis << ")" << endl;
        inorder(node->right, depth + 1);
    }

    void destroy(KdNode* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    KdTree() : root(nullptr) {}
    ~KdTree() { destroy(root); }

    // Build balanced tree from point set - O(n log n)
    void buildTree(vector<Point>& points) {
        root = build(points, 0, points.size(), 0);
    }

    // Insert point - O(log n) average
    void insert(const Point& p) {
        root = insert(root, p, 0);
    }

    // Range search - O(sqrt(n) + |output|) average
    vector<Point> rangeSearch(double x1, double y1, double x2, double y2) {
        vector<Point> result;
        rangeSearch(root, x1, y1, x2, y2, 0, result);
        return result;
    }

    // Nearest neighbor - O(log n) average
    Point nearestNeighbor(const Point& target) {
        Point best(0, 0, -1);
        double bestDist = 1e18;
        nearestNeighbor(root, target, 0, best, bestDist);
        return best;
    }

    void print() {
        cout << "Tree (in-order, showing split axis):" << endl;
        inorder(root, 0);
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  k-d Tree Demo (2D Points)" << endl;
    cout << "========================================" << endl;

    // 31 points from the lecture slides
    vector<Point> points = {
        {0.03, 0.90, 0}, {0.37, 0.04, 1}, {0.56, 0.78, 2},
        {0.01, 0.48, 3}, {0.41, 0.89, 4}, {0.95, 0.07, 5},
        {0.97, 0.09, 6}, {0.54, 0.65, 7}, {0.04, 0.61, 8},
        {0.73, 0.69, 9}, {0.46, 0.58, 10}, {0.08, 0.89, 11},
        {0.04, 0.41, 12}, {0.94, 0.02, 13}, {0.33, 0.07, 14},
        {0.55, 0.54, 15}, {0.06, 0.05, 16}, {0.04, 0.06, 17},
        {0.74, 0.97, 18}, {0.29, 0.15, 19}, {0.05, 0.88, 20},
        {0.23, 0.23, 21}, {0.55, 0.02, 22}, {0.02, 0.97, 23},
        {0.05, 0.07, 24}, {0.06, 0.28, 25}, {0.09, 0.55, 26},
        {0.02, 0.91, 27}, {0.05, 0.97, 28}, {0.68, 0.42, 29},
        {0.97, 0.18, 30}
    };

    KdTree tree;
    tree.buildTree(points);

    cout << "\nTree structure (depth 0=split-x, depth 1=split-y):" << endl;
    tree.print();

    // Range search
    cout << "\n--- Range Search ---" << endl;
    cout << "Query: points in [0.5, 1.0] x [0.0, 0.5]" << endl;
    vector<Point> results = tree.rangeSearch(0.5, 0.0, 1.0, 0.5);
    cout << "Found " << results.size() << " points:" << endl;
    for (const Point& p : results) {
        cout << "  (" << p.x << ", " << p.y << ")" << endl;
    }

    // Nearest neighbor
    cout << "\n--- Nearest Neighbor ---" << endl;
    Point query(0.5, 0.5);
    Point nn = tree.nearestNeighbor(query);
    cout << "Nearest to (" << query.x << ", " << query.y << "): "
         << "(" << nn.x << ", " << nn.y << ")" << endl;

    // Insert a new point
    cout << "\n--- Insert New Point ---" << endl;
    Point newPt(0.15, 0.66, 31);
    tree.insert(newPt);
    cout << "Inserted (" << newPt.x << ", " << newPt.y << ")" << endl;

    results = tree.rangeSearch(0.1, 0.6, 0.2, 0.7);
    cout << "Range [0.1,0.2] x [0.6,0.7] found " << results.size() << " points:" << endl;
    for (const Point& p : results)
        cout << "  (" << p.x << ", " << p.y << ")" << endl;

    cout << "\n========================================" << endl;
    cout << "  k-d Tree Properties" << endl;
    cout << "========================================" << endl;
    cout << "Depth 0, k, 2k: split on 1st coordinate (x)" << endl;
    cout << "Depth 1, k+1: split on 2nd coordinate (y)" << endl;
    cout << "Balanced: always pick median as split point" << endl;
    cout << "Range search: prune subtrees that can't contain points in range" << endl;
    cout << "Insert: O(log n) average" << endl;
    cout << "Range query: O(sqrt(n) + |output|) average" << endl;
    cout << "Nearest neighbor: O(log n) average with pruning" << endl;
    cout << "Bad for: deletion (hard to maintain structure)" << endl;

    return 0;
}
