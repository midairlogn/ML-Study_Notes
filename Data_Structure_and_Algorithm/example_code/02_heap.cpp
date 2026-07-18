// 02_heap.cpp - Binary Min-Heap: Push, Pop, Heap Sort
// Knowledge points: Complete binary tree, array representation, percolate up/down

#include <iostream>
#include <algorithm>
using namespace std;

class MinHeap {
private:
    int* array;
    int capacity;
    int count;

    // Percolate up: restore heap after push
    void percolateUp(int pos) {
        while (pos > 1 && array[pos / 2] > array[pos]) {
            swap(array[pos], array[pos / 2]);
            pos /= 2;
        }
    }

    // Percolate down: restore heap after pop
    void percolateDown(int pos) {
        while (2 * pos <= count) {
            int child = 2 * pos;          // left child
            // Choose the smaller child
            if (child + 1 <= count && array[child + 1] < array[child])
                child++;
            if (array[pos] > array[child]) {
                swap(array[pos], array[child]);
                pos = child;
            } else {
                break;
            }
        }
    }

public:
    MinHeap(int cap = 100) : capacity(cap), count(0) {
        array = new int[capacity + 1];  // 1-indexed
    }
    ~MinHeap() { delete[] array; }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }

    // Push: insert at end, percolate up - O(log n)
    void push(int val) {
        if (count >= capacity) {
            cout << "Heap is full!" << endl;
            return;
        }
        array[++count] = val;
        percolateUp(count);
    }

    // Pop: return min, move last to root, percolate down - O(log n)
    int pop() {
        if (isEmpty()) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        int minVal = array[1];
        array[1] = array[count--];
        percolateDown(1);
        return minVal;
    }

    // Top: return min without removing - O(1)
    int top() const {
        return isEmpty() ? -1 : array[1];
    }

    // Print array representation (1-indexed)
    void printArray() const {
        cout << "Array: [_";
        for (int i = 1; i <= count; i++)
            cout << ", " << array[i];
        cout << "]" << endl;
    }

    // Print tree structure
    void printTree() const {
        if (isEmpty()) { cout << "(empty)" << endl; return; }
        int level = 0, nodesInLevel = 1, idx = 1;
        while (idx <= count) {
            cout << "Level " << level << ": ";
            for (int i = 0; i < nodesInLevel && idx <= count; i++, idx++)
                cout << array[idx] << " ";
            cout << endl;
            level++;
            nodesInLevel *= 2;
        }
    }
};

// ===== Build Max-Heap for Heap Sort =====
void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;
    if (left <= n && a[left] > a[largest]) largest = left;
    if (right <= n && a[right] > a[largest]) largest = right;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void buildMaxHeap(int a[], int n) {
    // Start from last non-leaf node
    for (int i = n / 2; i >= 1; i--)
        heapify(a, n, i);
}

// In-place Heap Sort - O(n log n)
void heapSort(int a[], int n) {
    buildMaxHeap(a, n);                    // Phase 1: O(n)
    for (int i = n; i > 1; i--) {
        swap(a[1], a[i]);                 // Move max to end
        heapify(a, i - 1, 1);            // Restore heap: O(log n)
    }
}

int main() {
    // ===== Part 1: Min-Heap Operations =====
    cout << "========================================" << endl;
    cout << "  Binary Min-Heap Demo" << endl;
    cout << "========================================" << endl;

    MinHeap heap;
    int values[] = {15, 12, 8, 5, 9, 3, 20, 7};

    cout << "\n--- Push operations ---" << endl;
    for (int v : values) {
        heap.push(v);
        cout << "Push " << v << ": ";
        heap.printArray();
    }

    cout << "\nHeap tree structure:" << endl;
    heap.printTree();

    cout << "\n--- Pop operations (extract min) ---" << endl;
    while (!heap.isEmpty()) {
        int val = heap.pop();
        cout << "Popped " << val << ": ";
        heap.printArray();
    }

    // ===== Part 2: Heap Sort =====
    cout << "\n========================================" << endl;
    cout << "  Heap Sort Demo (In-Place)" << endl;
    cout << "========================================" << endl;

    int arr[] = {0, 34, 15, 65, 59, 79, 42, 40, 80, 50, 61, 23, 46};
    // Index 0 unused, data starts at index 1
    int n = 12;

    cout << "\nBefore sorting: ";
    for (int i = 1; i <= n; i++) cout << arr[i] << " ";
    cout << endl;

    // Show the max-heap after buildMaxHeap
    buildMaxHeap(arr, n);
    cout << "After buildMaxHeap: ";
    for (int i = 1; i <= n; i++) cout << arr[i] << " ";
    cout << endl;

    // Complete the sort
    heapSort(arr, n);
    cout << "After heap sort:    ";
    for (int i = 1; i <= n; i++) cout << arr[i] << " ";
    cout << endl;

    // ===== Part 3: Complexity Summary =====
    cout << "\n========================================" << endl;
    cout << "  Complexity Summary" << endl;
    cout << "========================================" << endl;
    cout << "Top (find min):     O(1)" << endl;
    cout << "Push (insert):      O(log n) worst, O(1) average" << endl;
    cout << "Pop (remove min):   O(log n)" << endl;
    cout << "Build max-heap:     O(n)" << endl;
    cout << "Heap sort:          O(n log n) in ALL cases" << endl;
    cout << "Space:              O(1) extra (in-place)" << endl;

    return 0;
}
