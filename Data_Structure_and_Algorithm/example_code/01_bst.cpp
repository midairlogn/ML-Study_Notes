// 01_bst.cpp - Binary Search Tree: Insert, Find, Delete, Traversals
// Knowledge points: BST definition, operations O(h), inorder gives sorted order

#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int val) {
        if (node == nullptr) return new TreeNode(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        // duplicate: do nothing
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    TreeNode* remove(TreeNode* node, int val) {
        if (node == nullptr) return nullptr;
        if (val < node->data) {
            node->left = remove(node->left, val);
        } else if (val > node->data) {
            node->right = remove(node->right, val);
        } else {
            // Case 1: Leaf node
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children - replace with inorder successor (min of right subtree)
            TreeNode* successor = findMin(node->right);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }
        return node;
    }

    bool search(TreeNode* node, int val) {
        if (node == nullptr) return false;
        if (val == node->data) return true;
        return (val < node->data) ? search(node->left, val) : search(node->right, val);
    }

    // Traversals
    void preorder(TreeNode* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(TreeNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(TreeNode* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // Level-order (BFS) using queue
    void levelorder(TreeNode* node) {
        if (node == nullptr) return;
        queue<TreeNode*> nodes;
        nodes.push(node);
        while (!nodes.empty()) {
            TreeNode* curr = nodes.front();
            nodes.pop();
            cout << curr->data << " ";
            if (curr->left) nodes.push(curr->left);
            if (curr->right) nodes.push(curr->right);
        }
    }

    int height(TreeNode* node) {
        if (node == nullptr) return -1;
        int hL = height(node->left);
        int hR = height(node->right);
        return (hL > hR ? hL : hR) + 1;
    }

    int countLeaves(TreeNode* node) {
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

    void destroy(TreeNode* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int val) { root = insert(root, val); }
    void remove(int val) { root = remove(root, val); }
    bool find(int val) { return search(root, val); }

    void printPreorder() { cout << "Preorder:    "; preorder(root); cout << endl; }
    void printInorder() { cout << "Inorder:     "; inorder(root); cout << endl; }
    void printPostorder() { cout << "Postorder:   "; postorder(root); cout << endl; }
    void printLevelorder() { cout << "Level-order: "; levelorder(root); cout << endl; }
    int getHeight() { return height(root); }
    int getLeafCount() { return countLeaves(root); }
};

int main() {
    BST tree;

    // Insert nodes: 50, 30, 70, 20, 40, 60, 80
    //        50
    //       /  \
    //     30    70
    //    / \   / \
    //  20  40 60  80
    int data[] = {50, 30, 70, 20, 40, 60, 80};
    for (int x : data) {
        tree.insert(x);
        cout << "Inserted " << x << endl;
    }

    cout << "\n=== Traversals ===" << endl;
    tree.printPreorder();
    tree.printInorder();     // BST inorder always gives sorted order!
    tree.printPostorder();
    tree.printLevelorder();

    cout << "\n=== Tree Properties ===" << endl;
    cout << "Height: " << tree.getHeight() << endl;
    cout << "Leaf count: " << tree.getLeafCount() << endl;

    cout << "\n=== Search ===" << endl;
    cout << "Find 40: " << (tree.find(40) ? "Found" : "Not found") << endl;
    cout << "Find 25: " << (tree.find(25) ? "Found" : "Not found") << endl;

    cout << "\n=== Delete ===" << endl;
    // Delete leaf node (20)
    tree.remove(20);
    cout << "After deleting 20: ";
    tree.printInorder();

    // Delete node with one child (30 now has only right child 40)
    tree.remove(30);
    cout << "After deleting 30: ";
    tree.printInorder();

    // Delete node with two children (50)
    tree.remove(50);
    cout << "After deleting 50: ";
    tree.printInorder();

    cout << "\n=== Reconstruct from Preorder + Inorder ===" << endl;
    cout << "Given preorder: 50 30 20 40 70 60 80" << endl;
    cout << "Given inorder:  20 30 40 50 60 70 80" << endl;
    cout << "Root = 50 (first in preorder)" << endl;
    cout << "In inorder: [20 30 40] 50 [60 70 80]" << endl;
    cout << "Left subtree: preorder=30 20 40, inorder=20 30 40" << endl;
    cout << "Right subtree: preorder=70 60 80, inorder=60 70 80" << endl;

    return 0;
}
