# Data Structures - Code Examples & Snapshots

> Complementary reference to the theoretical knowledge in the root folder.
> All code examples are from `example_code/` folder.

---

## Table of Contents
1. [Trees](#1-trees)
2. [Heaps](#2-heaps)
3. [Linked Lists](#3-linked-lists)
4. [Stacks & Queues](#4-stacks--queues)
5. [Hash Tables](#5-hash-tables)
6. [Graphs](#6-graphs)
7. [Sorting](#7-sorting)
8. [Advanced Structures](#8-advanced-structures)

---

## 1. Trees

**EXAM TIP**: Trees are the most tested topic! Focus on understanding rotations (AVL), color properties (Red-Black), and heap properties.

### 1.1 Binary Search Tree (BST)
**File:** `example_code/01_bst.cpp`

```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
```

**Core Operations:**

```cpp
// INSERT - O(h)
TreeNode* insert(TreeNode* node, int val) {
    if (node == nullptr) return new TreeNode(val);
    if (val < node->data)
        node->left = insert(node->left, val);
    else if (val > node->data)
        node->right = insert(node->right, val);
    return node;
}

// DELETE - O(h) - Three cases
TreeNode* remove(TreeNode* node, int val) {
    if (node == nullptr) return nullptr;
    if (val < node->data) {
        node->left = remove(node->left, val);
    } else if (val > node->data) {
        node->right = remove(node->right, val);
    } else {
        // Case 1: Leaf node
        if (node->left == nullptr && node->right == nullptr) {
            delete node; return nullptr;
        }
        // Case 2: One child
        if (node->left == nullptr) { TreeNode* t = node->right; delete node; return t; }
        if (node->right == nullptr) { TreeNode* t = node->left; delete node; return t; }
        // Case 3: Two children - replace with inorder successor
        TreeNode* successor = findMin(node->right);
        node->data = successor->data;
        node->right = remove(node->right, successor->data);
    }
    return node;
}

// INORDER TRAVERSAL - gives sorted order
void inorder(TreeNode* node) {
    if (node == nullptr) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}
```

**Snapshot - Tree Structure:**
```
        50
       /  \
     30    70
    / \   / \
  20  40 60  80
```

---

### 1.2 AVL Tree (Self-Balancing)
**File:** `example_code/03_avl.cpp`

**EXAM TIP**: AVL trees maintain |height(left) - height(right)| ≤ 1 for every node. Height is at most 1.44·log₂(n).

```cpp
struct AVLNode {
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int val) : data(val), height(0), left(nullptr), right(nullptr) {}
};
```

**Rotation Operations:**

```cpp
// SINGLE RIGHT ROTATION (LL Case)
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

// SINGLE LEFT ROTATION (RR Case)
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

// DOUBLE ROTATION: LEFT-RIGHT (LR Case)
AVLNode* dblRotateL(AVLNode* v) {
    v->left = rotateR(v->left);  // First, fix the left child (RR on left)
    return rotateL(v);            // Then, rotate current node (LL)
}

// DOUBLE ROTATION: RIGHT-LEFT (RL Case)
AVLNode* dblRotateR(AVLNode* v) {
    v->right = rotateL(v->right);  // First, fix the right child (LR on right)
    return rotateR(v);              // Then, rotate current node (RR)
}
```

**Insert with Balancing:**
```cpp
AVLNode* insert(AVLNode* t, int val) {
    if (t == nullptr) return new AVLNode(val);
    if (val < t->data) t->left = insert(t->left, val);
    else if (val > t->data) t->right = insert(t->right, val);
    else return t;  // duplicate

    updateHeight(t);
    int balance = getBalance(t);

    // LL case: left-heavy, inserted in left-left
    if (balance > 1 && val < t->left->data) return rotateL(t);
    // RR case: right-heavy, inserted in right-right
    if (balance < -1 && val > t->right->data) return rotateR(t);
    // LR case: left-heavy, inserted in left-right
    if (balance > 1 && val > t->left->data) return dblRotateL(t);
    // RL case: right-heavy, inserted in right-left
    if (balance < -1 && val < t->right->data) return dblRotateR(t);
    return t;
}
```

**Rotation Cases Snapshot:**
```
LL Case (single right):
      30              20
     /  \            /  \
   20    C    =>    A    30
  /  \                  /  \
 A    B                B    C

RR Case (single left):
   10                  20
  /  \                /  \
 A   20      =>      10    C
    /  \            /  \
   B    C          A    B

LR Case (double):
      30               30               20
     /  \             /  \             /  \
   10    D    =>    20    D    =>    10    30
  /  \             /  \             /  \  /  \
 A   20           10    C          A    B C    D
    /  \         /  \
   B    C       A    B

RL Case (double):
   10                 10                 20
  /  \               /  \               /  \
 A   30      =>     A   20      =>     10    30
    /  \               /  \           /  \  /  \
   20   D             B    30        A    B C    D
  /  \                    /  \
 B    C                  C    D
```

---

### 1.3 Red-Black Tree
**Files:** `example_code/10_splay_and_rb.cpp`, `example_code/15_redblack.cpp`

**EXAM TIP**: Red-Black trees are used in C++ STL (map, set). They allow more efficient insert/delete than AVL at the cost of slightly slower search.

```cpp
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
```

**Properties:**
1. Root is BLACK
2. No two RED nodes in a row
3. Every null path has same # of BLACK nodes

**Insert Fix (Bottom-up):**
```cpp
// Note: This conceptual snippet treats nullptr as a BLACK leaf.
void fixInsert(RBNode* z) {
    while (z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* uncle = z->parent->parent->right;
            // Case 1: Uncle is RED -> recolor
            if (uncle != nullptr && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            // Case 2: Uncle is BLACK, z is right child -> rotate
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
        }
        // Mirror cases for right child...
    }
    root->color = BLACK;
}
```

**Comparison: AVL vs Red-Black**
```
                  AVL              Red-Black
Height bound:     1.44*log2(n)     2*log2(n+1)
Search:           Faster           Slightly slower
Insert rotations: At most 1        At most 2
Delete rotations: Up to O(log n)   Up to O(log n)
Extra storage:    1 byte (height)  1 bit (color)
Use case:         Read-heavy       Insert/delete-heavy
```

---

### 1.4 Splay Tree (Self-Adjusting)
**File:** `example_code/10_splay_and_rb.cpp`

```cpp
// SPLAY: Bring node with given key to root
SplayNode* splay(SplayNode* node, int key) {
    if (node == nullptr || node->data == key) return node;

    if (key < node->data) {
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
                node->left = rotateL(node->left);
        }
        return (node->left == nullptr) ? node : rotateR(node);
    } else {
        // Mirror cases for right subtree...
    }
}
```

**Splay Operation Snapshot:**
```
Zig (single right rotation):
      z                 x
     / \               / \
    x   D      =>     A   z
   / \                   / \
  A   B                 B   D

Zag (single left rotation):
    z                     x
   / \                   / \
  A   x        =>       z   D
     / \               / \
    B   D             A   B

Zig-Zig (Left-Left):
        z                   x
       / \                 / \
      y   D       =>      A   y
     / \                     / \
    x   C                   B   z
   / \                         / \
  A   B                       C   D

Zag-Zag (Right-Right):
    z                           x
   / \                         / \
  A   y           =>          y   D
     / \                     / \
    B   x                   z   C
       / \                 / \
      C   D               A   B

Zig-Zag (Left-Right):
      z                   z                   x
     / \                 / \                 / \
    y   D       =>      x   D       =>      y   z
   / \                 / \                 / \ / \
  A   x               y   C               A  B C  D
     / \             / \
    B   C           A   B

Zag-Zig (Right-Left):
    z                     z                     x
   / \                   / \                   / \
  A   y        =>       A   x        =>       z   y
     / \                   / \               / \ / \
    x   D                 B   y             A  B C  D
   / \                       / \
  B   C                     C   D
```

---

### 1.5 k-d Tree (k-Dimensional)
**File:** `example_code/13_kd_tree.cpp`

```cpp
struct Point {
    double x, y;
    int id;
};

struct KdNode {
    Point point;
    KdNode* left;
    KdNode* right;
    KdNode(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};
```

**Build Balanced Tree:**
```cpp
KdNode* build(vector<Point>& points, int start, int end, int depth) {
    if (start >= end) return nullptr;
    int axis = depth % 2;  // 0 = x-axis, 1 = y-axis
    int mid = (start + end) / 2;
    nth_element(points.begin() + start, points.begin() + mid, points.begin() + end,
        [axis](const Point& a, const Point& b) {
            return axis == 0 ? a.x < b.x : a.y < b.y;
        });
    KdNode* node = new KdNode(points[mid]);
    node->left = build(points, start, mid, depth + 1);
    node->right = build(points, mid + 1, end, depth + 1);
    return node;
}
```

**Range Search:**
```cpp
void rangeSearch(KdNode* node, double x1, double y1, double x2, double y2,
                 int depth, vector<Point>& result) {
    if (node == nullptr) return;
    double px = node->point.x, py = node->point.y;
    if (px >= x1 && px <= x2 && py >= y1 && py <= y2)
        result.push_back(node->point);
    int axis = depth % 2;
    if (axis == 0) {
        if (x1 <= px) rangeSearch(node->left, x1, y1, x2, y2, depth + 1, result);
        if (x2 >= px) rangeSearch(node->right, x1, y1, x2, y2, depth + 1, result);
    } else {
        if (y1 <= py) rangeSearch(node->left, x1, y1, x2, y2, depth + 1, result);
        if (y2 >= py) rangeSearch(node->right, x1, y1, x2, y2, depth + 1, result);
    }
}
```

**Snapshot - k-d Tree Space Partitioning:**
```
Depth 0:
  Split by x = 0.5 (vertical line)

       x < 0.5   |   x >= 0.5
                 |

Depth 1:
  In left region:  split by y = 0.3 (horizontal line)
  In right region: split by y = 0.7 (horizontal line)

       left half                  right half
     y >= 0.3                    y >= 0.7
          ---                        ---
     y <  0.3                    y <  0.7

Depth 2:
  Split by x again inside each remaining subregion

Axis order by depth: x -> y -> x -> y -> ...
```

---

### 1.6 Treap (Tree + Heap)
**File:** `example_code/18_treap_pairing_heap.cpp`

```cpp
struct TreapNode {
    int key;
    int priority;  // Random, heap-ordered
    TreapNode* left;
    TreapNode* right;
};
```

**Insert with Rotation:**
```cpp
TreapNode* insert(TreapNode* t, int key, int priority) {
    if (!t) return new TreapNode(key, priority);
    if (key < t->key) {
        t->left = insert(t->left, key, priority);
        if (t->left->priority > t->priority)
            t = rotateR(t);  // Rotate up to maintain heap property
    } else if (key > t->key) {
        t->right = insert(t->right, key, priority);
        if (t->right->priority > t->priority)
            t = rotateL(t);
    }
    return t;
}
```

**Snapshot - Treap Structure:**
```
BST by key, max-heap by priority:

            50 (p=95)
           /         \
     30 (p=80)     70 (p=70)
      /     \       /      \
20 (p=60) 40 (p=50) 60 (p=40) 80 (p=30)
```

---

## 2. Heaps

**EXAM TIP**: Heaps are always complete binary trees. Binary heap has O(n) merge, which is why leftist/skew heaps exist.

### 2.1 Binary Min-Heap
**File:** `example_code/02_heap.cpp`

**EXAM TIP**: Binary heap is stored in a 1-indexed array. Parent of k is k/2, children are 2k and 2k+1.

**Structure:** 1-indexed array (complete binary tree)

```cpp
class MinHeap {
    int* array;      // 1-indexed
    int capacity;
    int count;
};
```

**Core Operations:**
```cpp
// PERCOLATE UP - Restore heap after push
void percolateUp(int pos) {
    while (pos > 1 && array[pos / 2] > array[pos]) {
        swap(array[pos], array[pos / 2]);
        pos /= 2;
    }
}

// PERCOLATE DOWN - Restore heap after pop
void percolateDown(int pos) {
    while (2 * pos <= count) {
        int child = 2 * pos;  // left child
        if (child + 1 <= count && array[child + 1] < array[child])
            child++;  // choose smaller child
        if (array[pos] > array[child]) {
            swap(array[pos], array[child]);
            pos = child;
        } else break;
    }
}

// PUSH - O(log n)
void push(int val) {
    array[++count] = val;
    percolateUp(count);
}

// POP - O(log n)
int pop() {
    int minVal = array[1];
    array[1] = array[count--];
    percolateDown(1);
    return minVal;
}
```

**Heap Sort (In-Place):**
```cpp
void heapSort(int a[], int n) {
    buildMaxHeap(a, n);  // Phase 1: O(n)
    for (int i = n; i > 1; i--) {
        swap(a[1], a[i]);       // Move max to end
        heapify(a, i - 1, 1);  // Restore heap: O(log n)
    }
}
```

**Snapshot - Heap Array Representation:**
```
1-indexed array:
Index:  0  1  2  3  4  5   6   7
Value:  _  3  5  7  8  9  11  13

Tree:
            3
          /   \
         5     7
        / \   / \
       8   9 11  13
```

---

### 2.2 Leftist Heap
**File:** `example_code/12_leftist_heap.cpp`

**EXAM TIP**: Leftist heap's key advantage is O(log n) merge. All operations work along the rightmost path.

```cpp
struct LeftistNode {
    int data;
    int npl;           // Null-path length: shortest distance to non-full node
    LeftistNode* left;
    LeftistNode* right;
};
```

**Merge Operation (Core):**
```cpp
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
```

**Snapshot - Leftist Heap Property:**
```
Leftist Property: npl(left) >= npl(right)

Example of a leftist heap:
        5(npl=1)
       /        \
   8(npl=1)   10(npl=0)
   /    \
12(npl=0) 15(npl=0)

NOT leftist:
        5(npl=2)
       /        \
  10(npl=0)   8(npl=1)
              /    \
         12(npl=0) 15(npl=0)

After swapping children to restore leftist property:
        5(npl=1)
       /        \
   8(npl=1)   10(npl=0)
   /    \
12(npl=0) 15(npl=0)
```

---

### 2.3 Skew Heap (Self-Adjusting)
**File:** `example_code/17_amortized_advanced_heaps.cpp`

**EXAM TIP**: Skew heap is like leftist heap but always swaps children after merge. Simpler but O(log n) amortized instead of worst-case.

```cpp
// Key difference from leftist heap: Always swap children after merge
static SkewNode* merge(SkewNode* a, SkewNode* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->data > b->data) swap(a, b);

    a->right = merge(a->right, b);
    swap(a->left, a->right);  // KEY: Always swap children
    return a;
}
```

**Comparison:**
```
                Binary Heap   Leftist Heap   Skew Heap
Push:           O(1)* avg     O(log n)       O(log n) amort
Pop:            O(log n)      O(log n)       O(log n) amort
Merge:          O(n)          O(log n)       O(log n) amort
Structure:      Complete tree  Right-heavy    No structure!
```

---

### 2.4 Binomial Queue
**File:** `example_code/17_amortized_advanced_heaps.cpp`

**EXAM TIP**: Binomial queue merge is like binary addition. B0+B0=B1, B1+B1=B2, etc.

```cpp
struct BinomialNode {
    int data;
    int order;  // Degree = number of children
    BinomialNode* child;
    BinomialNode* sibling;
    BinomialNode* parent;
};
```

**Link Two Binomial Trees:**
```cpp
static BinomialNode* link(BinomialNode* t1, BinomialNode* t2) {
    if (t1->data > t2->data) swap(t1, t2);
    t2->parent = t1;
    t2->sibling = t1->child;
    t1->child = t2;
    t1->order++;
    return t1;
}
```

**Snapshot - Binomial Queue Structure:**
```
Binomial Queue with 13 elements:

  B0 (order 0, 1 node):
      5

  B2 (order 2, 4 nodes):
        2
       / \
      4   6
     /
    8

  B3 (order 3, 8 nodes):
          1
        / | \
       3  5  7
      /\  |
     9 11 13
    /
   15

Binary representation of 13: 1101 = 8 + 4 + 1
So the queue contains B3, B2, and B0.
```

---

### 2.5 Pairing Heap
**File:** `example_code/18_treap_pairing_heap.cpp`

```cpp
struct PairingNode {
    int data;
    PairingNode* child;
    PairingNode* next;  // Sibling
};
```

**Two-Pass Merge (DeleteMin):**
```cpp
PairingNode* combineChildren(PairingNode* firstChild) {
    if (!firstChild || !firstChild->next) return firstChild;

    // Collect all children
    PairingNode* arr[64];
    int count = 0;
    for (PairingNode* c = firstChild; c && count < 64; c = c->next)
        arr[count++] = c;

    // Pass 1: Pair up left-to-right
    for (int i = 0; i < count - 1; i += 2)
        arr[i] = merge(arr[i], arr[i+1]);

    // Pass 2: Merge right-to-left
    PairingNode* result = (count % 2 == 0) ? arr[count-2] : arr[count-1];
    for (int i = (count % 2 == 0 ? count-4 : count-2); i >= 0; i -= 2)
        result = merge(arr[i], result);

    return result;
}
```

---

## 3. Linked Lists

### 3.1 Singly Linked List
**File:** `example_code/09_linkedlist.cpp`

```cpp
struct SinglyNode {
    int data;
    SinglyNode* next;
    SinglyNode(int val) : data(val), next(nullptr) {}
};
```

**Operations:**
```cpp
// INSERT AT HEAD - O(1)
void insertFront(int val) {
    SinglyNode* newNode = new SinglyNode(val);
    newNode->next = head;
    head = newNode;
}

// INSERT SORTED - O(n)
void insertSorted(int val) {
    SinglyNode* newNode = new SinglyNode(val);
    if (head == nullptr || val < head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }
    SinglyNode* curr = head;
    while (curr->next && curr->next->data < val)
        curr = curr->next;
    newNode->next = curr->next;
    curr->next = newNode;
}

// REMOVE - O(n)
void remove(int val) {
    if (head == nullptr) return;
    if (head->data == val) {
        SinglyNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    SinglyNode* curr = head;
    while (curr->next && curr->next->data != val)
        curr = curr->next;
    if (curr->next) {
        SinglyNode* temp = curr->next;
        curr->next = temp->next;
        delete temp;
    }
}
```

**Snapshot - Sorted Insert:**
```
head -> [1] -> [3] -> [5] -> [8] -> NULL

Insert sorted 7:
head -> [1] -> [3] -> [5] -> [7] -> [8] -> NULL
```

---

### 3.2 Doubly Linked List
**File:** `example_code/09_linkedlist.cpp`

```cpp
struct DoublyNode {
    int data;
    DoublyNode* prev;
    DoublyNode* next;
    DoublyNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};
```

**O(1) Removal (given pointer):**
```cpp
void removeNode(DoublyNode* node) {
    if (!node) return;
    if (node->prev) node->prev->next = node->next;
    else head = node->next;
    if (node->next) node->next->prev = node->prev;
    else tail = node->prev;
    delete node;
}
```

**Snapshot - Doubly Linked Removal:**
```
head                               tail
 |                                  |
 v                                  v
NULL <-> [1] <-> [2] <-> [3] <-> [4] <-> NULL

Remove 2:
head                      tail
 |                         |
 v                         v
NULL <-> [1] <-> [3] <-> [4] <-> NULL
```

---

## 4. Stacks & Queues

### 4.1 Stack (LIFO)
**File:** `example_code/05_stack.cpp`

```cpp
template <typename T>
class Stack {
    T* array;
    int topIdx;
    int capacity;
public:
    void push(T val) { array[++topIdx] = val; }
    T pop() { return array[topIdx--]; }
    T top() const { return array[topIdx]; }
    bool isEmpty() const { return topIdx == -1; }
};
```

**Application: Postfix Evaluation**
```cpp
int evaluatePostfix(string expr) {
    Stack<int> s;
    for (char c : expr) {
        if (isdigit(c)) {
            s.push(c - '0');
        } else {
            int op2 = s.pop();
            int op1 = s.pop();
            switch (c) {
                case '+': s.push(op1 + op2); break;
                case '-': s.push(op1 - op2); break;
                case '*': s.push(op1 * op2); break;
                case '/': s.push(op1 / op2); break;
            }
        }
    }
    return s.pop();
}
// "62+31-4*7+*" => (6+2)*((3-1)*4+7) = 120
```

**Application: Balanced Symbols**
```cpp
bool isBalanced(string s) {
    Stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') stk.push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (stk.isEmpty()) return false;
            char top = stk.pop();
            if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{'))
                return false;
        }
    }
    return stk.isEmpty();
}
```

---

### 4.2 Circular Queue (FIFO)
**File:** `example_code/06_queue.cpp`

```cpp
template <typename T>
class CircularQueue {
    T* array;
    int frontIdx, rearIdx, capacity, count;
public:
    void enqueue(T val) {
        rearIdx = (rearIdx + 1) % capacity;
        array[rearIdx] = val;
        count++;
    }
    T dequeue() {
        T val = array[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        count--;
        return val;
    }
};
```

**Snapshot - Circular Behavior:**
```
Capacity=5, Enqueue 10,20,30,40:
[10, 20, 30, 40, _]  front=0, rear=3

Dequeue 2:
[10, 20, 30, 40, _]  front=2, rear=3  (30 is now at front)

Enqueue 50,60,70:
  enqueue 50 -> [10, 20, 30, 40, 50]  front=2, rear=4
  enqueue 60 -> [60, 20, 30, 40, 50]  front=2, rear=0
  enqueue 70 -> [60, 70, 30, 40, 50]  front=2, rear=1

Current logical queue order:
front -> 30 -> 40 -> 50 -> 60 -> 70 -> rear
```

---

## 5. Hash Tables

### 5.1 Linear Probing
**File:** `example_code/08_hashing.cpp`

```cpp
class LinearProbingHashTable {
    int* table;
    static const int EMPTY = -1;
    static const int DELETED = -2;

    int hash(int key) const { return key % capacity; }

    bool insert(int key) {
        int idx = hash(key);
        while (table[idx] != EMPTY && table[idx] != DELETED) {
            if (table[idx] == key) return false;  // duplicate
            idx = (idx + 1) % capacity;  // Linear probe
        }
        table[idx] = key;
        return true;
    }
};
```

**Snapshot - Collision Resolution:**
```
h(4371) = 4371 % 11 = 4
h(1323) = 1323 % 11 = 3
h(6173) = 6173 % 11 = 2
h(4199) = 4199 % 11 = 8
h(4344) = 4344 % 11 = 10
h(9679) = 9679 % 11 = 10 (COLLISION!) -> probe to 0

Table: [9679, _, 6173, 1323, 4371, _, _, _, 4199, _, 4344]
Index:  0     1  2     3     4     5  6  7  8     9  10
```

---

### 5.2 Quadratic Probing
**File:** `example_code/08_hashing.cpp`

```cpp
bool insert(int key) {
    int idx = hash(key);
    int probe = 0;
    while (table[idx] != EMPTY) {
        if (table[idx] == key) return false;
        probe++;
        idx = (hash(key) + probe * probe) % capacity;  // h+1², h+2², h+3²...
        if (probe >= capacity) return false;
    }
    table[idx] = key;
    return true;
}
```

---

### 5.3 Separate Chaining
**File:** `example_code/08_hashing.cpp`

```cpp
class ChainingHashTable {
    vector<list<int>> table;

    void insert(int key) {
        int idx = hash(key);
        for (int x : table[idx])
            if (x == key) return;  // duplicate
        table[idx].push_back(key);
    }
};
```

**Snapshot - Separate Chaining Buckets:**
```
Chain: [0] -> NULL
Chain: [1] -> NULL
Chain: [2] -> 6173 -> NULL
Chain: [3] -> 1323 -> NULL
Chain: [4] -> 4371 -> NULL
Chain: [5] -> NULL
Chain: [6] -> NULL
Chain: [7] -> NULL
Chain: [8] -> 4199 -> NULL
Chain: [9] -> NULL
Chain: [10] -> 4344 -> 9679 -> NULL  (collisions chain here)
```

---

### 5.4 Cuckoo Hashing
**File:** `example_code/20_cuckoo_hashing.cpp`

```cpp
class CuckooHashTable {
    vector<int> table1, table2;  // Two tables
    int h1(int key) const { return key % size; }
    int h2(int key) const { return (key / size) % size; }

    bool insert(int key) {
        int pos = h1(key);
        for (int i = 0; i < 2 * size; i++) {
            if (table1[pos] == -1) { table1[pos] = key; return true; }
            swap(table1[pos], key);  // Evict to table2
            pos = h2(key);
            if (table2[pos] == -1) { table2[pos] = key; return true; }
            swap(table2[pos], key);  // Evict to table1
            pos = h1(key);
        }
        rehash();  // Too many evictions
        return insert(key);
    }
};
```

**Snapshot - Cuckoo Eviction:**
```
Insert 10: h1(10)=3, h2(10)=1
Table1: [_, _, _, 10, _, _, _]  (placed at h1)

Insert 22: h1(22)=1, h2(22)=3
Table1: [_, 22, _, 10, _, _, _]

Insert 31: h1(31)=3 (COLLISION with 10!)
  Evict 10 -> try h2(10)=1 in Table2
Table1: [_, 22, _, 31, _, _, _]
Table2: [_, 10, _, _, _, _, _]
```

---

### 5.5 Extendible Hashing
**File:** `example_code/20_cuckoo_hashing.cpp`

```cpp
class ExtendibleHashing {
    struct Bucket {
        int localDepth;
        int capacity;
        vector<int> data;
    };
    vector<Bucket*> directory;
    int globalDepth;

    void splitBucket(int idx) {
        Bucket* old = directory[idx];
        if (old->localDepth >= globalDepth) {
            // Double directory
            directory.resize(directory.size() * 2);
            globalDepth++;
        }
        old->localDepth++;
        // Split into two buckets using new bit
    }
};
```

**Snapshot - Directory Doubling:**
```
Initial:
  globalDepth = 1
  0 -> B0   (localDepth = 1)
  1 -> B1   (localDepth = 1)

Directory doubles before split:
  globalDepth = 2
  00 -> B0
  01 -> B1
  10 -> B0
  11 -> B1

After splitting B0:
  B0's localDepth becomes 2, so entries that pointed to B0 split by one more bit:

  00 -> B00
  01 -> B1
  10 -> B10
  11 -> B1

Result:
  Only the entries for the split bucket change.
  B1 is still shared by 01 and 11 until B1 itself splits.
```

---

## 6. Graphs

### 6.1 Graph Representation
**File:** `example_code/04_graph_bfs_dfs.cpp`

```cpp
class Graph {
    int V;
    vector<vector<int>> adj;  // Adjacency list
public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);  // undirected
    }
};
```

**Snapshot - Adjacency List:**
```
Graph:
    0 --- 1 --- 2
    |     |     |
    3 --- 4     5
          |
          6

Adjacency List:
0: [1, 3]
1: [0, 2, 4]
2: [1, 5]
3: [0, 4]
4: [1, 3, 6]
5: [2]
6: [4]
```

---

### 6.2 BFS (Breadth-First Search)
**File:** `example_code/04_graph_bfs_dfs.cpp`

```cpp
void BFS(int start) {
    vector<bool> visited(V, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        cout << v << " ";
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
```

**Snapshot - BFS Traversal:**
```
Start at 0:
Queue: [0]
Visit 0 -> enqueue 1,3
Queue: [1,3]

Visit 1 -> enqueue 2,4
Queue: [3,2,4]

Visit 3 -> (4 already visited)
Queue: [2,4]

Visit 2 -> enqueue 5
Queue: [4,5]

Visit 4 -> enqueue 6
Queue: [5,6]

Visit 5 -> (no unvisited neighbors)
Queue: [6]

Visit 6 -> done
BFS Order: 0 1 3 2 4 5 6
```

---

### 6.3 DFS (Depth-First Search)
**File:** `example_code/04_graph_bfs_dfs.cpp`

```cpp
// Recursive
void DFSUtil(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int neighbor : adj[v]) {
        if (!visited[neighbor])
            DFSUtil(neighbor, visited);
    }
}

// Iterative with Stack
void DFS_Iterative(int start) {
    vector<bool> visited(V, false);
    stack<int> s;
    s.push(start);
    while (!s.empty()) {
        int v = s.top(); s.pop();
        if (visited[v]) continue;
        visited[v] = true;
        cout << v << " ";
        for (int i = adj[v].size() - 1; i >= 0; i--)
            if (!visited[adj[v][i]])
                s.push(adj[v][i]);
    }
}
```

**Snapshot - DFS Traversal:**
```
Start at 0:
Stack: [0]
Pop 0, visit -> push 3,1 (reverse order)
Stack: [3,1]

Pop 1, visit -> push 4,2
Stack: [3,4,2]

Pop 2, visit -> push 5
Stack: [3,4,5]

Pop 5, visit -> no unvisited
Stack: [3,4]

Pop 4, visit -> push 6,3
Stack: [3,6,3]

Pop 3, visit -> no unvisited
Stack: [3,6]

Pop 6, visit -> done
Stack: [3]

Pop 3, already visited
DFS Order: 0 1 2 5 4 3 6
```

---

### 6.4 Dijkstra's Shortest Path
**File:** `example_code/16_graph_algorithms.cpp`

```cpp
void dijkstra(const WeightedGraph& g, int src) {
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;  // stale entry

        for (auto [v, w] : g.neighbors(u)) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}
```

**Snapshot - Dijkstra:**
```
Graph:
  0 --10-- 1 --20-- 3
  |        |        |
  5       15       8
  |        |        |
  2 --30-- 4 --50-- 3

Dijkstra from 0:
  to 0: dist=0, path=0
  to 1: dist=10, path=0->1
  to 2: dist=5, path=0->2
  to 3: dist=30, path=0->1->3
  to 4: dist=25, path=0->1->4
```

---

### 6.5 Prim's MST
**File:** `example_code/16_graph_algorithms.cpp`

```cpp
void primMST(const WeightedGraph& g) {
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;

        for (auto [v, wt] : g.neighbors(u)) {
            if (!inMST[v] && wt < key[v]) {
                key[v] = wt;
                parent[v] = u;
                pq.push({wt, v});
            }
        }
    }
}
```

---

### 6.6 Kruskal's MST
**File:** `example_code/16_graph_algorithms.cpp`

```cpp
void kruskalMST(const WeightedGraph& g) {
    vector<weightedEdge> edges;
    // Collect all edges
    for (int u = 0; u < V; u++)
        for (auto [v, w] : g.neighbors(u))
            if (u < v) edges.push_back({u, v, w});

    sort(edges.begin(), edges.end());  // Sort by weight

    KruskalUF uf(V);
    for (auto [u, v, w] : edges) {
        if (uf.unite(u, v)) {  // No cycle
            cout << u << " -- " << v << " (weight " << w << ")" << endl;
        }
    }
}
```

**Union-Find for Kruskal's:**
```cpp
class KruskalUF {
    vector<int> parent, rank;
public:
    int find(int i) {
        if (parent[i] != i) parent[i] = find(parent[i]);  // Path compression
        return parent[i];
    }
    bool unite(int i, int j) {
        int ri = find(i), rj = find(j);
        if (ri == rj) return false;  // Same set
        if (rank[ri] < rank[rj]) swap(ri, rj);
        parent[rj] = ri;  // Union by rank
        if (rank[ri] == rank[rj]) rank[ri]++;
        return true;
    }
};
```

---

### 6.7 Topological Sort
**File:** `example_code/16_graph_algorithms.cpp`

```cpp
void topologicalSortUtil(int v, const vector<vector<int>>& adj,
                         vector<bool>& visited, vector<int>& result) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u])
            topologicalSortUtil(u, adj, visited, result);
    }
    result.push_back(v);  // Add after all descendants
}

void topologicalSort(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    vector<int> result;
    for (int i = 0; i < V; i++)
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, result);
    reverse(result.begin(), result.end());
}
```

**Snapshot - Topological Sort:**
```
DAG (course prerequisites):
0->1, 0->2, 1->3, 2->3, 2->4, 3->5, 4->5

    0
   / \
  v   v
 1     2
  \   / \
   v v   v
    3     4
     \   /
      v v
       5

Topological order: 0 1 2 3 4 5 (or 0 2 1 4 3 5)
```

---

### 6.8 Disjoint Set (Union-Find)
**File:** `example_code/11_disjoint_set.cpp`

```cpp
class DisjointSet {
    vector<int> parent;  // Negative = root with size
    vector<int> height;
public:
    // Find with Path Compression - amortized O(α(n)) ≈ O(1)
    int find(int i) {
        if (parent[i] < 0) return i;
        parent[i] = find(parent[i]);  // Path compression
        return parent[i];
    }

    // Union by Height
    void unionByHeight(int i, int j) {
        int rootI = find(i), rootJ = find(j);
        if (rootI == rootJ) return;

        if (height[rootI] < height[rootJ]) {
            parent[rootJ] += parent[rootI];
            parent[rootI] = rootJ;
        } else if (height[rootI] > height[rootJ]) {
            parent[rootI] += parent[rootJ];
            parent[rootJ] = rootI;
        } else {
            parent[rootI] += parent[rootJ];
            parent[rootJ] = rootI;
            height[rootI]++;
        }
    }
};
```

**Snapshot - Path Compression:**
```
Before find(4):
    0 (root)
   /|\
  1  2  3
     |
     4

After find(4):
    0 (root)
  /| | \
 1 2  3  4

Node 4 now points directly to the root.
```

---

## 7. Sorting

### 7.1 Comparison Table
**File:** `example_code/07_sorting.cpp`

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Insertion | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Bubble | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |

---

### 7.2 Insertion Sort
```cpp
void insertionSort(int a[], int n) {
    for (int k = 1; k < n; k++) {
        int key = a[k];
        int j = k - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
```

**Snapshot - Insertion Steps:**
```
[34, 15, 65, 59, 79] -> insert 15
[15, 34, 65, 59, 79] -> insert 65 (no change)
[15, 34, 65, 59, 79] -> insert 59
[15, 34, 59, 65, 79] -> insert 79 (no change)
[15, 34, 59, 65, 79] -> sorted!
```

---

### 7.3 Merge Sort
```cpp
void merge(int a[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int* L = new int[n1], *R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = a[left + i];
    for (int j = 0; j < n2; j++) R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void mergeSort(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}
```

**Snapshot - Merge Process:**
```
[34, 15, 65, 59, 79, 42, 40, 80]
           /           \
    [34, 15, 65, 59]  [79, 42, 40, 80]
       /      \         /      \
  [34, 15] [65, 59] [79, 42] [40, 80]
    / \      / \      / \      / \
 [34] [15] [65] [59] [79] [42] [40] [80]

Merge back up:
[15, 34] [59, 65] [42, 79] [40, 80]
   \        /        \        /
[15, 34, 59, 65]  [40, 42, 79, 80]
         \              /
[15, 34, 40, 42, 59, 65, 79, 80]
```

---

### 7.4 Quick Sort
```cpp
int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            swap(a[++i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}
```

**Snapshot - Partition:**
```
[34, 15, 65, 59, 79, 42, 40, 80]  pivot=80
                                ^
i=-1, scan j=0..6

Since every element is < 80, each one stays on the left side.

After partition:
[34, 15, 65, 59, 79, 42, 40, 80]
<-------- all elements less than 80 -------->

Pivot final index = 7  (array unchanged)
```

---

## 8. Advanced Structures

### 8.1 Suffix Array
**File:** `example_code/14_suffix_array.cpp`

```cpp
vector<int> buildSuffixArray(const string& T) {
    int n = T.size();
    vector<int> sa(n), rankArr(n), temp(n);

    // Step 1: Sort by 1st character
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rankArr[i] = T[i];
    }

    // Step 2: Doubling - sort by 2^k characters
    for (int k = 1; k < n; k *= 2) {
        auto compare = [&](int a, int b) {
            if (rankArr[a] != rankArr[b])
                return rankArr[a] < rankArr[b];
            int ra = (a + k < n) ? rankArr[a + k] : -1;
            int rb = (b + k < n) ? rankArr[b + k] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), compare);
        temp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            temp[sa[i]] = temp[sa[i-1]] + (compare(sa[i-1], sa[i]) ? 1 : 0);
        rankArr = temp;
        if (rankArr[sa[n-1]] == n-1) break;
    }
    return sa;
}
```

**Snapshot - Suffix Array for "mississippi":**
```
Some suffixes:
S[0]  = "mississippi"
S[1]  = "ississippi"
S[4]  = "issippi"
S[5]  = "ssippi"
S[6]  = "sippi"
S[7]  = "ippi"
S[8]  = "ppi"
S[9]  = "pi"
S[10] = "i"

Sorted suffix array for "mississippi":
SA[0]  = 10 -> "i"
SA[1]  = 7  -> "ippi"
SA[2]  = 4  -> "issippi"
SA[3]  = 1  -> "ississippi"
SA[4]  = 0  -> "mississippi"
SA[5]  = 9  -> "pi"
SA[6]  = 8  -> "ppi"
SA[7]  = 6  -> "sippi"
SA[8]  = 3  -> "sissippi"
SA[9]  = 5  -> "ssippi"
SA[10] = 2  -> "ssissippi"
```

---

### 8.2 External Sorting
**File:** `example_code/19_external_sorting.cpp`

```cpp
// Phase 1: Create Initial Sorted Runs
vector<vector<int>> createInitialRuns(const vector<int>& data, int memorySize) {
    vector<vector<int>> runs;
    for (int i = 0; i < n; i += memorySize) {
        vector<int> chunk;
        for (int j = i; j < min(i + memorySize, n); j++)
            chunk.push_back(data[j]);
        sort(chunk.begin(), chunk.end());  // Sort in memory
        runs.push_back(chunk);
    }
    return runs;
}

// Phase 2: K-way Merge
vector<int> kWayMerge(vector<vector<int>>& runs) {
    priority_queue<RunElement, vector<RunElement>, greater<>> pq;
    for (int i = 0; i < k; i++)
        if (!runs[i].empty())
            pq.push({runs[i][0], i, 0});

    vector<int> result;
    while (!pq.empty()) {
        RunElement min = pq.top(); pq.pop();
        result.push_back(min.value);
        if (++min.elemIndex < runs[min.runIndex].size())
            pq.push({runs[min.runIndex][min.elemIndex], min.runIndex, min.elemIndex});
    }
    return result;
}
```

**Snapshot - External Sort Process:**
```
Original: [15, 3, 8, 12, 1, 9, 4, 11, 7, 2, 6, 14, 5, 10, 13]
Memory size: 5

Phase 1: Create runs
Run 0: [1, 3, 8, 12, 15]  (sorted chunk 0-4)
Run 1: [2, 4, 7, 9, 11]   (sorted chunk 5-9)
Run 2: [5, 6, 10, 13, 14] (sorted chunk 10-14)

Phase 2: 3-way merge
Min-heap: [1(R0), 2(R1), 5(R2)]
Output: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
```

---

### 8.3 Amortized Analysis
**File:** `example_code/17_amortized_advanced_heaps.cpp`

**Three Methods:**
1. **Aggregate Method:** Total cost of n operations / n
2. **Accounting Method:** Assign different charges to operations
3. **Potential Method:** Amortized cost = actual cost + ΔΦ

**Example: Dynamic Array Doubling**
```
n inserts, each O(1) except when resizing
Resizes at 1, 2, 4, 8, ..., 2^k where 2^k >= n
Total: n + 1 + 2 + 4 + ... + 2^k = n + 2^(k+1) - 1 ≤ 3n
Amortized: 3n/n = O(1) per insert
```

**Key Amortized Results:**
- Stack with multi-pop: O(1) amortized
- Dynamic array push: O(1) amortized
- Splay tree: O(log n) amortized per operation
- Fibonacci heap: O(1) amortized for insert, decreaseKey, merge
- Binomial queue merge: O(log n) amortized

---

## Summary: When to Use What

| Need | Best Choice |
|------|-------------|
| Fast search, sorted order | BST, AVL, Red-Black |
| Fast insert/delete | Red-Black, Splay |
| Priority queue | Binary Heap, Leftist, Pairing |
| Mergeable heaps | Leftist, Skew, Fibonacci |
| Randomized BST | Treap |
| 2D range search | k-d Tree |
| String matching | Suffix Array |
| Disjoint sets | Union-Find |
| Graph shortest path | Dijkstra |
| Graph MST | Prim or Kruskal |
| Large data sorting | External Sort |
| Worst-case O(1) lookup | Cuckoo Hashing |
| Disk-based storage | Extendible Hashing |
