// 03_avl.cpp - AVL Tree: Rotations, Insert, Height Balance
// Knowledge points: |hL - hR| <= 1, 4 rotation cases (LL, RR, LR, RL)

#include <iostream>
#include <algorithm>
using namespace std;

struct AVLNode {
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int val) : data(val), height(0), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    int h(AVLNode* t) {
        return t == nullptr ? -1 : t->height;
    }

    void updateHeight(AVLNode* t) {
        t->height = max(h(t->left), h(t->right)) + 1;
    }

    // Single Right Rotation (LL case)
    //       v              x
    //      / \            / \
    //     x   C   =>    A   v
    //    / \                / \
    //   A   B              B   C
    AVLNode* rotateL(AVLNode* v) {
        AVLNode* x = v->left;
        v->left = x->right;
        x->right = v;
        updateHeight(v);
        updateHeight(x);
        return x;
    }

    // Single Left Rotation (RR case)
    //     v                x
    //    / \              / \
    //   A   x     =>     v   C
    //      / \          / \
    //     B   C        A   B
    AVLNode* rotateR(AVLNode* v) {
        AVLNode* x = v->right;
        v->right = x->left;
        x->left = v;
        updateHeight(v);
        updateHeight(x);
        return x;
    }

    // Double Rotation: Left-Right (LR case)
    //    v           v              z
    //   / \         / \           /   \
    //  x   C  =>   z   C   =>   x     v
    //   \         / \           / \   / \
    //    z       x   B         A   B C   D
    //   / \     / \
    //  A   B   A   D
    AVLNode* dblRotateL(AVLNode* v) {
        v->left = rotateR(v->left);  // First, fix the left child (RR on left)
        return rotateL(v);            // Then, rotate current node (LL)
    }

    // Double Rotation: Right-Left (RL case)
    //    v         v              z
    //   / \       / \           /   \
    //  A   x  => A   z   =>   v     x
    //     / \       / \       / \   / \
    //    z   D     B   x     A   B C   D
    //   / \           / \
    //  B   C         C   D
    AVLNode* dblRotateR(AVLNode* v) {
        v->right = rotateL(v->right);  // First, fix the right child (LR on right)
        return rotateR(v);              // Then, rotate current node (RR)
    }

    int getBalance(AVLNode* t) {
        return t == nullptr ? 0 : h(t->left) - h(t->right);
    }

    AVLNode* insert(AVLNode* t, int val) {
        if (t == nullptr) return new AVLNode(val);

        if (val < t->data) {
            t->left = insert(t->left, val);
        } else if (val > t->data) {
            t->right = insert(t->right, val);
        } else {
            return t;  // duplicate
        }

        updateHeight(t);
        int balance = getBalance(t);

        // LL case: left-heavy, inserted in left-left
        if (balance > 1 && val < t->left->data)
            return rotateL(t);

        // RR case: right-heavy, inserted in right-right
        if (balance < -1 && val > t->right->data)
            return rotateR(t);

        // LR case: left-heavy, inserted in left-right
        if (balance > 1 && val > t->left->data)
            return dblRotateL(t);

        // RL case: right-heavy, inserted in right-left
        if (balance < -1 && val < t->right->data)
            return dblRotateR(t);

        return t;
    }

    void inorder(AVLNode* t) {
        if (t == nullptr) return;
        inorder(t->left);
        cout << t->data << "(h=" << t->height << ",b=" << getBalance(t) << ") ";
        inorder(t->right);
    }

    void destroy(AVLNode* t) {
        if (t == nullptr) return;
        destroy(t->left);
        destroy(t->right);
        delete t;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }

    void insert(int val) { root = insert(root, val); }

    void print() {
        cout << "Inorder (data,h,balance): ";
        inorder(root);
        cout << endl;
    }

    int getHeight() { return h(root); }
};

int main() {
    cout << "========================================" << endl;
    cout << "  AVL Tree Demo - Rotations" << endl;
    cout << "========================================" << endl;

    AVLTree tree;

    // Demo 1: LL Case - single right rotation
    cout << "\n--- Demo 1: LL Case (single right rotation) ---" << endl;
    cout << "Insert: 30, 20, 10" << endl;
    cout << "Without rotation: 30->20->10 (degenerate, height=2)" << endl;
    cout << "With AVL: right rotate at 30, result: 20 at root" << endl;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    tree.print();
    cout << "Height: " << tree.getHeight() << " (balanced!)" << endl;

    // Demo 2: RR Case - single left rotation
    cout << "\n--- Demo 2: RR Case (single left rotation) ---" << endl;
    cout << "Insert: 10, 20, 30" << endl;
    cout << "Without rotation: 10->20->30 (degenerate)" << endl;
    cout << "With AVL: left rotate at 10, result: 20 at root" << endl;
    AVLTree tree2;
    tree2.insert(10);
    tree2.insert(20);
    tree2.insert(30);
    tree2.print();
    cout << "Height: " << tree2.getHeight() << endl;

    // Demo 3: LR Case - double rotation
    cout << "\n--- Demo 3: LR Case (double rotation) ---" << endl;
    cout << "Insert: 30, 10, 20" << endl;
    cout << "Step 1: Left rotate at 10 (fixes RR in left subtree)" << endl;
    cout << "Step 2: Right rotate at 30 (fixes LL)" << endl;
    AVLTree tree3;
    tree3.insert(30);
    tree3.insert(10);
    tree3.insert(20);
    tree3.print();
    cout << "Height: " << tree3.getHeight() << endl;

    // Demo 4: RL Case - double rotation
    cout << "\n--- Demo 4: RL Case (double rotation) ---" << endl;
    cout << "Insert: 10, 30, 20" << endl;
    AVLTree tree4;
    tree4.insert(10);
    tree4.insert(30);
    tree4.insert(20);
    tree4.print();
    cout << "Height: " << tree4.getHeight() << endl;

    // Demo 5: Larger tree
    cout << "\n--- Demo 5: Insert sequence [20, 10, 30, 5, 15, 25, 35] ---" << endl;
    AVLTree tree5;
    int vals[] = {20, 10, 30, 5, 15, 25, 35};
    for (int v : vals) {
        tree5.insert(v);
        cout << "After insert " << v << ": height = " << tree5.getHeight() << endl;
    }
    tree5.print();

    cout << "\n========================================" << endl;
    cout << "  AVL Tree Properties" << endl;
    cout << "========================================" << endl;
    cout << "Balance condition: |height(left) - height(right)| <= 1 for every node" << endl;
    cout << "Height bound: h <= 1.44 * log2(n) ~ log_phi(n)" << endl;
    cout << "phi (golden ratio) = (1 + sqrt(5)) / 2 ~ 1.618" << endl;
    cout << "LL/RR cases: single rotation" << endl;
    cout << "LR/RL cases: double rotation" << endl;
    cout << "Insert: O(log n) - at most one rotation needed" << endl;
    cout << "Delete: O(log n) - may need O(log n) rotations (cascading)" << endl;

    return 0;
}
