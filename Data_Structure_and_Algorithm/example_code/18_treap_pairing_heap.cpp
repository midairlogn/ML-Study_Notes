// 18_treap_pairing_heap.cpp - Treap & Pairing Heap
// Knowledge points: randomized BST, mergeable heap variants

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// ===== 1. Treap =====
// A BST ordered by key + heap ordered by random priority
// Expected O(log n) for all operations (like randomized BST)
struct TreapNode {
    int key;
    int priority;  // random priority, heap-ordered
    TreapNode* left;
    TreapNode* right;
    TreapNode(int k, int p) : key(k), priority(p), left(nullptr), right(nullptr) {}
};

class Treap {
private:
    TreapNode* root;

    // Right rotation
    TreapNode* rotateR(TreapNode* t) {
        TreapNode* u = t->left;
        t->left = u->right;
        u->right = t;
        return u;
    }

    // Left rotation
    TreapNode* rotateL(TreapNode* t) {
        TreapNode* u = t->right;
        t->right = u->left;
        u->left = t;
        return u;
    }

    // Insert: BST insert by key, then rotate up to fix heap by priority
    TreapNode* insert(TreapNode* t, int key, int priority) {
        if (!t) return new TreapNode(key, priority);
        if (key < t->key) {
            t->left = insert(t->left, key, priority);
            if (t->left->priority > t->priority)
                t = rotateR(t);
        } else if (key > t->key) {
            t->right = insert(t->right, key, priority);
            if (t->right->priority > t->priority)
                t = rotateL(t);
        }
        return t;
    }

    // Remove: rotate down the node to a leaf, then delete
    TreapNode* remove(TreapNode* t, int key) {
        if (!t) return nullptr;
        if (key < t->key) {
            t->left = remove(t->left, key);
        } else if (key > t->key) {
            t->right = remove(t->right, key);
        } else {
            if (!t->left) {
                TreapNode* right = t->right;
                delete t;
                return right;
            }
            if (!t->right) {
                TreapNode* left = t->left;
                delete t;
                return left;
            }
            // Rotate toward higher-priority child
            if (t->left->priority > t->right->priority) {
                t = rotateR(t);
                t->right = remove(t->right, key);
            } else {
                t = rotateL(t);
                t->left = remove(t->left, key);
            }
        }
        return t;
    }

    void inorder(TreapNode* t) {
        if (!t) return;
        inorder(t->left);
        cout << t->key << "(p=" << t->priority << ") ";
        inorder(t->right);
    }

    void printTree(TreapNode* t, string prefix, bool isLeft) {
        if (!t) return;
        cout << prefix << (isLeft ? "|-- " : "\\-- ")
             << t->key << "(p=" << t->priority << ")" << endl;
        printTree(t->left, prefix + (isLeft ? "|   " : "    "), true);
        printTree(t->right, prefix + (isLeft ? "|   " : "    "), false);
    }

    void destroy(TreapNode* t) {
        if (!t) return;
        destroy(t->left);
        destroy(t->right);
        delete t;
    }

public:
    Treap() : root(nullptr) {}
    ~Treap() { destroy(root); }

    void insert(int key) {
        int priority = rand();
        root = insert(root, key, priority);
    }

    void remove(int key) { root = remove(root, key); }

    void print() {
        cout << "Treap (key, priority):" << endl;
        printTree(root, "", false);
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }
};

// ===== 2. Pairing Heap =====
// Simple mergeable heap, amortized O(log n) for deleteMin
// Insert and merge are O(1)
// DecreaseKey is O(log n) amortized (best known for decreaseKey)
struct PairingNode {
    int data;
    PairingNode* child;
    PairingNode* next;  // sibling
    PairingNode(int val) : data(val), child(nullptr), next(nullptr) {}
};

class PairingHeap {
    PairingNode* root;

    // Merge two pairing heaps
    static PairingNode* merge(PairingNode* a, PairingNode* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->data > b->data) swap(a, b);
        b->next = a->child;
        a->child = b;
        return a;
    }

    // Two-pass merge: pair up children left-to-right, then right-to-left
    PairingNode* combineChildren(PairingNode* firstChild) {
        if (!firstChild || !firstChild->next) return firstChild;

        // Collect children and detach sibling links before merging.
        vector<PairingNode*> trees;
        for (PairingNode* current = firstChild; current != nullptr; ) {
            PairingNode* next = current->next;
            current->next = nullptr;
            trees.push_back(current);
            current = next;
        }

        // Pair up: merge arr[0] with arr[1], arr[2] with arr[3], ...
        vector<PairingNode*> merged;
        for (size_t i = 0; i < trees.size(); i += 2) {
            if (i + 1 < trees.size()) merged.push_back(merge(trees[i], trees[i + 1]));
            else merged.push_back(trees[i]);
        }

        // Merge results right-to-left
        PairingNode* result = merged.back();
        for (int i = static_cast<int>(merged.size()) - 2; i >= 0; i--)
            result = merge(merged[i], result);

        return result;
    }

    void inorder(PairingNode* t) {
        if (!t) return;
        cout << t->data << " ";
        inorder(t->child);
        inorder(t->next);
    }

    void destroy(PairingNode* t) {
        if (!t) return;
        destroy(t->child);
        destroy(t->next);
        delete t;
    }

public:
    PairingHeap() : root(nullptr) {}
    ~PairingHeap() { destroy(root); }

    bool isEmpty() const { return !root; }
    int top() const { return root ? root->data : -1; }

    // Insert: O(1) actual
    void push(int val) {
        root = merge(root, new PairingNode(val));
    }

    // Delete min: O(log n) amortized
    int pop() {
        if (!root) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        int val = root->data;
        PairingNode* old = root;
        root = combineChildren(root->child);
        delete old;
        return val;
    }

    // Merge: O(1) actual
    void mergeWith(PairingHeap& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }

    void print() {
        cout << "Pairing heap: ";
        inorder(root);
        cout << endl;
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  Treap Demo" << endl;
    cout << "========================================" << endl;

    srand(42);
    Treap treap;
    int keys[] = {50, 30, 70, 20, 40, 60, 80, 10, 25};
    for (int k : keys) {
        treap.insert(k);
        cout << "Insert " << k << endl;
    }
    treap.print();

    cout << "\nRemove 30:" << endl;
    treap.remove(30);
    treap.print();

    cout << "\n--- Treap Properties ---" << endl;
    cout << "  BST ordered by key (left < root < right)" << endl;
    cout << "  Heap ordered by random priority (parent > children)" << endl;
    cout << "  Expected O(log n) for insert, remove, find" << endl;
    cout << "  Rotations maintain both BST and heap properties" << endl;

    cout << "\n========================================" << endl;
    cout << "  Pairing Heap Demo" << endl;
    cout << "========================================" << endl;

    PairingHeap ph1, ph2;
    ph1.push(5); ph1.push(3); ph1.push(8);
    ph2.push(4); ph2.push(2); ph2.push(7);
    ph1.print(); ph2.print();

    ph1.mergeWith(ph2);
    cout << "After merge: "; ph1.print();

    cout << "Pop: " << ph1.pop() << endl;
    cout << "Pop: " << ph1.pop() << endl;
    cout << "After pops: "; ph1.print();

    cout << "\n--- Heap Comparison ---" << endl;
    cout << "                Binary   Leftist   Skew     Fibonacci  Pairing" << endl;
    cout << "Push:           O(1)*    O(logn)   O(logn)* O(1)*     O(1)" << endl;
    cout << "DeleteMin:      O(logn) O(logn)  O(logn)* O(logn)*  O(logn)*" << endl;
    cout << "Merge:          O(n)    O(logn)  O(logn)* O(1)*     O(1)" << endl;
    cout << "DecreaseKey:    O(n)    O(logn)  O(logn)* O(1)*     O(logn)*" << endl;
    cout << "* = amortized" << endl;

    return 0;
}
