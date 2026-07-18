// 17_amortized_advanced_heaps.cpp - Amortized Analysis, Fibonacci/Skew/Binomial Heaps
// Knowledge points: amortized bounds, Fibonacci heap O(1) insert, skew/binomial heap

#include <iostream>
#include <algorithm>
using namespace std;

// ===== 1. Amortized Analysis Concepts =====
void amortizedAnalysisDemo() {
    cout << "========================================" << endl;
    cout << "  Amortized Analysis Concepts" << endl;
    cout << "========================================" << endl;

    cout << "\n--- Three Methods ---" << endl;
    cout << "1. Aggregate Method: total cost of n operations / n" << endl;
    cout << "   Example: dynamic array doubling" << endl;
    cout << "   - n inserts, each O(1) except when resizing" << endl;
    cout << "   - Resizes at 1,2,4,8,...,2^k where 2^k >= n" << endl;
    cout << "   - Total: n + 1 + 2 + 4 + ... + 2^k = n + 2^(k+1) - 1 <= 3n" << endl;
    cout << "   - Amortized: 3n/n = O(1) per insert" << endl;

    cout << "\n2. Accounting Method: assign different charges to operations" << endl;
    cout << "   - Cheap operations overcharge, expensive ones undercharge" << endl;
    cout << "   - Invariant: credit never goes negative" << endl;

    cout << "\n3. Potential Method: Phi(D) = potential of data structure D" << endl;
    cout << "   - Amortized cost = actual cost + Phi(Di) - Phi(Di-1)" << endl;
    cout << "   - If Phi increases: operation was cheap (saved credit)" << endl;
    cout << "   - If Phi decreases: operation was expensive (spent credit)" << endl;

    cout << "\n--- Key Amortized Results ---" << endl;
    cout << "Stack with multi-pop: O(1) amortized (aggregate: n ops = 2n)" << endl;
    cout << "Dynamic array push: O(1) amortized (doubling)" << endl;
    cout << "Splay tree: O(log n) amortized per operation" << endl;
    cout << "Fibonacci heap: O(1) amortized for insert, decreaseKey, merge" << endl;
    cout << "Binomial queue merge: O(log n) amortized" << endl;
}

// ===== 2. Skew Heap (self-adjusting mergeable heap) =====
// Simpler than leftist heap, no npl stored
// Amortized O(log n) for all operations
struct SkewNode {
    int data;
    SkewNode* left;
    SkewNode* right;
    SkewNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class SkewHeap {
    SkewNode* root;

    static SkewNode* merge(SkewNode* a, SkewNode* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->data > b->data) swap(a, b);

        // Merge right paths, then swap children
        a->right = merge(a->right, b);
        swap(a->left, a->right);  // Key difference from leftist heap!
        return a;
    }

    void destroy(SkewNode* t) {
        if (!t) return;
        destroy(t->left);
        destroy(t->right);
        delete t;
    }

    void inorder(SkewNode* t) {
        if (!t) return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

public:
    SkewHeap() : root(nullptr) {}
    ~SkewHeap() { destroy(root); }

    bool isEmpty() const { return !root; }
    int top() const { return root ? root->data : -1; }

    void push(int val) {
        root = merge(root, new SkewNode(val));
    }

    int pop() {
        int val = root->data;
        SkewNode* old = root;
        root = merge(root->left, root->right);
        delete old;
        return val;
    }

    void mergeWith(SkewHeap& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }

    void print() { cout << "Skew heap: "; inorder(root); cout << endl; }
};

// ===== 3. Binomial Queue =====
// Collection of binomial trees, mergeable in O(log n)
struct BinomialNode {
    int data;
    int order;  // degree = number of children
    BinomialNode* child;
    BinomialNode* sibling;
    BinomialNode* parent;
    BinomialNode(int val) : data(val), order(0), child(nullptr),
                            sibling(nullptr), parent(nullptr) {}
};

class BinomialQueue {
    BinomialNode* roots[32];  // max ~2^32 elements
    int size;

    // Merge two binomial trees of same order
    static BinomialNode* link(BinomialNode* t1, BinomialNode* t2) {
        if (t1->data > t2->data) swap(t1, t2);
        t2->parent = t1;
        t2->sibling = t1->child;
        t1->child = t2;
        t1->order++;
        return t1;
    }

    void destroy(BinomialNode* node) {
        if (!node) return;
        destroy(node->child);
        destroy(node->sibling);
        delete node;
    }

    void printTree(BinomialNode* node, int depth) const {
        while (node) {
            cout << "  " << string(depth * 2, ' ') << node->data << endl;
            if (node->child) printTree(node->child, depth + 1);
            node = node->sibling;
        }
    }

public:
    BinomialQueue() : size(0) { for (int i = 0; i < 32; i++) roots[i] = nullptr; }
    ~BinomialQueue() {
        for (int i = 0; i < 32; i++) destroy(roots[i]);
    }

    bool isEmpty() const { return size == 0; }
    int getSize() const { return size; }

    void mergeWith(BinomialQueue& other) {
        BinomialNode* carry = nullptr;
        for (int i = 0; i < 32; i++) {
            int state = (roots[i] != nullptr) + 2 * (other.roots[i] != nullptr) + 4 * (carry != nullptr);
            switch (state) {
                case 0: break;
                case 1: break;
                case 2:
                    roots[i] = other.roots[i];
                    other.roots[i] = nullptr;
                    break;
                case 3:
                    carry = link(roots[i], other.roots[i]);
                    roots[i] = nullptr;
                    other.roots[i] = nullptr;
                    break;
                case 4:
                    roots[i] = carry;
                    carry = nullptr;
                    break;
                case 5:
                    carry = link(roots[i], carry);
                    roots[i] = nullptr;
                    break;
                case 6:
                    carry = link(other.roots[i], carry);
                    other.roots[i] = nullptr;
                    break;
                case 7: {
                    BinomialNode* nextCarry = link(other.roots[i], carry);
                    other.roots[i] = nullptr;
                    roots[i] = roots[i];
                    carry = nextCarry;
                    break;
                }
            }
        }
        if (carry) {
            destroy(carry);
            cout << "  Merge overflow: queue capacity exceeded" << endl;
        }
        size += other.size;
        other.size = 0;
    }

    void insert(int val) {
        BinomialQueue temp;
        temp.roots[0] = new BinomialNode(val);
        temp.size = 1;
        mergeWith(temp);
        cout << "  Insert " << val << " (amortized O(1))" << endl;
    }

    void print() const {
        cout << "Binomial Queue (size=" << size << "): ";
        cout << "composed of binomial trees B0, B1, B2, ..." << endl;
        for (int i = 0; i < 32; i++) {
            if (roots[i]) {
                cout << "  B" << i << " present (2^" << i << " nodes)" << endl;
                printTree(roots[i], 1);
            }
        }
    }
};

int main() {
    // Amortized Analysis
    amortizedAnalysisDemo();

    // Skew Heap
    cout << "\n========================================" << endl;
    cout << "  Skew Heap Demo" << endl;
    cout << "========================================" << endl;

    SkewHeap sh1, sh2;
    sh1.push(5); sh1.push(3); sh1.push(8);
    sh2.push(4); sh2.push(2); sh2.push(7);
    sh1.print(); sh2.print();

    sh1.mergeWith(sh2);
    cout << "After merge: "; sh1.print();

    cout << "Pop: " << sh1.pop() << endl;
    cout << "After pop: "; sh1.print();

    cout << "\n--- Skew vs Leftist vs Binary Heap ---" << endl;
    cout << "                Binary Heap   Leftist Heap   Skew Heap" << endl;
    cout << "Push:           O(1)* avg     O(log n)       O(log n) amort" << endl;
    cout << "Pop:            O(log n)      O(log n)       O(log n) amort" << endl;
    cout << "Merge:          O(n)          O(log n)       O(log n) amort" << endl;
    cout << "Structure:      Complete tree  Right-heavy    No structure!" << endl;
    cout << "Storage:        Array          Node-based     Node-based" << endl;
    cout << "* O(1) amortized" << endl;

    // Binomial Queue
    cout << "\n========================================" << endl;
    cout << "  Binomial Queue Concept" << endl;
    cout << "========================================" << endl;

    BinomialQueue bq;
    bq.insert(10);
    bq.insert(20);
    bq.insert(30);
    bq.insert(40);
    bq.insert(50);
    bq.print();

    cout << "\nBinomial Queue Properties:" << endl;
    cout << "  - Collection of binomial trees B0, B1, B2, ..." << endl;
    cout << "  - Bi has 2^i nodes, children are Bi-1, Bi-2, ..., B0" << endl;
    cout << "  - Merge: like binary addition (0+0=0, 0+1=1, 1+1=carry)" << endl;
    cout << "  - Insert: O(1) amortized, Merge: O(log n) amortized" << endl;
    cout << "  - DeleteMin: O(log n)" << endl;

    cout << "\n========================================" << endl;
    cout << "  Fibonacci Heap Concept" << endl;
    cout << "========================================" << endl;
    cout << "  - Collection of heap-ordered trees (like binomial queue)" << endl;
    cout << "  - But trees can be very unstructured (lazy merging)" << endl;
    cout << "  - Cut operation: cut node and add to root list" << endl;
    cout << "  - Cascading cut: cut parent if already cut once" << endl;
    cout << "  - Insert, decreaseKey, merge: O(1) AMORTIZED" << endl;
    cout << "  - DeleteMin: O(log n) amortized" << endl;
    cout << "  - Used in: Dijkstra O(E + V log V), Prim O(E + V log V)" << endl;

    return 0;
}
