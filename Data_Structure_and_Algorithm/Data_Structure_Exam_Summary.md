# Data Structure & Algorithm - Final Exam Knowledge Summary

---

## 1. Program Complexities (复杂度分析)

### Asymptotic Notation (渐近符号)

| Symbol | Meaning | Description |
|--------|---------|-------------|
| O(g(n)) | Big-Oh | Upper bound: 0 ≤ f(n) ≤ cg(n) for all n ≥ n0 |
| Ω(g(n)) | Big-Omega | Lower bound: 0 ≤ cg(n) ≤ f(n) for all n ≥ n0 |
| Θ(g(n)) | Theta | Tight bound: c1·g(n) ≤ f(n) ≤ c2·g(n) for all n ≥ n0 |
| o(g(n)) | Little-oh | Strict upper bound: f(n) < cg(n) for every c > 0 |

### Growth Rate Order (from slowest to fastest)
```
log n < √n < n < n·log n < n² < n⁴ < 2ⁿ < n!
```

### Rules for Big-Oh Analysis
1. **For loops**: running time = body × iterations
2. **Nested loops**: body × product of all loop sizes
3. **Consecutive statements**: take the maximum
4. **If/else**: test + max(S1, S2)

### Recursive Recurrence Examples
- T(n) = T(n-1) + A → O(n)
- T(n) = T(n-1) + n → O(n²)
- T(n) = 2T(n/2) + n → O(n·log n)
- Tower of Hanoi: T(n) = 2T(n-1) + 1 → O(2ⁿ)

---

## 2. Abstract Data Type (ADT)

- **Definition**: A package of data type declarations and meaningful operations, implementation-independent
- **Components**:
  - Value definition (with optional condition)
  - Operations definition (header + precondition + postcondition)
- **Key idea**: Separate *what* to do from *how* to do it (modular design)

---

## 3. Linked List (链表)

### Types
- **Singly Linked List**: Each node has data + next pointer
- **Circular List**: Last node's next points back to head
- **Doubly Linked List**: Each node has prev + next pointers

### Key Operations
| Operation | Time Complexity |
|-----------|----------------|
| Insert (sorted) | O(n) |
| Remove | O(n) |
| Search | O(n) |
| Count | O(n) |

### Insert Cases (Sorted)
1. Insert before first node (head changes)
2. Insert in middle
3. Insert at end

### Remove Cases
1. Remove first node
2. Remove non-first node (need predecessor)

### Dummy Header Node
- Simplifies insert/remove by eliminating special cases for the first node

### Advantages/Disadvantages
- **Advantages**: No pre-allocation needed, efficient memory use, easy insertion/deletion
- **Disadvantages**: Extra memory for pointers, sequential access only (no random access)

---

## 4. Stack (栈)

### ADT Definition
- **LIFO** (Last-In-First-Out)
- All operations at one end (top)

### Operations
| Operation | Description | Time |
|-----------|-------------|------|
| Push(e) | Add element to top | O(1) |
| Pop() | Remove and return top | O(1) |
| Top() | Return top without removing | O(1) |
| IsEmpty() | Check if empty | O(1) |
| IsFull() | Check if full (array only) | O(1) |

### Implementations

#### Array Implementation
- Use `top` index (-1 when empty)
- Dynamic array: double capacity when full, halve when ≤ 1/4 full
- **Amortized push**: O(1) with doubling strategy

#### Linked List Implementation
- `Top` pointer to first node
- Push = insert at head; Pop = remove from head

### Applications
1. **Backtracking** (maze generation)
2. **Balancing Symbols** (check matching brackets)
3. **Postfix Expression Evaluation**: scan left→right, push operands, pop 2 for operators
4. **Infix to Postfix Conversion**: use operator precedence
5. **Recursive function calls** (call stack)

---

## 5. Queue (队列)

### ADT Definition
- **FIFO** (First-In-First-Out)
- Insert at rear, delete from front

### Operations
| Operation | Description | Time |
|-----------|-------------|------|
| Enqueue(e) | Add to rear | O(1) |
| Dequeue() | Remove from front | O(1) |
| Front() | View front element | O(1) |
| IsEmpty() | Check if empty | O(1) |

### Implementations

#### Linked List
- `front` and `back` pointers
- Enqueue at back, Dequeue from front

#### Array (Circular)
- Use circular array to avoid wasting space
- `iback` = index of most recent entry, `ifront` = index of front
- **full**: `(rear+1) % capacity == front`
- **empty**: `front == rear`

### Deque (Double-Ended Queue)
- Supports insert/delete at both ends
- Operations: `push_front`, `push_back`, `pop_front`, `pop_back`

### Priority Queue
- Elements removed by **priority**, not insertion order
- Implementations: ordered list, unordered list, multiple queues, AVL tree, **Heap**

---

## 6. Trees (树) — DETAILED

### 6.1 Definition and Terminology

A **tree** is a finite set T of one or more nodes such that:
1. There is one specially designated node called the **root**
2. The remaining nodes are partitioned into m ≥ 0 disjoint sets T1, T2, ..., Tm
3. Each of these sets is itself a tree (subtrees)

### 6.2 Key Terminology (must know definitions!)

| Term | Definition |
|------|-----------|
| **Degree of a node** | Number of subtrees of that node |
| **Leaf / Terminal node** | A node with degree 0 (no children) |
| **Internal / Branch node** | A non-terminal node (has children) |
| **Parent** | The node above (root of its subtrees) |
| **Child** | A node below (root of a subtree) |
| **Siblings** | Nodes sharing the same parent |
| **Path** | Sequence n1, n2, ..., nk where ni is parent of ni+1 |
| **Path length** | Number of edges on the path |
| **Ancestor** | Any node on the path from root to a given node (including itself) |
| **Descendant** | Any node reachable by going down from a given node |
| **Level/Depth of node** | Length of unique path from root to this node (root has depth 0) |
| **Height of tree** | Maximum depth of any leaf (empty tree height = -1) |

### 6.3 Binary Tree

A **binary tree** is a finite set of nodes that either:
- Is empty, OR
- Consists of a root and two disjoint binary trees called **left subtree** and **right subtree**

**Key difference from general tree**: Left and right children are distinguished (order matters).

#### Special Types
- **Full node**: Both left and right subtrees are non-empty
- **Full binary tree**: Every node is either a full node or a leaf node
- **Perfect binary tree**: All levels completely filled → nodes = 2^(h+1) - 1
- **Complete binary tree**: All levels fully filled except possibly last, which is filled from left to right

#### Properties of Binary Tree
| Property | Formula |
|----------|---------|
| Max nodes at level i | 2ⁱ |
| Max total nodes (height h) | 2^(h+1) - 1 |
| Min nodes (height h) | h + 1 (skewed tree) |
| Number of leaves in perfect tree | 2^h |
| Height of tree with n nodes (perfect) | ⌊log₂(n)⌋ |

### 6.4 Array Representation of Binary Tree

Two indexing schemes:

**0-indexed (starting at 0):**
```
Left child of i:   2i + 1
Right child of i:  2i + 2
Parent of i:       ⌊(i-1)/2⌋
```

**1-indexed (first entry blank, starting at 1) — simpler for heaps:**
```
Left child of k:   2k
Right child of k:  2k + 1
Parent of k:       ⌊k/2⌋  (or k >> 1 in C++)
```

**C++ bitwise operations (1-indexed):**
```cpp
parent = k >> 1;
left_child = k << 1;
right_child = left_child | 1;
```

**Advantages of array representation**: Simpler, saves storage for nearly full trees
**Disadvantages**: Wastes space for sparse trees, fixed max size, costly insert/delete in middle
**Best practice**: Only use array for **complete binary trees**

### 6.5 Linked Representation of Binary Tree

```cpp
class TreeNode {
    int info;
    TreeNode* left;
    TreeNode* right;
    // optional: TreeNode* parent;
};

class MyTree {
    TreeNode* root;  // NULL if empty
};
```

- If always traversing downward, parent pointer is unnecessary
- From root, you can reach all nodes via left/right pointers

### 6.6 Binary Tree Operations (Code)

**Height of a binary tree:**
```cpp
int TreeNode::height() {
    if (this == NULL) return -1;
    if (left == NULL && right == NULL) return 0;
    int hL = left->height();
    int hR = right->height();
    return (hL > hR ? hL : hR) + 1;
}
```

**Count leaf nodes:**
```cpp
int count_leaf(TreeNode* p) {
    if (p == NULL) return 0;
    if (p->left == NULL && p->right == NULL) return 1;
    return count_leaf(p->left) + count_leaf(p->right);
}
```

**Check equality of two trees:**
```cpp
bool TreeNode::equal(TreeNode* TN) {
    if (this == NULL && TN == NULL) return true;
    if (this == NULL || TN == NULL) return false;
    if (info != TN->info) return false;
    return left->equal(TN->left) && right->equal(TN->right);
}
```

### 6.7 Tree Traversals — CRITICAL FOR EXAM

#### Depth-First Traversals (Recursive / Stack)

| Traversal | Order | Use Case |
|-----------|-------|----------|
| **Preorder** | Root → Left → Right | Copy/tree construction, prefix expressions |
| **Inorder** | Left → Root → Right | **BST gives sorted order**, infix expressions |
| **Postorder** | Left → Right → Root | Delete tree, postfix expressions, evaluate expressions |

#### Breadth-First Traversal (Queue)

| Traversal | Order | Use Case |
|-----------|-------|----------|
| **Level-order** | Visit level by level | Level-by-level processing |

#### Traversal Implementation (Recursive)
```cpp
void PreorderHelper(TreeNode* node) {
    if (node != NULL) {
        cout << node->info;        // Visit root
        PreorderHelper(node->left);  // Traverse left
        PreorderHelper(node->right); // Traverse right
    }
}

void InorderHelper(TreeNode* node) {
    if (node != NULL) {
        InorderHelper(node->left);
        cout << node->info;
        InorderHelper(node->right);
    }
}

void PostorderHelper(TreeNode* node) {
    if (node != NULL) {
        PostorderHelper(node->left);
        PostorderHelper(node->right);
        cout << node->info;
    }
}
```

#### Non-recursive Inorder Traversal (using Stack)
1. Start with empty stack, pointer p = root
2. At each node, push address onto stack, go left
3. When hitting NULL, pop from stack, visit node, go right
4. Repeat until stack empty and no right child

#### Level-order Traversal (using Queue)
1. Push root into queue
2. While queue not empty:
   - Dequeue front node, visit it
   - Enqueue its left child (if exists)
   - Enqueue its right child (if exists)

### 6.8 Reconstructing Binary Tree — EXAM FAVORITE

**Given preorder + inorder → uniquely determines tree**

**Algorithm:**
1. First element of **preorder** is always the **root**
2. Find root in **inorder** → everything left of root is left subtree, everything right is right subtree
3. Count how many elements in left subtree
4. Recursively construct left and right subtrees

**Example:**
- Preorder: A B C D E X Z U T Y
- Inorder: D C E B A U Z T X Y
- Root = A (first in preorder)
- In inorder: D C E B | A | U Z T X Y → left subtree has 4 elements
- Left subtree: preorder = B C D E, inorder = D C E B
  - Root = B, left of B in inorder: D C E → left subtree of B
  - Continue recursively...

**Important**: Preorder + Postorder does NOT uniquely determine a tree!

### 6.9 Applications of Tree Traversals

1. **Expression tree**: Inorder → infix notation; Preorder → prefix; Postorder → postfix
2. **Evaluate expression tree**: Postorder traversal
3. **Find duplicates in list**: Build BST, check during construction → O(n·log n) average

---

## 7. Binary Search Tree (BST)

### Definition
A BST is a binary tree where for every node:
- All values in **left subtree** < node value
- All values in **right subtree** > node value
- Both subtrees are also BSTs

**No duplicate values** (by convention)

### BST vs Degenerate Tree
- Balanced BST: height O(log n) → fast operations
- Degenerate BST (like linked list): height O(n) → slow operations
- Inserting sorted data into empty BST → worst case O(n) height!

### Operations — All O(h) where h = tree height

| Operation | Average (balanced) | Worst (degenerate) |
|-----------|-------------------|-------------------|
| Find/Insert/Delete | O(log n) | O(n) |

### Find Operation
```cpp
bool find(Type const& obj) const {
    if (empty()) return false;
    if (value() == obj) return true;
    return (obj < value()) ? left()->find(obj) : right()->find(obj);
}
```

### Insert Operation
- Traverse tree like find
- If found → return false (no duplicates)
- If empty node reached → insert new leaf there
```cpp
bool insert(Type const& obj, Binary_search_node*& ptr_to_this) {
    if (empty()) {
        ptr_to_this = new Binary_search_node(obj);
        return true;
    } else if (obj < value()) {
        return left()->insert(obj, left_tree);
    } else if (obj > value()) {
        return right()->insert(obj, right_tree);
    } else {
        return false; // duplicate
    }
}
```

### Delete — THREE CASES (must know!)

**Case 1: Leaf node** → Simply remove (set parent's pointer to NULL)

**Case 2: One child** → Replace node with its only child (promote child)

**Case 3: Two children (full node):**
1. Find the **minimum in the right subtree** (inorder successor)
2. Replace current node's value with that minimum value
3. Recursively delete that minimum node from the right subtree
4. (Alternatively, use maximum of left subtree)

**Why minimum of right subtree?** It's the smallest value greater than current node, maintaining BST property.

### BST Application: Sort Array
- Method 1: Insert all into BST, then repeatedly find+remove min → O(n²)
- Method 2: Insert all into BST, then inorder traversal → O(n²) construction + O(n) traversal
- **Inorder traversal of BST always gives sorted order**

---

## 8. Heap (堆) — DETAILED

### 8.1 Definition

**Binary Min-Heap**: A complete binary tree where:
- The key at the root is ≤ keys of both subtrees
- Both subtrees are also binary min-heaps

**Binary Max-Heap**: A complete binary tree where:
- The root key ≥ both children's keys
- Both subtrees are also binary max-heaps

**Critical insight**: No relationship between elements in left and right subtrees! Only parent-child ordering matters.

### 8.2 Complete Binary Tree Property
- Heaps are always **complete binary trees**
- This guarantees height = O(log n)
- Enables efficient **array representation** (no gaps except possibly last level)

### 8.3 Array Implementation (1-indexed)

```
Index:  0  1  2  3  4  5  6  7  8  9  10  11 ...
Heap:  [_ 3  5  7  9  8  12 15 11 20 18 25 ...]
                  ↑root
```

**Navigation formulas:**
| Operation | Formula | C++ |
|-----------|---------|-----|
| Parent of k | ⌊k/2⌋ | `k >> 1` |
| Left child of k | 2k | `k << 1` |
| Right child of k | 2k+1 | `(k << 1) | 1` |

**Important**: Index 0 is unused (or stores size); heap starts at index 1.

### 8.4 Three Core Operations

#### Top (Find Minimum/Maximum) — O(1)
- Just return array[1] (the root)

#### Push (Insert) — O(log n)
**Algorithm (Percolate Up / Bubble Up):**
1. Place new element at the end of array (next leaf position in complete tree)
2. Compare with parent: if smaller than parent, swap
3. Repeat until heap property restored or reach root

```
Push 8 into min-heap:
Array: [_, 3, 5, 12, 9, 8, 15]
Step 1: Place 8 at position 7
Step 2: parent(7) = 3, array[3] = 12 > 8 → swap
Step 3: parent(3) = 1, array[1] = 3 < 8 → stop
Result: [_, 3, 5, 8, 9, 12, 15] ✓
```

**Code:**
```cpp
void push(Type x) {
    array[++count] = x;  // place at end
    int posn = count;
    while (posn > 1 && array[posn/2] > array[posn]) {
        swap(array[posn], array[posn/2]);  // percolate up
        posn /= 2;
    }
}
```

#### Pop (Remove Minimum/Maximum) — O(log n)
**Algorithm (Percolate Down / Bubble Down):**
1. Save array[1] (the minimum to return)
2. Move last element array[count] to root (array[1])
3. Decrease count
4. Compare root with children: if larger than either child, swap with the **smaller** child
5. Repeat until heap property restored or no children smaller

```
Pop from min-heap [_, 3, 5, 8, 9, 12, 15]:
Step 1: Save 3, move 15 to root → [_, 15, 5, 8, 9, 12]
Step 2: 15 > 5 and 15 > 8, swap with min child (5) → [_, 5, 15, 8, 9, 12]
Step 3: 15 > 9 and 15 > 12, swap with min child (9) → [_, 5, 9, 8, 15, 12]
Step 4: 15 > 12, swap → [_, 5, 9, 8, 12, 15]
Step 5: 15 has no children → done
```

**Code:**
```cpp
Type pop() {
    Type min = array[1];
    array[1] = array[count--];  // move last to root
    int posn = 1;
    while (2*posn <= count) {  // has at least one child
        int child = 2*posn;    // left child
        if (child + 1 <= count && array[child+1] < array[child])
            child++;           // right child is smaller
        if (array[posn] > array[child]) {
            swap(array[posn], array[child]);
            posn = child;
        } else break;
    }
    return min;
}
```

### 8.5 Heap Property Maintenance — Key Points

- **Push**: only percolates **UP** (lighter elements rise)
- **Pop**: only percolates **DOWN** (heavier elements sink)
- Both operations are O(log n) because tree height = O(log n)
- **Neither operation requires searching the whole array!**

### 8.6 Heap Sort — O(n·log n) In-Place

**Two-phase algorithm:**
1. **Build max-heap** from unsorted array (bottom-up): O(n)
   - Start from last non-leaf node (index n/2), percolate down each
   - Why O(n) and not O(n·log n)? Because most nodes are near the bottom and need few swaps
2. **Extract max n times**: swap root with last unsorted, reduce heap, percolate down → O(n·log n)

```cpp
void HeapSort(Type* a, int array_size) {
    BuildMaxHeap(a, array_size);           // Phase 1: O(n)
    for (int i = array_size; i > 1; i--) {
        swap(a[1], a[i]);                 // Move max to end
        Heapify(a, i-1, 1);              // Restore heap: O(log n)
    }
}

void BuildMaxHeap(Type* a, int n) {
    for (int i = n/2; i >= 1; i--)       // Start from last non-leaf
        Heapify(a, n, i);
}

void Heapify(Type* a, int n, int i) {
    int largest = i;
    int left = 2*i, right = 2*i+1;
    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;
    if (largest != i) {
        swap(a[i], a[largest]);
        Heapify(a, n, largest);
    }
}
```

### 8.7 Build Max-Heap — Why O(n)?

At depth k, there are 2^k nodes, each may need to percolate down at most (h-k) levels:
```
Total swaps = Σ(k=0 to h) 2^k · (h-k)
            = Σ(j=0 to h) 2^(h-j) · j
            = 2^h · Σ(j=0 to h) j/2^j
            = O(n)  (geometric series converges)
```

### 8.8 Heap Complexity Summary

| Operation | Binary Min/Max-Heap | Leftist Heap | Fibonacci Heap |
|-----------|-------------------|--------------|----------------|
| Top | O(1) | O(1) | O(1) |
| Push | O(log n) worst, **O(1) avg** | O(log n) | **O(1) amortized** |
| Pop | O(log n) | O(log n) | O(log n) amortized |
| Merge | O(n) | **O(log n)** | **O(1) amortized** |
| Delete arbitrary | O(n) | O(n) | O(log n) amortized |

### 8.9 Leftist Heap — DETAILED

**Why Leftist Heap?** Binary min-heap merge is O(n). Leftist heap enables O(log n) merge.

**Definition**: A node-based binary tree satisfying:
1. **Min-heap property**: root ≤ both children (recursive)
2. **Leftist property**: npl(left) ≥ npl(right) for every node

**Null-Path Length (npl)**:
- npl(node) = shortest distance from node to a non-full node (node with < 2 children)
- npl(leaf) = 0; npl(NULL) = -1
- npl(node) = 1 + min(npl(left), npl(right))

**EXAM TIP**: The leftist property ensures that the rightmost path is the shortest path to a non-full node. This is where all operations happen.

**Leftist property consequence**: The rightmost path is the shortest path to a non-full node. This is where all operations happen → efficient.

**EXAM TIP**: Remember "Leftist = Left-heavy" - the left subtree is always at least as "deep" as the right subtree in terms of null paths.

#### Merge Algorithm — O(log n)
```
merge(a, b):
    if a == NULL return b
    if b == NULL return a
    if a->data > b->data: swap(a, b)  // ensure a has smaller root
    
    a->right = merge(a->right, b)      // merge b into a's right subtree
    
    // Fix leftist property
    if a->left == NULL OR (a->right != NULL AND a->left->npl < a->right->npl):
        swap(a->left, a->right)
    
    a->npl = (a->right == NULL) ? 0 : a->right->npl + 1
    return a
```

**Three cases for merging a's right subtree with b:**
1. a->right is empty → attach b as a->right
2. a->right ≤ b → continue merging with a->right->right
3. b < a->right → b becomes a->right, merge detached subtree with b's right

**EXAM TIP**: The merge operation always works on the rightmost path. This is why leftist heaps are efficient for merging.

#### Push — O(log n)
- Create trivial single-node heap, merge with current heap

#### Pop — O(log n)
- Remove root, merge left and right subtrees

#### Key Insight
- All operations work along the **rightmost path** only
- Leftist property ensures rightmost path length = O(log n)
- No array needed — purely node-based (like linked list)

#### Quick Reference: Leftist Heap Properties
| Property | Value |
|----------|-------|
| Leftist property | npl(left) ≥ npl(right) |
| Null-path length | Shortest distance to non-full node |
| Rightmost path length | O(log n) |
| Merge time | O(log n) |
| Push time | O(log n) |
| Pop time | O(log n) |
| Space per node | data, npl, left, right pointers |

### 8.10 Priority Queue with Heap

- Use **max-heap** for highest-priority-first
- For **stable** priority queue (FIFO within same priority):
  - Use **lexicographic ordering**: priority (n, k) where k is insertion order
  - (n1, k1) < (n2, k2) iff n1 < n2 OR (n1 = n2 AND k1 < k2)

---

## 9. Hashing (哈希)

### Hash Function
- Maps key → slot index
- **Division method**: `h(key) = key % table_size` (table_size should be prime)

### Collision Resolution

#### Open Addressing
| Method | Probe Sequence |
|--------|---------------|
| Linear Probing | h+1, h+2, h+3, ... |
| Quadratic Probing | h+1², h+2², h+3², ... |
| Double Hashing | h+h2(x), h+2·h2(x), ... |

- **Quadratic probing** with prime table size: can always insert if table is ≥ half empty
- **Double hashing** with prime table size: can always insert if table is not full

#### Separate Chaining
- Each slot is a linked list
- Insert/search in corresponding list

### Rehashing
- When load factor > threshold (e.g., half full), create new table (double size), reinsert all elements
- Total cost over n insertions: O(n) → amortized O(1) per insertion

### Perfect Hashing
- Two-level hashing for O(1) worst-case search
- Primary table of size N², secondary tables for collisions

---

## 10. Disjoint Set (并查集) — DETAILED

### ADT Definition
- **Value**: A set of items, each associated with an equivalence class name
- **Find(a)**: return the equivalence class name for element a
  - If Find(a) == Find(b), then a and b are in the same equivalence class
- **Union(a, b)**: merge a's equivalence class with b's equivalence class
  - Postcondition: a, b, and all their class members share the same class name

### Equivalence Relation Properties
- **Reflexive**: aRa is true for all a
- **Symmetric**: aRb → bRa
- **Transitive**: aRb and bRc → aRc

### Array Implementation
- `s[i]` = class name of element i
- **Find(i)**: return `s[i]` → O(1)
- **Union(i, j)**: change all `s[k]` where `s[k] == s[j]` to `s[i]` → O(n)

```cpp
int find(int i) { return name[i]; }
void unionSets(int i, int j) {
    int nameI = find(i), nameJ = find(j);
    if (nameI == nameJ) return;
    for (int k = 0; k < n; k++)
        if (name[k] == nameJ) name[k] = nameI;
}
```

### Tree Implementation
- Each element points to a parent; roots represent equivalence classes
- **Find**: follow parent links to root → O(h)
- **Union**: attach root of one tree to root of another

```
Before Union(1,5):    After Union(1,5):
  1                     1
 / \                   /|\
2   3                 2 3 5
    |
    4
```

### Optimizations

#### Union by Height (or Union by Size)
- **Rule**: Attach shorter tree under taller tree
- If equal height: attach either way, height increases by 1
- **Guarantee**: depth of any node ≤ O(log n)

```cpp
void unionByHeight(int i, int j) {
    int rootI = find(i), rootJ = find(j);
    if (rootI == rootJ) return;
    if (height[rootI] < height[rootJ]) {
        parent[rootJ] += parent[rootI];  // merge i into j
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
```

#### Path Compression
- During **Find(i)**, make every node on the path point directly to the root
- "Flattens" the tree structure dramatically

```cpp
int find(int i) {
    if (parent[i] < 0) return i;  // i is root
    parent[i] = find(parent[i]);   // path compression
    return parent[i];
}
```

#### Combined Complexity
- Union by Height + Path Compression → amortized **O(α(n))** per operation
- α(n) = inverse Ackermann function, grows incredibly slowly (α(2^65536) ≤ 5)
- **Practically O(1)** for any realistic input

### Theorem: Union-by-Height Guarantees O(log n)
- **Lemma**: For any root x, size(x) ≥ 2^height(x)
- **Proof**: By induction. Base: height 0, size ≥ 1 = 2^0 ✓
  - When merging two trees of equal height h, new height = h+1, new size ≥ 2·2^h = 2^(h+1) ✓
- Therefore: height ≤ log₂(n) → O(log n)

### Application: Maze Generation
1. Start with n cells, each in its own set
2. While entrance and exit not connected:
   - Pick a random wall between adjacent cells i and j
   - If Find(i) ≠ Find(j): Union(i, j) — break the wall
3. Result: a maze with exactly one path between any two cells

---

## 11. Balanced Trees — DETAILED

### 11.1 Why Balanced Trees?

BST operations are O(h). If tree is balanced, h = O(log n). If degenerate, h = O(n).
**Goal**: maintain h = O(log n) through rotations after insert/delete.

**Similarity to heap**: both maintain structure property
**Difference**: Heap maintains value ordering (parent ≤ children); BST maintains sorted ordering (left < root < right)

### 11.2 AVL Tree

**Definition**: For every node v, |height(left) - height(right)| ≤ 1
**Height guarantee**: h ≤ 1.44 · log₂(n) (proof via Fibonacci-like recurrence)

#### Why O(log n) height?
- F(h) = fewest nodes in AVL tree of height h
- F(0) = 1, F(1) = 2
- F(h) = F(h-1) + 1 + F(h-2)  (worst case: one subtree h-1, other h-2)
- This is Fibonacci-like → F(h) ≈ φ^h where φ = 1.618
- Therefore h ≤ log_φ(n) ≈ 1.44 · log₂(n)

**EXAM TIP**: Memorize that AVL trees have height ≤ 1.44·log₂(n). This is tighter than Red-Black trees (2·log₂(n+1)).

#### Insertion — 4 Cases

After inserting a node, walk up from insertion point to root, checking balance:

| Case | Unbalanced Node v | Inserted in | Fix |
|------|------------------|-------------|-----|
| **LL** | Left child's left subtree | Left-Left | **Single right rotation** on v |
| **RR** | Right child's right subtree | Right-Right | **Single left rotation** on v |
| **LR** | Left child's right subtree | Left-Right | **Double rotation**: left rotate left child, then right rotate v |
| **RL** | Right child's left subtree | Right-Left | **Double rotation**: right rotate right child, then left rotate v |

**EXAM TIP**: Remember the acronym "LL-RR-LR-RL" - it's like a mirror: LL/RR are single rotations, LR/RL are double rotations.

#### Rotation Code

```cpp
// Single Right Rotation (LL case)
void rotateL(Node*& s) {  // s is the unbalanced node
    Node* t = s->lson;     // t = left child (will become new root)
    s->lson = t->rson;     // t's right subtree becomes s's left
    t->rson = s;           // s becomes t's right child
    s->height = max(h(s->lson), h(s->rson)) + 1;
    t->height = max(h(t->lson), s->height) + 1;
    s = t;                 // t is now the root of this subtree
}

// Single Left Rotation (RR case)
void rotateR(Node*& s) {
    Node* t = s->rson;
    s->rson = t->lson;
    t->lson = s;
    s->height = max(h(s->lson), h(s->rson)) + 1;
    t->height = max(h(t->rson), s->height) + 1;
    s = t;
}

// Double Rotation (LR case): left rotate left child, then right rotate
void dbl_rotateL(Node*& s) {
    rotateR(s->lson);  // First, fix the left child
    rotateL(s);         // Then, fix the current node
}

// Double Rotation (RL case): right rotate right child, then left rotate
void dbl_rotateR(Node*& s) {
    rotateL(s->rson);
    rotateR(s);
}
```

**EXAM TIP**: Draw the rotation diagrams! For LL case: 
```
    v          x
   / \   =>   / \
  x   C       A   v
 / \              / \
A   B            B   C
```

#### AVL Insertion — Complete Algorithm
```cpp
void AVL::insert(Node*& t, item x) {
    if (t == NULL) { t = new Node(x); return; }
    else if (x < t->data) {
        insert(t->lson, x);
        if (h(t->lson) == h(t->rson) + 2) {
            if (x < t->lson->data) rotateL(t);    // LL case
            else dbl_rotateL(t);                    // LR case
        }
    } else if (x > t->data) {
        insert(t->rson, x);
        if (h(t->rson) == h(t->lson) + 2) {
            if (x > t->rson->data) rotateR(t);    // RR case
            else dbl_rotateR(t);                    // RL case
        }
    }
    // else: duplicate, do nothing
    t->height = max(h(t->lson), h(t->rson)) + 1;
}
```

#### AVL Deletion
- More complex than insertion
- May cause **O(log n) imbalances** (cascading up to root)
- After deleting, check balance at each ancestor and rotate if needed
- Same 4 cases as insertion

**EXAM TIP**: For deletion, after removing a node, you may need to perform rotations all the way up to the root. The key difference from insertion is that insertion only requires at most one rotation (or two for double rotation), but deletion may require O(log n) rotations.

#### AVL vs Complete Binary Tree
- Q: Does an AVL tree have to be complete? **No** (AVL only requires |hL - hR| ≤ 1)
- Q: Does a complete tree have to be AVL? **Yes** (complete trees are perfectly balanced)

#### Quick Reference: AVL Tree Properties
| Property | Value |
|----------|-------|
| Balance factor | \|hL - hR\| ≤ 1 for every node |
| Height bound | h ≤ 1.44·log₂(n) |
| Minimum nodes for height h | F(h) ≈ φ^h, φ = 1.618 |
| Insertion rotations | At most 1 (single or double) |
| Deletion rotations | Up to O(log n) |
| Search time | O(log n) |
| Insert time | O(log n) |
| Delete time | O(log n) |
| Extra storage per node | height (integer) |

### 11.3 Splay Tree

**Idea**: Self-adjusting BST — every access (find/insert/delete) **splays** the accessed node to the root.

**Key insight**: Recently accessed nodes are likely to be accessed again → move them to root.

**Amortized O(log n)** for all operations (but worst-case single operation can be O(n)).

**No extra storage** needed (no height/color fields) — simpler than AVL.

#### Splay Operations

**Zig**: Node's parent is root → single rotation
```
    p              n
   / \    →      / \
  n   C         A   p
 / \               / \
A   B             B   C
```

**Zig-Zig** (same direction: both left or both right):
- Rotate grandparent, then parent (two single rotations, same direction)
```
      g           n
     / \         / \
    p   D  →    A   p
   / \             / \
  n   C           B   g
 / \                 / \
A   B               C   D
```

**Zig-Zag** (opposite directions):
- Double rotation at grandparent (like AVL LR/RL)
```
      g             n
     / \           / \
    A   p    →    g   p
       / \       / \ / \
      B   n     A  B C  D
         / \
        C   D
```

#### Splay Tree Operations

**Find**: Normal BST find, then splay found node to root
**Insert**: BST insert, then splay new node to root
**Delete**: Find node (splay to root), then find max of left subtree (splay to root of left subtree), attach right subtree as right child of new root

#### Why Splaying Helps
- Accessing a deep node brings it to root via splay
- Nodes on the access path move closer to root (approximately half the depth)
- Frequent accesses stay near top; infrequent stays near bottom
- **Self-tuning** behavior

### 11.4 Red-Black Tree

**Definition**: A BST where each node is colored **red** or **black**, satisfying:

1. **Root is black**
2. **Red node's children must be black** (no two red nodes in a row)
3. **Every null path has the same number of black nodes** (black-height property)

**EXAM TIP**: Remember the acronym "RB3" - Root is black, no two Reds in a row, Black-height equal.

#### Consequences
- Every red node is either a **full node** (two black children) or a **leaf**
- If a node has exactly one child, that child must be a **red leaf**, and the parent must be **black**
- Height: h ≤ 2·log₂(n+1) (roughly twice as tall as AVL in worst case)

#### Null Path Definition
A null path is any path from root to a non-full node (where you'd follow a NULL pointer). All null paths must have the same number of black nodes.

**EXAM TIP**: The black-height property is what makes Red-Black trees balanced. It ensures that the longest path from root to leaf is no more than twice the shortest path.

#### Insertion — Bottom-Up
1. Insert new node as **red** (to not violate black-height)
2. If parent is black → done (no violation)
3. If parent is red → red-red violation! Fix:
   - **Case A**: Uncle is black → **rotation** (like AVL LL/RR/LR/RL)
   - **Case B**: Uncle is red → **recolor** (parent, uncle, grandparent swap colors), then recurse to grandparent
4. At root: if root becomes red, color it black

**EXAM TIP**: For insertion, remember "UR" - Uncle Red = recolor, Uncle Black = rotation.

#### Insertion Cases (Bottom-Up) — DETAILED

| Case | Parent | Uncle | Grandparent | Action |
|------|--------|--------|-------------|--------|
| 1 | RED | RED | any | Recolor parent, uncle, grandparent |
| 2a | RED | BLACK | left-heavy | Right rotation on grandparent |
| 2b | RED | BLACK | right-heavy | Left rotation on grandparent |
| 3a | RED | BLACK | left-heavy, z is right child | Left rotate parent, then right rotate grandparent |
| 3b | RED | BLACK | right-heavy, z is left child | Right rotate parent, then left rotate grandparent |

**EXAM TIP**: Cases 2 and 3 are analogous to AVL LL/RR and LR/RL rotations.

#### Insertion — Top-Down
- While descending from root, preemptively **recolor** any black node with two red children
- This ensures at most one rotation needed at the end
- No recursion back to root needed

**EXAM TIP**: Top-down insertion is simpler to implement but less efficient in practice. Bottom-up is more commonly taught.

#### Deletion
- More complex than insertion
- May require up to O(log n) rotations
- Key concept: "double black" nodes - when a black node is removed and replaced by a black child
- Fix double black by cases involving siblings, nephews, and nieces

**EXAM TIP**: For deletion, remember "DB" - Double Black nodes need fixing.

#### Quick Reference: Red-Black Tree Properties
| Property | Value |
|----------|-------|
| Root color | BLACK |
| Red node children | Must be BLACK |
| Black-height | Same for all null paths |
| Height bound | h ≤ 2·log₂(n+1) |
| Insert rotations | At most 2 |
| Delete rotations | Up to O(log n) |
| Extra storage per node | color (1 bit) |

#### Comparison with AVL
| Feature | AVL | Red-Black |
|---------|-----|-----------|
| Height bound | 1.44·log₂(n) | 2·log₂(n+1) |
| Search speed | Faster (shorter) | Slightly slower |
| Insert/Delete | More rotations | Fewer rotations |
| Storage | 1 byte (height) | 1 bit (color) |
| Implementation | More complex | Simpler |
| Use case | Read-heavy | Insert/delete-heavy |

**EXAM TIP**: AVL trees are better for lookup-intensive applications, while Red-Black trees are better for insert/delete-intensive applications like maps and sets in C++ STL.

---

## 12. Graphs — BFS & DFS

*(Note: Graphs are covered in the context of tree traversals and queue applications)*

### 12.1 Graph Terminology

| Term | Definition |
|------|-----------|
| **Vertex (node)** | A point in the graph |
| **Edge** | Connection between two vertices |
| **Directed graph** | Edges have direction (digraph) |
| **Undirected graph** | Edges have no direction |
| **Weighted graph** | Edges have associated weights |
| **Path** | Sequence of vertices connected by edges |
| **Cycle** | Path that starts and ends at same vertex |
| **Connected graph** | Path exists between every pair of vertices |

### 12.2 Breadth-First Search (BFS)

**Strategy**: Explore all neighbors at current depth before moving deeper.

**Algorithm (using Queue):**
```
BFS(start):
    enqueue(start)
    mark start as visited
    while queue not empty:
        v = dequeue()
        process(v)
        for each neighbor w of v:
            if w not visited:
                enqueue(w)
                mark w as visited
```

**Time Complexity**: O(V + E) where V = vertices, E = edges
**Space Complexity**: O(V) for queue and visited array

**Applications:**
- Level-order tree traversal
- Shortest path in unweighted graph
- Finding connected components
- BFS on directory tree (search shallow dirs first)

### 12.3 Depth-First Search (DFS)

**Strategy**: Explore as far as possible along each branch before backtracking.

**Algorithm (using Stack or Recursion):**
```
DFS(v):
    mark v as visited
    process(v)
    for each neighbor w of v:
        if w not visited:
            DFS(w)
```

**Time Complexity**: O(V + E)
**Space Complexity**: O(V) for recursion stack / explicit stack

**Applications:**
- Topological sorting
- Detecting cycles
- Finding connected components
- Maze solving (backtracking)
- Tree traversals (preorder/inorder/postorder are all DFS!)

### 12.4 BFS vs DFS

| Feature | BFS | DFS |
|---------|-----|-----|
| Data structure | Queue | Stack / Recursion |
| Order | Level by level | Branch by branch |
| Shortest path | Yes (unweighted) | No guarantee |
| Memory | O(width of tree) | O(height of tree) |
| Complete? | Yes (finds solution if exists) | May not find shortest |

---

## 13. Sorting (排序)

### Comparison of Sorting Algorithms

| Algorithm | Best | Average | Worst | Space | Stable |
|-----------|------|---------|-------|-------|--------|
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Heap Sort | O(n·log n) | O(n·log n) | O(n·log n) | O(1) | No |
| Merge Sort | O(n·log n) | O(n·log n) | O(n·log n) | O(n) | Yes |
| Quick Sort | O(n·log n) | O(n·log n) | O(n²) | O(log n) | No |
| Bucket Sort | O(n+M) | O(n+M) | O(n+M) | O(M) | Yes |
| Radix Sort | O(d·(n+M)) | O(d·(n+M)) | O(d·(n+M)) | O(n+M) | Yes |
| Shell Sort | varies | varies | O(n²) | O(1) | No |

### Inversions
- Pair (aⱼ, aₖ) where j < k but aⱼ > aₖ
- Each swap of adjacent elements changes inversion count by ±1
- **Insertion/Bubble sort comparisons ≈ n + d** (d = number of inversions)

### Insertion Sort
- Treat first k elements as sorted, insert k+1th into correct position
- Best case O(n) when already sorted; Worst case O(n²) when reverse sorted

### Bubble Sort (4 Improvements)
1. Basic: swap adjacent elements
2. Swap-elimination: track max, move elements instead of swapping
3. Flagged: stop early if no swaps occurred
4. Range-limiting: track last swap position
5. Alternating: bubble up then sink down

### Heap Sort (In-Place)
1. Build max-heap from array: O(n)
2. Swap root with last, reduce heap size, percolate down: O(log n) × n

### Merge Sort
- Divide array in half, recursively sort, merge: T(n) = 2T(n/2) + Θ(n)
- Always O(n·log n), but requires O(n) extra space

### Quicksort
- Choose pivot, partition into elements < pivot and > pivot, recurse
- **Best/Average**: O(n·log n); **Worst** (sorted input): O(n²)
- **Improvements**: median-of-three pivot, insertion sort for small subarrays

### Bucket Sort / Radix Sort
- **Bucket sort**: O(n+M) when keys in {0,...,M-1}; M = number of buckets
- **Radix sort**: stable sort by each digit (LSD→MSD), O(d·(n+M))

---

## 14. Advanced Data Structures

### B+ Tree
- Balanced multiway search tree for disk-based storage
- All data at **leaf blocks** (linked for sequential access)
- Internal nodes: M-way tree with 2 to M children
- Leaf blocks: contain ⌈L/2⌉ to L records
- Height: O(log n) → few disk accesses
- Insert: split leaf (and possibly internal nodes) when full
- Delete: merge/redistribute when blocks below half full

### Suffix Array — DETAILED

**Definition**: Given string T = t₁t₂...tₙ, the suffix at position i is S[i] = tᵢtᵢ₊₁...tₙ.
The **suffix array** SA is the sorted array of all suffix indices in lexicographic order.

**Example**: T = "mississippi"
```
Suffix S[0]  = "mississippi"
Suffix S[1]  = "ississippi"
Suffix S[2]  = "ssissippi"
Suffix S[3]  = "sissippi"
Suffix S[4]  = "issippi"
Suffix S[5]  = "ssippi"
Suffix S[6]  = "sippi"
Suffix S[7]  = "ippi"
Suffix S[8]  = "ppi"
Suffix S[9]  = "pi"
Suffix S[10] = "i"

Sorted: S[10]="i", S[7]="ippi", S[4]="issippi", S[1]="ississippi",
        S[0]="mississippi", S[9]="pi", S[8]="ppi", S[6]="sippi",
        S[3]="sissippi", S[5]="ssippi", S[2]="ssissippi"

SA = [10, 7, 4, 1, 0, 9, 8, 6, 3, 5, 2]
```

**Key Insight**: Any substring (pattern) of T is a prefix of some suffix.
- Pattern P = "ssip" → P = Prefix(Suffix(T, 2), 4)

**Pattern Matching** via binary search on suffix array: O(|P| · log|T|)

**Construction — Doubling Algorithm** O(T·log T):
1. Sort suffixes by 1st character (1-order)
2. Extend 1-order to 2-order: compare pairs (rank[i], rank[i+1])
3. Extend 2-order to 4-order: compare pairs (rank[i], rank[i+2])
4. Continue doubling until all ranks unique
5. Each phase: O(T) with radix sort → total O(T·log T)

```cpp
// L-order to 2L-order extension:
// S[i] <_L S[j]  → S[i] <_2L S[j]
// S[i] >_L S[j]  → S[i] >_2L S[j]
// S[i] =_L S[j]  → compare S[i+L] and S[j+L] using L-order
```

### Suffix Tree
- **Compact trie** of all suffixes (single-branch nodes collapsed)
- O(T) nodes, O(T) storage with edge label tricks
- Pattern matching: O(|P|) — just follow the path
- More complex to implement than suffix array

---

## 15. Geometric Data Structures

### k-d Tree — DETAILED

**Definition**: A binary tree for k-dimensional points where:
- At depth d, split on dimension `d mod k`
- Use the **median** point (along current dimension) as the split node
- Left subtree: points with smaller coordinate; Right: larger

**2D Example**: depth 0 splits on x, depth 1 splits on y, depth 2 on x, ...

#### Construction (Balanced) — O(n·log n)
1. Sort points by 1st coordinate, pick median → root
2. Recursively build left (smaller x) and right (larger x)
3. At next level, sort by 2nd coordinate, pick median
4. Alternate dimensions at each level

#### Properties
- **All points in left subtree** are in a restricted region
- Following a path from root restricts the region at each step
- This enables **pruning** during range search

#### Operations

**Range Search** — Find all points in rectangle [x₁,x₂] × [y₁,y₂]:
1. At each node, check if current point is in range
2. If split coordinate < range start → only search right subtree
3. If split coordinate > range end → only search left subtree
4. Otherwise → search both subtrees
5. **Pruning**: if entire subtree's region is inside the query rectangle, add all points

**Insert** — O(log n) average:
- Compare appropriate coordinate at each level (like BST)
- Go left if smaller, right if larger

**Nearest Neighbor** — O(log n) average:
- Search as if inserting, track best distance
- Prune subtrees whose region is farther than current best

#### Applications
- Image processing: locating objects in scenes
- Range queries in databases
- Finding points within a circular region (use bounding box first)
- k-d trees can't detect circular regions directly — find bounding box, then filter

### Quadtree
- **Region Quadtree**: recursive 4-way decomposition of binary images
  - Operations: Union, Intersection, Rotate — O(size of tree)
- **Point Quadtree**: stores points, insertion order determines structure
- **Point Region Quadtree**: equal subdivision until one point per cell
- **Octree**: 3D extension of quadtree (8 children per node)

### Interval Tree
- Stores intervals for overlap queries
- BST on median endpoint, each node stores overlapping intervals
- Query: O(log n + |output|)

---

## 16. Graph Algorithms (Dijkstra, MST, Topological Sort)

### 16.1 Dijkstra's Shortest Path
- **Greedy**: always process the closest unvisited vertex
- Uses min-heap priority queue
- **Time**: O((V+E)·log V)
- **Limitation**: No negative edge weights

**Algorithm:**
```
dist[src] = 0, all others = infinity
pq.push((0, src))
while pq not empty:
    (d, u) = pq.pop()  // closest unvisited
    if d > dist[u]: continue  // stale
    for each neighbor (v, w) of u:
        if dist[u] + w < dist[v]:
            dist[v] = dist[u] + w
            parent[v] = u
            pq.push((dist[v], v))
```

### 16.2 Minimum Spanning Tree (MST)
Connect all vertices with minimum total edge weight, no cycles.

#### Prim's Algorithm — O(E·log V)
- Start from arbitrary vertex, greedily add cheapest edge connecting tree to non-tree
- Like Dijkstra but using edge weight as key
- **Best for dense graphs**

#### Kruskal's Algorithm — O(E·log E)
- Sort all edges by weight
- Add cheapest edge that doesn't form a cycle (use Union-Find!)
- **Best for sparse graphs**

### 16.3 Topological Sort
- **DAG only** (directed acyclic graph)
- Linear ordering where all edges go from earlier to later
- **DFS-based**: run DFS, add vertex to front when finished
- **Time**: O(V+E)
- **Applications**: task scheduling, course prerequisites, build systems

---

## 17. Amortized Analysis

### Three Methods

| Method | Approach |
|--------|----------|
| **Aggregate** | Total cost of n operations / n = amortized cost per op |
| **Accounting** | Overcharge cheap ops, undercharge expensive ops; credit never negative |
| **Potential** | Amortized = actual + Φ(Дi) - Φ(Дi-1) |

### Key Amortized Results
| Data Structure | Operation | Amortized |
|----------------|-----------|-----------|
| Dynamic array | push | O(1) (doubling) |
| Stack | multi-pop | O(1) |
| Splay tree | all ops | O(log n) |
| Fibonacci heap | insert, decreaseKey | O(1) |
| Fibonacci heap | deleteMin | O(log n) |
| Binomial queue | insert | O(1) |
| Binomial queue | merge | O(log n) |

### Fibonacci Heap (Concept)
- Collection of heap-ordered trees (lazy merging)
- DecreaseKey: cut node, add to root list; cascading cut if parent was already cut
- **Key advantage**: Dijkstra/Prim become O(E + V·log V) instead of O((E+V)·log V)

---

## 18. Advanced Heap Variants

### Skew Heap
- Self-adjusting mergeable heap (like leftist but no npl)
- **All operations**: O(log n) amortized
- Merge: always swap children after merging right path
- Simpler than leftist heap, no extra storage

### Binomial Queue
- Collection of binomial trees B0, B1, B2, ...
- Bi has 2^i nodes; children are Bi-1, Bi-2, ..., B0
- Merge like binary addition (carry propagation)
- Insert: O(1) amortized; Merge: O(log n); DeleteMin: O(log n)

### Pairing Heap
- Simple structure: min-heap + child/sibling pointers
- Insert/Merge: O(1) actual
- DeleteMin: O(log n) amortized (two-pass merging)
- DecreaseKey: O(log n) amortized (best known practical)

---

## 19. External Sorting

### When data doesn't fit in memory
1. **Phase 1**: Read memory-sized chunks, sort in memory, write sorted runs to disk
2. **Phase 2**: K-way merge k runs at a time using k input buffers

### Replacement Selection
- Use min-heap instead of sorting chunks
- Run continues as long as new element ≥ last output
- Average run size = 2M (twice memory size)
- Reduces number of merge passes by ~half

### Complexity
- Total I/O = O(n/blockSize × log_k(n/M))
- k = number of merge buffers

---

## 20. Advanced Hashing

### Cuckoo Hashing
- Two tables, two hash functions
- On collision: evict existing to alternate table
- **Worst-case O(1)** lookup, insert, delete
- Occasionally needs full rehash (when cycle detected)
- Poor cache performance (two separate tables)

### Extendible Hashing
- Directory of pointers with global depth
- Buckets with local depth
- On insert: split bucket when full; double directory when globalDepth = localDepth
- **Only affected buckets need rewriting** → good for disk
- Application: database indexing

### Hopscotch Hashing
- Combines linear probing with hashing
- Each hash location has a "neighborhood" of nearby slots
- On collision: find empty slot in neighborhood, rearrange
- Good cache performance, bounded probe length

---

## 21. Common Exam Pitfalls & Tips

### Tree Pitfalls
1. **AVL Rotation Confusion**: Remember LL=right rotation, RR=left rotation (opposite of what you might think!)
2. **Red-Black Insert**: New node is always RED. Fix violations by checking uncle color.
3. **Heap Property**: Parent ≤ children (min-heap). No relationship between siblings!
4. **Leftist Heap**: Always merge along rightmost path, then swap children if needed.
5. **BST Delete**: When node has 2 children, replace with inorder successor (min of right subtree).

### Complexity Confusion
- **AVL vs Red-Black**: AVL has tighter height bound (1.44·log n vs 2·log n)
- **Binary Heap Merge**: O(n) - this is why we need leftist/skew heaps for efficient merging
- **Amortized vs Worst-case**: Splay tree is O(log n) amortized but O(n) worst-case

### Code Pitfalls
1. **Null pointer checks**: Always check for NULL before dereferencing!
2. **Update heights**: After rotation, update heights of both nodes.
3. **Balance factor**: AVL balance = height(left) - height(right), can be -1, 0, or 1.
4. **Heap indexing**: 1-indexed arrays make parent/child calculations simpler.

### Quick Memory Aids
- **AVL**: "At most 1 rotation per insert"
- **Red-Black**: "At most 2 rotations per insert"
- **Leftist Heap**: "Merge along rightmost path"
- **Binary Heap**: "Complete binary tree in array"
- **BST Inorder**: "Always gives sorted order"

---

## Key Formulas & Quick Reference

| Concept | Formula |
|---------|---------|
| Max nodes in binary tree of height h | 2^(h+1) - 1 |
| Height of balanced BST | O(log n) |
| Height of AVL tree | ≤ 1.44 · log₂(n) |
| Height of Red-Black tree | ≤ 2·log₂(n+1) |
| Heap: parent of k | ⌊k/2⌋ (1-indexed) |
| Heap: children of k | 2k, 2k+1 (1-indexed) |
| BST height (balanced) | O(log n) |
| BST height (degenerate) | O(n) |
| Heap sort time | O(n·log n) always |
| Merge sort time | O(n·log n) always, O(n) space |
| Quick sort time | O(n·log n) avg, O(n²) worst |
| Leftist Heap: all ops | O(log n) — merge, push, pop |
| Disjoint Set (by height) | O(log n) per operation |
| Disjoint Set (with path compression) | O(α(n)) ≈ O(1) amortized |
| B+ Tree height | O(log n) with large branching factor |
| Splay tree | Amortized O(log n) |
| k-d Tree: range search | O(√n + \|output\|) average |
| k-d Tree: nearest neighbor | O(log n) average |
| Suffix Array: construction | O(T·log T) — doubling algorithm |
| Suffix Array: pattern match | O(\|P\|·log\|T\|) |
| Suffix Tree: construction | O(T) nodes, O(T) storage |
| Suffix Tree: pattern match | O(\|P\|) |
| Fibonacci numbers | F(h) = F(h-1) + F(h-2), F(0)=1, F(1)=2 |
| AVL min nodes | F(h) ≈ φ^h, φ = (1+√5)/2 ≈ 1.618 |
| Red-Black null path | All null paths have same # of BLACK nodes |
| α(n) (inverse Ackermann) | Practically constant: α(2^65536) ≤ 5 |

---

## Example Code Files

| File | Topic |
|------|-------|
| `01_bst.cpp` | BST: insert, delete, traversals, reconstruction |
| `02_heap.cpp` | Binary heap: push, pop, heap sort |
| `03_avl.cpp` | AVL tree: 4 rotation cases, insert |
| `04_graph_bfs_dfs.cpp` | Graph: BFS, DFS, shortest path, cycle detection |
| `05_stack.cpp` | Stack: postfix eval, balanced symbols, infix→postfix |
| `06_queue.cpp` | Circular queue, BFS level-order traversal |
| `07_sorting.cpp` | Sorting comparison with timing |
| `08_hashing.cpp` | Hashing: linear/quadratic probing, chaining |
| `09_linkedlist.cpp` | Singly & doubly linked lists |
| `10_splay_and_rb.cpp` | Splay tree + Red-Black tree properties |
| `11_disjoint_set.cpp` | Union-Find: array, tree, by-height, path compression, maze |
| `12_leftist_heap.cpp` | Leftist heap: merge, push, pop |
| `13_kd_tree.cpp` | k-d tree: range search, nearest neighbor |
| `14_suffix_array.cpp` | Suffix array: doubling algorithm, pattern matching |
| `15_redblack.cpp` | Red-Black tree: full insert/delete implementation |
| `16_graph_algorithms.cpp` | Dijkstra, Prim/Kruskal MST, Topological Sort |
| `17_amortized_advanced_heaps.cpp` | Amortized analysis, Skew heap, Binomial queue, Fibonacci heap |
| `18_treap_pairing_heap.cpp` | Treap (randomized BST), Pairing heap |
| `19_external_sorting.cpp` | External sorting: k-way merge, replacement selection |
| `20_cuckoo_hashing.cpp` | Cuckoo hashing, Extendible hashing |

---

*Generated from course lecture slides + textbook (Weiss, 4th Ed.) for exam preparation.*
