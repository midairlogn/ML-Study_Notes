// 06_queue.cpp - Queue: Circular Queue, BFS on Tree
// Knowledge points: FIFO, circular array, level-order traversal

#include <iostream>
using namespace std;

// ===== Circular Array-based Queue =====
template <typename T>
class CircularQueue {
private:
    T* array;
    int frontIdx;
    int rearIdx;
    int capacity;
    int count;

public:
    CircularQueue(int cap = 100) : capacity(cap), frontIdx(0), rearIdx(-1), count(0) {
        array = new T[capacity];
    }
    ~CircularQueue() { delete[] array; }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }

    void enqueue(T val) {
        if (isFull()) { cout << "Queue overflow!" << endl; return; }
        rearIdx = (rearIdx + 1) % capacity;
        array[rearIdx] = val;
        count++;
    }

    T dequeue() {
        if (isEmpty()) { cout << "Queue underflow!" << endl; return T(); }
        T val = array[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        count--;
        return val;
    }

    T front() const {
        if (isEmpty()) { cout << "Queue is empty!" << endl; return T(); }
        return array[frontIdx];
    }

    void print() const {
        if (isEmpty()) { cout << "(empty)" << endl; return; }
        cout << "Queue: ";
        for (int i = 0; i < count; i++) {
            cout << array[(frontIdx + i) % capacity] << " ";
        }
        cout << "(front=" << frontIdx << ", rear=" << rearIdx << ")" << endl;
    }
};

// ===== Application: Breadth-First Tree Traversal =====
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void BFS_LevelOrder(TreeNode* root) {
    if (root == nullptr) return;
    CircularQueue<TreeNode*> q(100);
    q.enqueue(root);

    cout << "BFS level-order: ";
    while (!q.isEmpty()) {
        TreeNode* curr = q.dequeue();
        cout << curr->data << " ";
        if (curr->left) q.enqueue(curr->left);
        if (curr->right) q.enqueue(curr->right);
    }
    cout << endl;
}

// ===== Application: Reverse a Stack using Queue =====
// (Conceptual: pop from stack, enqueue, dequeue, push back)
void reverseArray(int arr[], int n) {
    // Simulating stack reversal with queue concept
    CircularQueue<int> q(n);
    for (int i = 0; i < n; i++)
        q.enqueue(arr[i]);
    for (int i = n - 1; i >= 0; i--)
        arr[i] = q.dequeue();
}

int main() {
    cout << "========================================" << endl;
    cout << "  Queue Demo" << endl;
    cout << "========================================" << endl;

    // Basic operations
    cout << "\n--- Basic Queue Operations ---" << endl;
    CircularQueue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.print();

    cout << "Dequeue: " << q.dequeue() << endl;
    cout << "Dequeue: " << q.dequeue() << endl;
    q.print();

    q.enqueue(50);
    q.enqueue(60);
    q.print();

    cout << "\n--- Circular Behavior Demo ---" << endl;
    CircularQueue<int> q2(5);
    for (int i = 1; i <= 7; i++) {
        q2.enqueue(i * 10);
        cout << "Enqueue " << i * 10 << ": ";
        q2.print();
    }

    for (int i = 0; i < 3; i++) {
        cout << "Dequeue: " << q2.dequeue() << " -> ";
        q2.print();
    }

    for (int i = 8; i <= 10; i++) {
        q2.enqueue(i * 10);
        cout << "Enqueue " << i * 10 << ": ";
        q2.print();
    }

    // BFS on tree
    cout << "\n--- BFS on Binary Tree ---" << endl;
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    cout << "Tree:" << endl;
    cout << "        1" << endl;
    cout << "       / \\" << endl;
    cout << "      2   3" << endl;
    cout << "     / \\   \\" << endl;
    cout << "    4   5   6" << endl;

    BFS_LevelOrder(root);

    cout << "\n--- Queue vs Stack ---" << endl;
    cout << "Queue: FIFO (First-In-First-Out) - like a line" << endl;
    cout << "Stack: LIFO (Last-In-First-Out) - like a stack of plates" << endl;
    cout << "Queue applications: BFS, scheduling, printers, buffering" << endl;
    cout << "Circular queue: wraps around, no wasted space" << endl;

    // Clean up
    delete root->left->left;
    delete root->left->right;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
