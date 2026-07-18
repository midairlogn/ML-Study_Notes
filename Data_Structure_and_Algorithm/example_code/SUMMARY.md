# Data Structures Code Examples Summary

## Table of Contents
1. [Trees](#trees)
2. [Heaps](#heaps)
3. [Linked Lists](#linked-lists)
4. [Stacks and Queues](#stacks-and-queues)
5. [Hash Tables](#hash-tables)
6. [Graphs](#graphs)
7. [Sorting Algorithms](#sorting-algorithms)
8. [Advanced Data Structures](#advanced-data-structures)

---

## Trees

### Binary Search Tree (BST)
**File:** `01_bst.cpp`

**Structure:**
```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};
```

**Major Operations:**
- **Insert:** O(h) - Compare and traverse left/right
- **Find/Search:** O(h) - Binary comparison
- **Delete:** O(h) - Three cases:
  - Leaf node: simply remove
  - One child: replace with child
  - Two children: replace with inorder successor (min of right subtree)
- **Traversals:**
  - Preorder: Root → Left → Right
  - Inorder: Left → Root → Right (gives sorted order)
  - Postorder: Left → Right → Root
  - Level-order: BFS using queue
- **Height:** O(n)
- **Count Leaves:** O(n)

---

### AVL Tree (Self-Balancing BST)
**File:** `03_avl.cpp`

**Structure:**
```cpp
struct AVLNode {
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;
};
```

**Balance Condition:** |height(left) - height(right)| ≤ 1

**Major Operations:**
- **Rotations:**
  - **Single Right Rotation (LL Case):**
    ```
        v              x
       / \            / \
      x   C   =>    A   v
     / \                / \
    A   B              B   C
    ```
  - **Single Left Rotation (RR Case):**
    ```
        v                x
       / \              / \
      A   x     =>     v   C
         / \          / \
        B   C        A   B
    ```
  - **Double Left-Right Rotation (LR Case):** Left rotate left child, then right rotate node
  - **Double Right-Left Rotation (RL Case):** Right rotate right child, then left rotate node
- **Insert:** O(log n) - At most one rotation needed
- **Delete:** O(log n) - May need O(log n) rotations (cascading)
- **Height Bound:** h ≤ 1.44 × log₂(n)

---

### Red-Black Tree
**Files:** `10_splay_and_rb.cpp`, `15_redblack.cpp`

**Structure:**
```cpp
enum Color { RED, BLACK };

struct RBNode {
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
};
```

**Properties:**
1. Root is BLACK
2. No two RED nodes in a row (RED node's children must be BLACK)
3. Every null path has the same number of BLACK nodes

**Major Operations:**
- **Left Rotation:** O(1)
- **Right Rotation:** O(1)
- **Insert Fix:** O(log n)
  - Case 1: Uncle is RED → Recolor
  - Case 2: Uncle is BLACK, z is right child → Rotate to make LL
  - Case 3: Uncle is BLACK, z is left child → Rotate grandparent
- **Delete Fix:** O(log n) - Four cases for each side
- **Insert:** O(log n) - At most 2 rotations
- **Delete:** O(log n) - Up to O(log n) rotations

---

### Splay Tree (Self-Adjusting BST)
**File:** `10_splay_and_rb.cpp`

**Structure:** Same as BST with splay operation

**Major Operations:**
- **Splay Operation:** Brings accessed node to root
  - **Zig-Zig (Left-Left):** Two right rotations
  - **Zig-Zag (Left-Right):** Left then right rotation
  - **Zag-Zig (Right-Left):** Right then left rotation
  - **Zag-Zag (Right-Right):** Two left rotations
- **Insert:** Amortized O(log n)
- **Find:** Amortized O(log n)
- **Property:** Recently accessed elements are near root

---

### k-d Tree (k-Dimensional Tree)
**File:** `13_kd_tree.cpp`

**Structure:**
```cpp
struct Point {
    double x, y;
    int id;
};

struct KdNode {
    Point point;
    KdNode* left;
    KdNode* right;
};
```

**Major Operations:**
- **Build Balanced:** O(n log n) - Median split alternating axes
  - Depth 0, 2k: Split on x-axis
  - Depth 1, 2k+1: Split on y-axis
- **Insert:** O(log n) average
- **Range Search:** O(√n + |output|) - Prune subtrees outside range
- **Nearest Neighbor:** O(log n) average with pruning

---

### Treap (Tree + Heap)
**File:** `18_treap_pairing_heap.cpp`

**Structure:**
```cpp
struct TreapNode {
    int key;
    int priority;  // Random, heap-ordered
    TreapNode* left;
    TreapNode* right;
};
```

**Properties:**
- BST ordered by key (left < root < right)
- Heap ordered by random priority (parent > children)

**Major Operations:**
- **Insert:** O(log n) expected - BST insert + rotate up by priority
- **Remove:** O(log n) expected - Rotate down to leaf, then delete
- **Rotations:** Maintain both BST and heap properties

---

## Heaps

### Binary Min-Heap
**File:** `02_heap.cpp`

**Structure:** 1-indexed array (complete binary tree)

**Major Operations:**
- **Percolate Up:** O(log n) - Restore heap after push
- **Percolate Down:** O(log n) - Restore heap after pop
- **Push:** O(log n) - Insert at end, percolate up
- **Pop:** O(log n) - Return min, move last to root, percolate down
- **Top:** O(1) - Return minimum
- **Build Max-Heap:** O(n) - From last non-leaf downward
- **Heap Sort:** O(n log n) - Build max-heap, repeatedly extract max

---

### Leftist Heap
**File:** `12_leftist_heap.cpp`

**Structure:**
```cpp
struct LeftistNode {
    int data;
    int npl;           // Null-path length
    LeftistNode* left;
    LeftistNode* right;
};
```

**Properties:**
- **Leftist Property:** npl(left) ≥ npl(right) for every node
- **NPL:** Shortest distance to non-full node (null node)

**Major Operations:**
- **Merge:** O(log n) - Compare roots, merge smaller's right subtree
- **Push:** O(log n) - Merge with single-node heap
- **Pop:** O(log n) - Remove root, merge left and right
- **Merge Two Heaps:** O(log n)

---

### Skew Heap
**File:** `17_amortized_advanced_heaps.cpp`

**Structure:** Same as leftist heap but no NPL stored

**Major Operations:**
- **Merge:** O(log n) amortized - Merge right paths, swap children
- **Push:** O(log n) amortized
- **Pop:** O(log n) amortized
- **Difference from Leftist:** Always swap children (self-adjusting)

---

### Binomial Queue
**File:** `17_amortized_advanced_heaps.cpp`

**Structure:**
```cpp
struct BinomialNode {
    int data;
    int order;  // Degree = number of children
    BinomialNode* child;
    BinomialNode* sibling;
    BinomialNode* parent;
};
```

**Properties:**
- Collection of binomial trees B₀, B₁, B₂, ...
- Bₖ has 2ᵏ nodes
- Merge like binary addition (0+0=0, 0+1=1, 1+1=carry)

**Major Operations:**
- **Insert:** O(1) amortized
- **Merge:** O(log n) amortized
- **DeleteMin:** O(log n)

---

### Fibonacci Heap
**File:** `17_amortized_advanced_heaps.cpp`

**Properties:**
- Collection of heap-ordered trees (lazy merging)
- Cut operation: cut node and add to root list
- Cascading cut: cut parent if already cut once

**Major Operations:**
- **Insert:** O(1) amortized
- **DecreaseKey:** O(1) amortized
- **Merge:** O(1) amortized
- **DeleteMin:** O(log n) amortized
- **Applications:** Dijkstra O(E + V log V), Prim O(E + V log V)

---

### Pairing Heap
**File:** `18_treap_pairing_heap.cpp`

**Structure:**
```cpp
struct PairingNode {
    int data;
    PairingNode* child;
    PairingNode* next;  // Sibling
};
```

**Major Operations:**
- **Push:** O(1) - Merge with single-node heap
- **Pop:** O(log n) amortized - Two-pass merge of children
- **Merge:** O(1) - Make smaller root the new root
- **DecreaseKey:** O(log n) amortized

---

## Linked Lists

### Singly Linked List
**File:** `09_linkedlist.cpp`

**Structure:**
```cpp
struct SinglyNode {
    int data;
    SinglyNode* next;
};
```

**Major Operations:**
- **Insert Front:** O(1)
- **Insert Sorted:** O(n)
- **Remove:** O(n) - Find and remove first occurrence
- **Search:** O(n)
- **Count:** O(n)

---

### Doubly Linked List
**File:** `09_linkedlist.cpp`

**Structure:**
```cpp
struct DoublyNode {
    int data;
    DoublyNode* prev;
    DoublyNode* next;
};
```

**Major Operations:**
- **Insert Front/Back:** O(1)
- **Remove Node (given pointer):** O(1)
- **Remove by Value:** O(n) - Search then remove
- **Forward/Backward Traversal:** O(n)

---

## Stacks and Queues

### Stack (LIFO)
**File:** `05_stack.cpp`

**Structure:** Template array-based implementation

**Major Operations:**
- **Push:** O(1) - Add to top
- **Pop:** O(1) - Remove from top
- **Top/Peek:** O(1) - View top element
- **Applications:**
  - Postfix expression evaluation
  - Balanced symbols checking
  - Infix to postfix conversion

---

### Circular Queue (FIFO)
**File:** `06_queue.cpp`

**Structure:** Template circular array implementation

**Major Operations:**
- **Enqueue:** O(1) - Add to rear (wrap around)
- **Dequeue:** O(1) - Remove from front
- **Front:** O(1) - View front element
- **Applications:** BFS level-order traversal, scheduling

---

## Hash Tables

### Linear Probing
**File:** `08_hashing.cpp`

**Structure:** Array with EMPTY/DELETED markers

**Collision Resolution:**
- **Probe Sequence:** h+1, h+2, h+3, ... (wrap around)
- **Issue:** Primary clustering

**Operations:**
- **Insert:** O(1) average
- **Search:** O(1) average
- **Remove:** Mark as DELETED (lazy deletion)

---

### Quadratic Probing
**File:** `08_hashing.cpp`

**Collision Resolution:**
- **Probe Sequence:** h+1², h+2², h+3², ...
- **Benefit:** No primary clustering

---

### Separate Chaining
**File:** `08_hashing.cpp`

**Structure:** Array of linked lists

**Collision Resolution:**
- Each slot contains a linked list
- Insert at head of list

**Operations:**
- **Insert:** O(1) average
- **Search:** O(1) average (list length depends on load factor)
- **Remove:** O(1) average

---

### Cuckoo Hashing
**File:** `20_cuckoo_hashing.cpp`

**Structure:** Two hash tables with two hash functions

**Collision Resolution:**
- On collision: evict existing element to its alternate table
- Worst-case O(1) lookup

**Operations:**
- **Insert:** Amortized O(1) - May need rehash
- **Search:** O(1) worst-case
- **Delete:** O(1) worst-case

---

### Extendible Hashing
**File:** `20_cuckoo_hashing.cpp`

**Structure:** Directory of pointers with global/local depth

**Properties:**
- Good for disk-based databases
- Directory doubles/halves as needed
- Buckets split when full

**Operations:**
- **Insert:** O(1) - Split bucket if full
- **Search:** O(1) - Follow directory pointer

---

## Graphs

### Graph Representation
**File:** `04_graph_bfs_dfs.cpp`

**Structure:**
```cpp
class Graph {
    int V;
    vector<vector<int>> adj;  // Adjacency list
};
```

---

### BFS (Breadth-First Search)
**File:** `04_graph_bfs_dfs.cpp`

**Algorithm:**
1. Use queue
2. Visit all neighbors at current depth before going deeper
3. Mark visited nodes

**Time:** O(V + E) | **Space:** O(V)

**Applications:**
- Shortest path in unweighted graph
- Level-order traversal
- Connected components

---

### DFS (Depth-First Search)
**File:** `04_graph_bfs_dfs.cpp`

**Algorithm:**
1. Use stack or recursion
2. Explore as deep as possible first
3. Backtrack when needed

**Time:** O(V + E) | **Space:** O(V)

**Applications:**
- Cycle detection
- Topological sort
- Connected components

---

### Dijkstra's Shortest Path
**File:** `16_graph_algorithms.cpp`

**Algorithm:** Greedy - Always process closest unvisited vertex

**Time:** O((V+E) log V) | **Space:** O(V)

**Requirement:** No negative weights

---

### Prim's MST (Minimum Spanning Tree)
**File:** `16_graph_algorithms.cpp`

**Algorithm:** Greedy - Add cheapest edge connecting tree to non-tree

**Time:** O(E log V)

---

### Kruskal's MST
**File:** `16_graph_algorithms.cpp`

**Algorithm:**
1. Sort all edges
2. Add cheapest that doesn't form cycle (using Union-Find)

**Time:** O(E log E)

---

### Topological Sort
**File:** `16_graph_algorithms.cpp`

**Algorithm:** DFS-based on DAG (Directed Acyclic Graph)

**Time:** O(V + E)

---

### Disjoint Set (Union-Find)
**File:** `11_disjoint_set.cpp`

**Structure:**
```cpp
class DisjointSet {
    vector<int> parent;  // Negative = root with size
    vector<int> height;
};
```

**Major Operations:**
- **Find:** Amortized O(α(n)) ≈ O(1) with path compression
- **Union by Height:** O(log n) without path compression
- **Path Compression:** Make every node point directly to root

**Applications:**
- Maze generation
- Connected components
- Kruskal's MST

---

## Sorting Algorithms

### Comparison Summary
**File:** `07_sorting.cpp`

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Insertion | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Bubble | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | No |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) | No |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | No |

### Key Algorithms:
- **Insertion Sort:** Adaptive, O(n) when sorted
- **Bubble Sort:** Flagged optimization
- **Heap Sort:** In-place, guaranteed O(n log n)
- **Merge Sort:** Stable, O(n) extra space
- **Quick Sort:** Fastest average, partition-based

---

## Advanced Data Structures

### Suffix Array
**File:** `14_suffix_array.cpp`

**Structure:** Sorted indices of all suffixes

**Doubling Algorithm:** O(T log T)
1. Sort by 1st character
2. Sort by 2nd, 4th, 8th, ... characters
3. Compare (rank[i], rank[i+k]) pairs

**Applications:**
- Pattern matching: O(|P| × log|T|)
- Any substring is prefix of some suffix

---

### External Sorting
**File:** `19_external_sorting.cpp`

**Use Case:** Data too large for memory

**Phase 1: Create Initial Runs**
- Read memory-sized chunks
- Sort in memory
- Write to disk

**Phase 2: K-way Merge**
- Merge k runs simultaneously using min-heap

**Replacement Selection:**
- Use min-heap to produce runs
- Average run size = 2M (twice memory size)

---

## Amortized Analysis

**Three Methods:**
1. **Aggregate Method:** Total cost of n operations / n
2. **Accounting Method:** Assign different charges to operations
3. **Potential Method:** Amortized cost = actual cost + ΔΦ

**Key Results:**
- Dynamic array push: O(1) amortized
- Splay tree: O(log n) amortized
- Fibonacci heap: O(1) amortized for insert, decreaseKey, merge
