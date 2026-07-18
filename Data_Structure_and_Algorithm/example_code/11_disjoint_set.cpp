// 11_disjoint_set.cpp - Disjoint Set (Union-Find)
// Knowledge points: Find, Union, Union-by-Height, Path Compression, Maze Generation

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

// ===== Basic Union-Find (Array Implementation) =====
class BasicDisjointSet {
private:
    vector<int> name;  // name[i] = equivalence class name of element i

public:
    BasicDisjointSet(int n) : name(n) {
        iota(name.begin(), name.end(), 0);  // each element is its own class
    }

    // Find: return equivalence class name - O(1)
    int find(int i) const { return name[i]; }

    // Union: merge two classes - O(n)
    void unionSets(int i, int j) {
        int nameI = find(i), nameJ = find(j);
        if (nameI == nameJ) return;
        // Change all elements with nameJ to nameI
        for (int k = 0; k < (int)name.size(); k++) {
            if (name[k] == nameJ)
                name[k] = nameI;
        }
    }

    bool sameSet(int i, int j) const { return find(i) == find(j); }

    void print() const {
        for (int i = 0; i < (int)name.size(); i++)
            cout << "  Element " << i << " -> class " << name[i] << endl;
    }
};

// ===== Optimized Union-Find (Tree + Union-by-Height + Path Compression) =====
class DisjointSet {
private:
    vector<int> parent;  // parent[i] = parent of i (negative = root with size)
    vector<int> height;  // height of tree rooted at i

public:
    DisjointSet(int n) : parent(n, -1), height(n, 0) {
        // Each element is its own root, size = 1 (stored as -1)
        for (int i = 0; i < n; i++) parent[i] = -1;
    }

    // Find with Path Compression - amortized O(α(n)) ≈ O(1)
    int find(int i) {
        if (parent[i] < 0)  // i is root
            return i;
        // Path compression: make every node point directly to root
        parent[i] = find(parent[i]);
        return parent[i];
    }

    // Union by Height - guarantees O(log n) depth without path compression
    void unionByHeight(int i, int j) {
        int rootI = find(i), rootJ = find(j);
        if (rootI == rootJ) return;  // already in same set

        // Attach shorter tree under taller tree
        if (height[rootI] < height[rootJ]) {
            parent[rootJ] += parent[rootI];  // merge i into j
            parent[rootI] = rootJ;
        } else if (height[rootI] > height[rootJ]) {
            parent[rootI] += parent[rootJ];  // merge j into i
            parent[rootJ] = rootI;
        } else {
            // Same height: merge j into i, height increases by 1
            parent[rootI] += parent[rootJ];
            parent[rootJ] = rootI;
            height[rootI]++;
        }
    }

    bool sameSet(int i, int j) { return find(i) == find(j); }

    int setSize(int i) { return -parent[find(i)]; }

    void print() const {
        cout << "  Parent: ";
        for (int i = 0; i < (int)parent.size(); i++) {
            if (parent[i] < 0)
                cout << "[" << i << "(root,sz=" << -parent[i] << ")] ";
        }
        cout << endl;
        cout << "  Links:  ";
        for (int i = 0; i < (int)parent.size(); i++) {
            if (parent[i] >= 0)
                cout << i << "->" << parent[i] << " ";
        }
        cout << endl;
    }
};

// ===== Maze Generation using Union-Find =====
void generateMaze(int rows, int cols) {
    int n = rows * cols;
    DisjointSet ds(n);

    // Cell (r,c) maps to index r*cols + c
    auto cellId = [cols](int r, int c) { return r * cols + c; };

    srand(42);
    int walls = (rows - 1) * cols + rows * (cols - 1);  // total interior walls
    int broken = 0;

    cout << "Maze " << rows << "x" << cols << " (" << n << " cells, " << walls << " walls)" << endl;

    // Randomly break walls until all cells connected
    while (broken < n - 1) {
        // Pick random wall (direction + cell)
        int dir = rand() % 4;  // 0=up, 1=down, 2=left, 3=right
        int r = rand() % rows;
        int c = rand() % cols;
        int nr = r, nc = c;

        if (dir == 0 && r > 0) nr = r - 1;       // up
        else if (dir == 1 && r < rows-1) nr = r + 1;  // down
        else if (dir == 2 && c > 0) nc = c - 1;       // left
        else if (dir == 3 && c < cols-1) nc = c + 1;  // right
        else continue;

        int id1 = cellId(r, c), id2 = cellId(nr, nc);
        if (!ds.sameSet(id1, id2)) {
            ds.unionByHeight(id1, id2);
            broken++;
        }
    }
    cout << "  Maze generated! (" << broken << " walls broken)" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  Disjoint Set (Union-Find) Demo" << endl;
    cout << "========================================" << endl;

    // Basic Union-Find
    cout << "\n--- Basic Union-Find (Array) ---" << endl;
    BasicDisjointSet basic(8);
    cout << "Initial:" << endl;
    basic.print();

    basic.unionSets(0, 1);
    cout << "\nAfter Union(0,1):" << endl;
    basic.print();

    basic.unionSets(2, 3);
    basic.unionSets(0, 3);
    cout << "\nAfter Union(2,3), Union(0,3):" << endl;
    basic.print();

    cout << "Same set (0,3)? " << (basic.sameSet(0, 3) ? "Yes" : "No") << endl;
    cout << "Same set (0,4)? " << (basic.sameSet(0, 4) ? "Yes" : "No") << endl;

    // Optimized Union-Find
    cout << "\n--- Optimized Union-Find (Union-by-Height + Path Compression) ---" << endl;
    DisjointSet ds(10);

    // Simulate: a~b, b~c, b~d, e~f, g~h, i~e, j~k, k~c
    int unions[][2] = {{0,1}, {1,2}, {1,3}, {4,5}, {6,7}, {8,4}, {9,10<0?0:9}, {1,2}};
    // Let me redo this with valid indices
    cout << "\nOperations:" << endl;

    ds.unionByHeight(0, 1);  // a~b
    cout << "Union(0,1): "; ds.print();

    ds.unionByHeight(1, 2);  // b~c
    cout << "Union(1,2): "; ds.print();

    ds.unionByHeight(1, 3);  // b~d
    cout << "Union(1,3): "; ds.print();

    ds.unionByHeight(4, 5);  // e~f
    cout << "Union(4,5): "; ds.print();

    ds.unionByHeight(6, 7);  // g~h
    cout << "Union(6,7): "; ds.print();

    ds.unionByHeight(8, 4);  // i~e
    cout << "Union(8,4): "; ds.print();

    cout << "\nFind with Path Compression:" << endl;
    cout << "  find(0) = " << ds.find(0) << endl;
    cout << "  find(3) = " << ds.find(3) << " (path compressed: 3->1->0)" << endl;
    cout << "  After compression: "; ds.print();

    cout << "\n=== Maze Generation ===" << endl;
    generateMaze(4, 4);

    cout << "\n========================================" << endl;
    cout << "  Disjoint Set Properties" << endl;
    cout << "========================================" << endl;
    cout << "Basic:      Find O(1), Union O(n)" << endl;
    cout << "By-Height:  Find O(log n), Union O(log n)" << endl;
    cout << "With Path Compression: amortized O(α(n)) ≈ O(1)" << endl;
    cout << "α(n) = inverse Ackermann, practically constant" << endl;
    cout << "Application: Maze generation, connected components, Kruskal's MST" << endl;

    return 0;
}
