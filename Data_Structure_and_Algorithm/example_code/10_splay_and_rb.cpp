// 10_splay_and_rb.cpp - Splay Tree & Red-Black Tree Concepts
// Knowledge points: Splay tree splaying, Red-black tree coloring rules

#include <iostream>
using namespace std;

// ===== Splay Tree (Simplified - insert + find with splay) =====
struct SplayNode {
    int data;
    SplayNode* left;
    SplayNode* right;
    SplayNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    SplayNode* root;

    // Right rotation (Zig for left child)
    SplayNode* rotateR(SplayNode* x) {
        SplayNode* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    // Left rotation (Zig for right child)
    SplayNode* rotateL(SplayNode* x) {
        SplayNode* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    // Splay: bring node with given key to root
    SplayNode* splay(SplayNode* node, int key) {
        if (node == nullptr || node->data == key)
            return node;

        if (key < node->data) {
            // Key is in left subtree
            if (node->left == nullptr) return node;

            // Zig-Zig (Left-Left): key < left->data
            if (key < node->left->data) {
                node->left->left = splay(node->left->left, key);
                node = rotateR(node);  // First rotation: rotate node
            }
            // Zig-Zag (Left-Right): key > left->data
            else if (key > node->left->data) {
                node->left->right = splay(node->left->right, key);
                if (node->left->right != nullptr)
                    node->left = rotateL(node->left);  // Rotate left child
            }
            return (node->left == nullptr) ? node : rotateR(node);
        } else {
            // Key is in right subtree
            if (node->right == nullptr) return node;

            // Zig-Zig (Right-Right): key > right->data
            if (key > node->right->data) {
                node->right->right = splay(node->right->right, key);
                node = rotateL(node);  // First rotation
            }
            // Zig-Zag (Right-Left): key < right->data
            else if (key < node->right->data) {
                node->right->left = splay(node->right->left, key);
                if (node->right->left != nullptr)
                    node->right = rotateR(node->right);
            }
            return (node->right == nullptr) ? node : rotateL(node);
        }
    }

    void inorder(SplayNode* t) {
        if (t == nullptr) return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    void destroy(SplayNode* t) {
        if (t == nullptr) return;
        destroy(t->left);
        destroy(t->right);
        delete t;
    }

public:
    SplayTree() : root(nullptr) {}
    ~SplayTree() { destroy(root); }

    void insert(int val) {
        if (root == nullptr) { root = new SplayNode(val); return; }
        root = splay(root, val);
        if (root->data == val) return;  // duplicate

        SplayNode* newNode = new SplayNode(val);
        if (val < root->data) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        root = newNode;
    }

    bool find(int val) {
        root = splay(root, val);
        return root != nullptr && root->data == val;
    }

    void print() {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
        if (root) cout << "Root: " << root->data << endl;
    }
};

// ===== Red-Black Tree Properties Check (Conceptual) =====
void printRBTreeProperties() {
    cout << "Red-Black Tree Rules:" << endl;
    cout << "  1. Root is BLACK" << endl;
    cout << "  2. RED node's children must be BLACK (no two reds in a row)" << endl;
    cout << "  3. Every null path has the same number of BLACK nodes" << endl;
    cout << endl;
    cout << "Consequences:" << endl;
    cout << "  - Every red node is either a full node or a leaf" << endl;
    cout << "  - If a node has one child, that child is a red leaf" << endl;
    cout << "  - Height <= 2 * log2(n+1)" << endl;
    cout << endl;
    cout << "Insertion:" << endl;
    cout << "  1. Insert new node as RED" << endl;
    cout << "  2. If parent is BLACK -> done" << endl;
    cout << "  3. If parent is RED -> red-red violation!" << endl;
    cout << "     a. Uncle is BLACK -> rotate (like AVL LL/RR/LR/RL)" << endl;
    cout << "     b. Uncle is RED -> recolor (parent, uncle, grandparent)" << endl;
    cout << "        then recurse to grandparent" << endl;
    cout << "  4. If root becomes RED, color it BLACK" << endl;
    cout << endl;
    cout << "Bottom-up vs Top-down:" << endl;
    cout << "  Bottom-up: insert then fix from leaf to root (needs recursion)" << endl;
    cout << "  Top-down: fix while descending (no recursion, at most 1 rotation)" << endl;
    cout << endl;
    cout << "AVL vs Red-Black:" << endl;
    cout << "  AVL: shorter height -> faster search" << endl;
    cout << "  RB: fewer rotations on insert/delete, simpler implementation" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  Splay Tree Demo" << endl;
    cout << "========================================" << endl;

    SplayTree splay;
    int data[] = {6, 3, 8, 1, 5, 7, 4, 2};
    cout << "\nInserting: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    for (int x : data) {
        splay.insert(x);
        cout << "Insert " << x << ": ";
        splay.print();
    }

    cout << "\n--- Find operations (splays to root) ---" << endl;
    cout << "Find 5: ";
    splay.find(5);
    splay.print();

    cout << "Find 1: ";
    splay.find(1);
    splay.print();

    cout << "\n========================================" << endl;
    cout << "  Red-Black Tree Properties" << endl;
    cout << "========================================" << endl;
    printRBTreeProperties();

    cout << "\n========================================" << endl;
    cout << "  Balanced Tree Comparison" << endl;
    cout << "========================================" << endl;
    cout << "                  AVL              Red-Black          Splay" << endl;
    cout << "Height bound:     1.44*log2(n)     2*log2(n+1)        Amortized O(log n)" << endl;
    cout << "Search:           O(log n)         O(log n)           Amortized O(log n)" << endl;
    cout << "Insert:           O(log n)         O(log n)           Amortized O(log n)" << endl;
    cout << "Delete:           O(log n)         O(log n)           Amortized O(log n)" << endl;
    cout << "Rotations/insert: At most 1         At most 2          Splay operations" << endl;
    cout << "Rotations/delete: Up to O(log n)    Up to O(log n)     Splay operations" << endl;
    cout << "Extra storage:    Height field      Color bit          None" << endl;
    cout << "Self-adjusting:   No               No                 Yes" << endl;

    return 0;
}
