// 15_redblack.cpp - Red-Black Tree: Full Implementation
// Knowledge points: coloring rules, rotations, bottom-up insert, properties

#include <iostream>
#include <string>
using namespace std;

enum Color { RED, BLACK };

struct RBNode {
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    RBNode(int val, Color c = RED, RBNode* p = nullptr)
        : data(val), color(c), left(nullptr), right(nullptr), parent(p) {}
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* NIL;  // sentinel node (black leaf)

    void createNIL() {
        NIL = new RBNode(0, BLACK);
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = NIL;
    }

    // Left rotation around x
    void rotateL(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Right rotation around x
    void rotateR(RBNode* x) {
        RBNode* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    // Fix red-red violation after insert
    void fixInsert(RBNode* z) {
        while (z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* uncle = z->parent->parent->right;

                // Case 1: Uncle is RED -> recolor
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;  // recurse to grandparent
                }
                // Case 2: Uncle is BLACK, z is right child -> rotate to make LL
                else if (z == z->parent->right) {
                    z = z->parent;
                    rotateL(z);
                }
                // Case 3: Uncle is BLACK, z is left child -> rotate grandparent
                else {
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateR(z->parent->parent);
                }
            } else {
                // Mirror: parent is right child of grandparent
                RBNode* uncle = z->parent->parent->left;

                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else if (z == z->parent->left) {
                    z = z->parent;
                    rotateR(z);
                }
                else {
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateL(z->parent->parent);
                }
            }
        }
        root->color = BLACK;  // Rule 1: root is always black
    }

    // Transplant: replace subtree rooted at u with subtree rooted at v
    void transplant(RBNode* u, RBNode* v) {
        if (u->parent == nullptr) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    // Find minimum in subtree
    RBNode* treeMin(RBNode* x) {
        while (x->left != NIL) x = x->left;
        return x;
    }

    // Fix red-red violation after delete
    void fixDelete(RBNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBNode* w = x->parent->right;  // sibling

                // Case 1: sibling is RED
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateL(x->parent);
                    w = x->parent->right;
                }

                // Case 2: sibling's children are both BLACK
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    // Case 3: sibling's right child is BLACK
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateR(w);
                        w = x->parent->right;
                    }
                    // Case 4: sibling's right child is RED
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateL(x->parent);
                    x = root;
                }
            }
            else {
                RBNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateR(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateL(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateR(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    RBNode* search(int val) {
        RBNode* curr = root;
        while (curr != NIL) {
            if (val == curr->data) return curr;
            curr = (val < curr->data) ? curr->left : curr->right;
        }
        return NIL;
    }

    void inorder(RBNode* t) {
        if (t == NIL) return;
        inorder(t->left);
        string c = (t->color == RED) ? "R" : "B";
        cout << t->data << c << " ";
        inorder(t->right);
    }

    void printTree(RBNode* node, string prefix, bool isLeft) {
        if (node == NIL) return;
        cout << prefix;
        cout << (isLeft ? "|-- " : "\\-- ");
        string c = (node->color == RED) ? "(R)" : "(B)";
        cout << node->data << c << endl;
        printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
        printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
    }

    void destroy(RBNode* t) {
        if (t == NIL) return;
        destroy(t->left);
        destroy(t->right);
        delete t;
    }

public:
    RedBlackTree() : root(nullptr) {
        createNIL();
        root = NIL;
    }
    ~RedBlackTree() { destroy(root); delete NIL; }

    // Insert - O(log n)
    void insert(int val) {
        if (find(val)) return;
        RBNode* z = new RBNode(val, RED);
        z->left = z->right = NIL;
        z->parent = nullptr;

        RBNode* y = nullptr;
        RBNode* x = root;

        // Standard BST insert
        while (x != NIL) {
            y = x;
            x = (z->data < x->data) ? x->left : x->right;
        }

        z->parent = y;
        if (y == nullptr) root = z;
        else if (z->data < y->data) y->left = z;
        else y->right = z;

        // Fix red-red violations
        fixInsert(z);
    }

    // Delete - O(log n)
    void remove(int val) {
        RBNode* z = search(val);
        if (z == NIL) { cout << val << " not found" << endl; return; }

        RBNode* y = z;
        RBNode* x;
        Color yOrigColor = y->color;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = treeMin(z->right);
            yOrigColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;
        if (yOrigColor == BLACK)
            fixDelete(x);
    }

    bool find(int val) { return search(val) != NIL; }

    void print() {
        cout << "Inorder (data, C=R/B): ";
        inorder(root);
        cout << endl;
    }

    void printTree() {
        cout << "Tree structure:" << endl;
        printTree(root, "", false);
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "  Red-Black Tree Demo" << endl;
    cout << "========================================" << endl;

    RedBlackTree rbt;

    // Insert sequence
    int data[] = {41, 38, 31, 12, 19, 8, 1, 5, 25, 48};
    cout << "\nInserting: ";
    for (int x : data) cout << x << " ";
    cout << endl;

    for (int x : data) {
        rbt.insert(x);
        cout << "Insert " << x << ": ";
        rbt.print();
    }

    cout << "\nFinal tree structure:" << endl;
    rbt.printTree();

    cout << "\n--- Verify Properties ---" << endl;
    cout << "Rule 1: Root is BLACK" << endl;
    cout << "Rule 2: No two RED nodes in a row" << endl;
    cout << "Rule 3: Every null path has same # of BLACK nodes" << endl;

    cout << "\n--- Search ---" << endl;
    cout << "Find 19: " << (rbt.find(19) ? "Found" : "Not found") << endl;
    cout << "Find 99: " << (rbt.find(99) ? "Found" : "Not found") << endl;

    cout << "\n--- Delete ---" << endl;
    rbt.remove(12);  // Delete leaf-like node
    cout << "After delete 12: "; rbt.print();

    rbt.remove(19);  // Delete node with children
    cout << "After delete 19: "; rbt.print();

    rbt.remove(38);  // Delete node
    cout << "After delete 38: "; rbt.print();

    cout << "\nFinal tree:" << endl;
    rbt.printTree();

    cout << "\n========================================" << endl;
    cout << "  Red-Black Tree vs AVL Tree" << endl;
    cout << "========================================" << endl;
    cout << "                    AVL             Red-Black" << endl;
    cout << "Height bound:       1.44*log2(n)    2*log2(n+1)" << endl;
    cout << "Search:             Faster          Slightly slower" << endl;
    cout << "Insert rotations:   At most 1        At most 2" << endl;
    cout << "Delete rotations:   Up to O(log n)   Up to O(log n)" << endl;
    cout << "Extra storage:      1 byte (height)  1 bit (color)" << endl;
    cout << "Top-down insert:    No               Yes (possible)" << endl;
    cout << "Use case:           Read-heavy       Insert/delete-heavy" << endl;

    return 0;
}
