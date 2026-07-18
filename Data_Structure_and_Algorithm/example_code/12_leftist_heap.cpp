// 12_leftist_heap.cpp - Leftist Heap: Merge, Push, Pop
// Knowledge points: min-npl, merge-based, O(log n) push/pop, O(log n) merge

#include <iostream>
using namespace std;

struct LeftistNode {
    int data;
    int npl;           // null-path length: shortest distance to a non-full node
    LeftistNode* left;
    LeftistNode* right;
    LeftistNode(int val) : data(val), npl(0), left(nullptr), right(nullptr) {}
};

class LeftistHeap {
private:
    LeftistNode* root;

    // Merge two leftist heaps - O(log n)
    static LeftistNode* merge(LeftistNode* a, LeftistNode* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;

        // Ensure a has the smaller root (min-heap property)
        if (a->data > b->data) swap(a, b);

        // Merge b with a's right subtree
        a->right = merge(a->right, b);

        // Maintain leftist property: npl(left) >= npl(right)
        if (a->left == nullptr || 
            (a->right != nullptr && a->left->npl < a->right->npl)) {
            swap(a->left, a->right);
        }

        // Update npl
        a->npl = (a->right == nullptr) ? 0 : a->right->npl + 1;

        return a;
    }

    void inorder(LeftistNode* t) {
        if (t == nullptr) return;
        inorder(t->left);
        cout << t->data << "(npl=" << t->npl << ") ";
        inorder(t->right);
    }

    void printTree(LeftistNode* t, string prefix, bool isLeft) {
        if (t == nullptr) return;
        cout << prefix;
        cout << (isLeft ? "|-- " : "\\-- ");
        cout << t->data << "(npl=" << t->npl << ")" << endl;
        printTree(t->left, prefix + (isLeft ? "|   " : "    "), true);
        printTree(t->right, prefix + (isLeft ? "|   " : "    "), false);
    }

    void destroy(LeftistNode* t) {
        if (t == nullptr) return;
        destroy(t->left);
        destroy(t->right);
        delete t;
    }

public:
    LeftistHeap() : root(nullptr) {}
    ~LeftistHeap() { destroy(root); }

    bool isEmpty() const { return root == nullptr; }

    // Push: merge with a single-node heap - O(log n)
    void push(int val) {
        LeftistNode* newNode = new LeftistNode(val);
        root = merge(root, newNode);
    }

    // Pop: remove root, merge left and right subtrees - O(log n)
    int pop() {
        if (isEmpty()) { cout << "Heap is empty!" << endl; return -1; }
        int minVal = root->data;
        LeftistNode* oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
        return minVal;
    }

    int top() const { return root ? root->data : -1; }

    // Merge another leftist heap into this one
    void mergeWith(LeftistHeap& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }

    void print() {
        cout << "Tree structure:" << endl;
        printTree(root, "", false);
    }

    void printInorder() {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  Leftist Heap Demo" << endl;
    cout << "========================================" << endl;

    // Demo 1: Basic operations
    cout << "\n--- Push Operations ---" << endl;
    LeftistHeap heap1;
    int vals[] = {15, 10, 20, 8, 12, 25, 5};
    for (int v : vals) {
        heap1.push(v);
        cout << "Push " << v << ": min=" << heap1.top() << endl;
    }

    cout << "\nHeap structure (leftist property: npl(left) >= npl(right)):" << endl;
    heap1.print();
    heap1.printInorder();

    cout << "\n--- Pop Operations ---" << endl;
    while (!heap1.isEmpty()) {
        cout << "Pop " << heap1.pop() << endl;
    }

    // Demo 2: Merge two leftist heaps
    cout << "\n--- Merge Two Leftist Heaps ---" << endl;
    LeftistHeap heap2, heap3;
    heap2.push(3);
    heap2.push(7);
    heap2.push(1);
    heap2.push(5);

    heap3.push(4);
    heap3.push(8);
    heap3.push(2);
    heap3.push(6);

    cout << "Heap 2: "; heap2.printInorder();
    cout << "Heap 3: "; heap3.printInorder();

    heap2.mergeWith(heap3);
    cout << "\nAfter merge:" << endl;
    cout << "Merged heap: "; heap2.printInorder();
    heap2.print();

    cout << "\n========================================" << endl;
    cout << "  Leftist Heap Properties" << endl;
    cout << "========================================" << endl;
    cout << "Null-path length (npl): shortest distance to non-full node" << endl;
    cout << "  - npl(single node) = 0" << endl;
    cout << "  - npl(NULL) = -1" << endl;
    cout << "Leftist property: npl(left) >= npl(right) for every node" << endl;
    cout << "  - Tree is 'heavier' on the left side" << endl;
    cout << "Merge: compare roots, merge smaller root's right with other" << endl;
    cout << "  - Then fix leftist property by swapping children if needed" << endl;
    cout << "Push: merge current heap with trivial single-node heap" << endl;
    cout << "Pop: remove root, merge left and right subtrees" << endl;
    cout << "All operations: O(log n)" << endl;
    cout << "Merge of binary heap: O(n) - leftist heap is much better!" << endl;

    return 0;
}
