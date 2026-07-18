# Data Structure Final Exam — Practice Questions

> Focus area: Trees and priority queues (AVL, Red-Black, heaps, leftist/skew heaps, and related comparisons)
> Use these questions to test your understanding before the exam.
> A complete answer key is provided in Section 7.

---

## Table of Contents
1. [AVL Tree Questions](#1-avl-tree-questions)
2. [Red-Black Tree Questions](#2-red-black-tree-questions)
3. [Heap Questions](#3-heap-questions)
4. [Leftist & Skew Heap Questions](#4-leftist--skew-heap-questions)
5. [BST & Tree Traversal Questions](#5-bst--tree-traversal-questions)
6. [General Tree Concept Questions](#6-general-tree-concept-questions)
7. [Answers & Explanations](#7-answers--explanations)

---

## 1. AVL Tree Questions

### Q1.1 — Rotation Identification
Insert the keys **30, 20, 10** into an initially empty AVL tree one by one. After each insertion:
- (a) Draw the resulting tree
- (b) Identify which node becomes unbalanced
- (c) State the rotation case (LL, RR, LR, RL)
- (d) Draw the tree after rotation

### Q1.2 — Double Rotation
Insert the keys **50, 30, 40** into an initially empty AVL tree.
- (a) After inserting 40, which node is unbalanced?
- (b) What rotation is needed? Why isn't a single rotation enough?
- (c) Draw the before and after trees.

### Q1.3 — AVL Height Bounds
- (a) What is the maximum height of an AVL tree with 7 nodes?
- (b) What is the minimum number of nodes in an AVL tree of height 5?
- (c) Prove or disprove: An AVL tree with 15 nodes must have height ≤ 4.

### Q1.4 — Mixed Insertions
Insert the following keys into an initially empty AVL tree: **10, 20, 30, 15, 25, 12, 5**
Draw the tree after each insertion. Mark any rotations performed.

### Q1.5 — AVL vs BST
- (a) Insert 1, 2, 3, 4, 5, 6, 7 into an empty BST. What is the height?
- (b) Insert the same keys into an empty AVL tree. What is the height?
- (c) Why does this difference matter for search performance?

---

## 2. Red-Black Tree Questions

### Q2.1 — Property Verification
Which of the following are valid Red-Black trees? If not, which property is violated?
```
Tree A:         Tree B:         Tree C:
    10(B)           10(R)           10(B)
   /  \           /  \            /  \
  5(R) 15(R)    5(B)  15(B)     5(B)  15(B)
 / \           / \              / \
3(B) 7(B)     3(R) 7(R)       3(R) 7(R)
```

### Q2.2 — Insertion Cases
Insert the key **25** into the following Red-Black tree:
```
    20(B)
   /    \
 10(R)  30(R)
/ \
5(B) 15(B)
```
- (a) Where does 25 go? What color is it initially?
- (b) What violation occurs?
- (c) What is the uncle's color?
- (d) Apply the fix. Draw the final tree.

### Q2.3 — Recoloring vs Rotation
For each scenario, state whether you need **recoloring** or **rotation**:
- (a) Insert into left-left of a red parent, uncle is red
- (b) Insert into right-right of a red parent, uncle is black
- (c) Insert into left-right of a red parent, uncle is red
- (d) Insert into right-left of a red parent, uncle is black

### Q2.4 — Red-Black Tree Properties
- (a) Assuming black-height counts black nodes on a path from a node (not including that node) down to a `NULL` leaf, what is the black-height of a tree whose root has a left child `B`, whose left child is also `B`, and then `NULL`?
- (b) Can a Red-Black tree node with exactly one child be black?
- (c) What is the maximum number of red nodes in a row on any path?

### Q2.5 — Comparison with AVL
Fill in the blanks:
- AVL trees have height at most \_\_\_\_\_ · log₂(n)
- Red-Black trees have height at most \_\_\_\_\_ · log₂(n+1)
- AVL requires at most \_\_\_\_\_ rotation(s) per insert
- Red-Black requires at most \_\_\_\_\_ rotation(s) per insert
- Red-Black uses \_\_\_\_\_ extra bit(s) per node; AVL typically stores a \_\_\_\_\_ or a height field per node

---

## 3. Heap Questions

### Q3.1 — Array to Heap
Convert the following array into a **min-heap** by drawing the heapify process step by step:
```
Array: [_, 8, 5, 12, 3, 7, 1, 15]  (1-indexed)
```
- (a) Draw the initial complete binary tree
- (b) Show the result after heapifying each non-leaf node (bottom-up)
- (c) Write the final array

### Q3.2 — Push and Pop
Given this min-heap: `[_, 2, 5, 8, 10, 7, 12]`
- (a) Push key **1**. Show each percolate-up step.
- (b) After pushing 1, pop the minimum. Show each percolate-down step.
- (c) What is the final heap?

### Q3.3 — Heap Sort
Apply **heap sort** (ascending order) to the array: `[4, 10, 3, 8, 1]`
- (a) Build a max-heap from the array. Show each step.
- (b) Perform the extract-max phase. Show the array after each swap+heapify.

### Q3.4 — Build Heap Complexity
- (a) Why is building a heap from an unsorted array O(n) and not O(n·log n)?
- (b) How many nodes are at depth k? How many swaps can each perform?
- (c) What is the total swap count expressed as a summation?

### Q3.5 — Heap Properties
- (a) In a min-heap of n elements, what is the height?
- (b) In a max-heap, can the smallest element be at a non-leaf node?
- (c) Can a complete binary tree violate the heap property? Give an example.

---

## 4. Leftist & Skew Heap Questions

### Q4.1 — Null-Path Length
Compute the `npl` (null-path length) for each node in this tree:
```
      A(npl=?)
     / \
    B   C(npl=?)
   / \    \
  D   E    F
 / \
G   H
```
- (a) What is `npl(G)`?
- (b) What is `npl(B)`?
- (c) What is `npl(A)`?
- (d) Does this tree satisfy the leftist property? Why or why not?

### Q4.2 — Leftist Heap Merge
Merge the following two leftist heaps:
```
Heap 1:       Heap 2:
    3            2
   / \          / \
  5   7        8   4
 /              /
9              10
```
- (a) Which root is smaller?
- (b) Merge the smaller root's right subtree with the other heap
- (c) After merging, check and fix the leftist property
- (d) Draw the final leftist heap

### Q4.3 — Skew Heap vs Leftist Heap
- (a) What is the key difference in merge between skew heap and leftist heap?
- (b) Skew heap operations are O(log n) \_\_\_\_\_ (amortized vs worst-case)
- (c) Leftist heap operations are O(log n) \_\_\_\_\_ (amortized vs worst-case)
- (d) Why is skew heap simpler to implement?

### Q4.4 — Push and Pop on Leftist Heap
Starting from this leftist heap:
```
    5
   / \
  10   8
 / \
12  15
```
- (a) Push key 3: create single-node heap, merge
- (b) Pop minimum: remove root, merge left and right subtrees

### Q4.5 — Comparison Table
Fill in the table:

| Operation | Binary Heap | Leftist Heap | Skew Heap | Binomial Queue |
|-----------|------------|--------------|-----------|----------------|
| Push      |            |              |           |                |
| Pop       |            |              |           |                |
| Merge     |            |              |           |                |
| `FindMin` |            |              |           |                |

---

## 5. BST & Tree Traversal Questions

### Q5.1 — BST Operations
Insert the following keys into an empty BST and draw the tree: **50, 30, 70, 20, 40, 60, 80, 10**
- (a) What is the height?
- (b) Delete 30 (which has two children). Show the result.
- (c) Delete 50 (root, two children). Show the result.

### Q5.2 — Traversal Orders
For this BST:
```
        50
       /  \
      30    70
     / \   / \
    20  40 60  80
```
- (a) Write the preorder traversal
- (b) Write the inorder traversal
- (c) Write the postorder traversal
- (d) Write the level-order traversal

### Q5.3 — Reconstruct Tree
Given:
- Preorder:  A B D E C F
- Inorder:   D B E A F C

(a) Draw the tree.
(b) What is the postorder traversal?

### Q5.4 — BST Property
- (a) Insert 5, 3, 7, 3 into a BST. What happens to the duplicate 3?
- (b) Can a BST have two nodes with the same value? (by convention)
- (c) Why does inorder traversal of BST give sorted order?

---

## 6. General Tree Concept Questions

### Q6.1 — True or False
- (a) Every AVL tree is a BST. \_\_\_\_\_
- (b) Every BST is an AVL tree. \_\_\_\_\_
- (c) Every complete binary tree is an AVL tree. \_\_\_\_\_
- (d) Every binary heap is a complete binary tree. \_\_\_\_\_
- (e) A Red-Black tree with height h has at most h + 1 black nodes on any root-to-leaf path if height is measured in edges. \_\_\_\_\_
- (f) Leftist heap merge is O(n) in the worst case. \_\_\_\_\_
- (g) Skew heap operations are O(log n) worst-case. \_\_\_\_\_
- (h) Heap sort is a stable sorting algorithm. \_\_\_\_\_

### Q6.2 — Complexity Summary
Fill in the table with worst-case complexities:

| Data Structure | Search | Insert | Delete | Merge |
|---------------|--------|--------|--------|-------|
| BST (balanced) |        |        |        |       |
| AVL Tree       |        |        |        |       |
| Red-Black Tree |        |        |        |       |
| Binary Heap    |        |        |        |       |
| Leftist Heap   |        |        |        |       |
| Skew Heap      |        |        |        |       |

### Q6.3 — When to Use What
Match each scenario with the best data structure:
- (a) Need O(log n) merge → \_\_\_\_\_
- (b) Need fastest single-element search → \_\_\_\_\_
- (c) Need priority queue with array-based storage → \_\_\_\_\_
- (d) Need self-adjusting tree with no extra storage → \_\_\_\_\_
- (e) Need amortized `O(1)` insert and `decreaseKey` → \_\_\_\_\_

---

## 7. Answers & Explanations

### Q1.1 — Rotation Identification
```
Insert 30:
    30

Insert 20:
    30
   /
  20

Insert 10:
    30   ← unbalanced at 30
   /
  20
 /
10

After rotation:
   20
  /  \
 10   30
```
- Unbalanced node: 30
- Case: LL
- Fix: single right rotation at 30

### Q1.2 — Double Rotation
```
Before rebalancing:
    50   ← unbalanced at 50
   /
  30
    \
     40

After LR rotation:
    40
   /  \
  30   50
```
- (a) Unbalanced node: 50
- (b) Rotation: LR, so left-rotate 30, then right-rotate 50
- (c) A single rotation is not enough because the new key was inserted in the right subtree of the left child

### Q1.3 — AVL Height Bounds
- (a) Maximum height with 7 nodes is **3** if height counts edges, because an AVL tree of height 4 needs at least 12 nodes
- (b) Minimum nodes for height 5 is **20** using `N(h) = N(h-1) + N(h-2) + 1` with `N(0)=1`, `N(1)=2`
- (c) **Proved**: with 15 nodes, height must be `<= 4` because height 5 would require at least 20 nodes

### Q1.4 — Mixed Insertions
```
Insert 10:
10

Insert 20:
10
  \
   20

Insert 30 -> rotate left at 10:
   20
  /  \
 10   30

Insert 15:
   20
  /  \
 10   30
   \
   15

Insert 25:
   20
  /  \
 10   30
   \
   15 25

Insert 12 -> rotate right at 15, then left at 10:
      20
     /  \
   12    30
  / \   /
10  15 25

Insert 5:
      20
     /  \
   12    30
  / \   /
10  15 25
/
5
```
- Rotations performed: after inserting 30, RR imbalance at 10 -> left rotation; after inserting 12, RL imbalance at 10 -> right rotation at 15, then left rotation at 10

### Q1.5 — AVL vs BST
- (a) BST height is **6** if height counts edges, because inserting sorted keys creates a chain
- (b) AVL height is **2** with 7 nodes in a perfectly balanced tree
- (c) Search time depends on height: BST search becomes `O(n)` here, while AVL search stays `O(log n)`

### Q2.1 — Property Verification
- Tree A: **valid**. Root is black, no red node has a red child, and all root-to-NULL paths have the same black-height
- Tree B: **invalid**. The root is red, violating the property that the root must be black
- Tree C: **valid**. Root is black, red nodes have black children, and every root-to-NULL path has the same black-height

### Q2.2 — Insertion Cases
```
Initial:
    20(B)
   /    \
 10(R)  30(R)
 / \    /
5(B)15(B)25(R)

After recoloring:
    20(B)
   /    \
 10(B)  30(B)
 / \    /
5(B)15(B)25(R)
```
- (a) 25 goes to the left of 30 and is inserted red
- (b) Violation: red parent (30) with red child (25)
- (c) Uncle is 10, which is red
- (d) Fix: recolor 10 and 30 to black, recolor 20 temporarily red, then force the root back to black

### Q2.3 — Recoloring vs Rotation
- (a) Recoloring
- (b) Rotation
- (c) Recoloring
- (d) Rotation

### Q2.4 — Red-Black Tree Properties
- (a) Black-height is **2** under the stated convention
- (b) Yes. A black node may have exactly one child if the Red-Black properties still hold overall
- (c) At most **one** red node can follow another red node, so the maximum number of consecutive red nodes is 1

### Q2.5 — Comparison with AVL
- AVL trees have height at most about **1.44** `· log₂(n)`
- Red-Black trees have height at most **2** `· log₂(n+1)`
- AVL requires at most **2** rotations per insert
- Red-Black requires at most **2** rotations per insert
- Red-Black uses **1** extra bit per node; AVL typically stores a **balance factor** or a height field per node

### Q3.1 — Array to Heap
Initial array: `[_, 8, 5, 12, 3, 7, 1, 15]`

```
Initial tree:
        8
      /   \
     5     12
    / \   / \
   3   7 1  15
```

Bottom-up heapify uses indices 3, 2, 1.

- Heapify index 3: value 12, children 1 and 15 -> swap with 1
```
        8
      /   \
     5     1
    / \   / \
   3   7 12 15
```
- Heapify index 2: value 5, children 3 and 7 -> swap with 3
```
        8
      /   \
     3     1
    / \   / \
   5   7 12 15
```
- Heapify index 1: value 8, children 3 and 1 -> swap with 1
```
        1
      /   \
     3     8
    / \   / \
   5   7 12 15
```
- Continue percolating 8: children 12 and 15 are larger, so stop

Final array: `[_, 1, 3, 8, 5, 7, 12, 15]`

### Q3.2 — Push and Pop
- (a) Push 1: `[_, 2, 5, 8, 10, 7, 12, 1] -> [_, 2, 5, 1, 10, 7, 12, 8] -> [_, 1, 5, 2, 10, 7, 12, 8]`
- (b) Pop min: move last element to root -> `[_, 8, 5, 2, 10, 7, 12]`, then percolate down: swap 8 with 2 (smaller child) -> `[_, 2, 5, 8, 10, 7, 12]`; now 8 has only child 12, so stop
- (c) Final heap: `[_, 2, 5, 8, 10, 7, 12]`

### Q3.3 — Heap Sort
- (a) Build max-heap from `[4, 10, 3, 8, 1]`:
  - Heapify index 2: 10 already dominates 8 and 1 -> `[4, 10, 3, 8, 1]`
  - Heapify index 1: swap 4 with 10 -> `[10, 4, 3, 8, 1]`
  - Continue heapifying index 2: swap 4 with 8 -> `[10, 8, 3, 4, 1]`
- (b) Extract-max phase:
  - swap -> `[1, 8, 3, 4, 10]`, heapify -> `[8, 4, 3, 1, 10]`
  - swap -> `[1, 4, 3, 8, 10]`, heapify -> `[4, 1, 3, 8, 10]`
  - swap -> `[3, 1, 4, 8, 10]`, heapify -> `[3, 1, 4, 8, 10]`
  - swap -> `[1, 3, 4, 8, 10]`

### Q3.4 — Build Heap Complexity
- (a) Most nodes are near the bottom, so they can move only a small number of levels
- (b) At depth `k`, there are at most `2^k` nodes, and each can move at most `h-k` levels
- (c) Total work is bounded by `sum_{k=0}^{h} 2^k (h-k) = O(n)`

### Q3.5 — Heap Properties
- (a) Height is `floor(log₂ n)` if height counts edges
- (b) Usually no if all keys are distinct, because every non-leaf must be at least as large as its children. With duplicate keys, a smallest value could appear at a non-leaf only if its children have the same value
- (c) Yes. Example complete tree with root 2 and left child 10 violates the max-heap property

### Q4.1 — Null-Path Length
- (a) `npl(G) = 0`
- (b) `npl(B) = 1`
- (c) `npl(A) = 1`
- (d) No. Node C has no left child but has a right child, so it violates the leftist property `npl(left) >= npl(right)`

### Q4.2 — Leftist Heap Merge
- (a) Smaller root is 2
- (b) Merge the right subtree of 2 with heap 1, so merge rooted at 4 with heap rooted at 3
- (c) After recursive merge, swap children where needed so each node satisfies the leftist property
- (d) One valid final heap is:
```
      2
     / \
    3   8
   / \
  4   5
 /   / \
10  9   7
```

### Q4.3 — Skew Heap vs Leftist Heap
- (a) Leftist heaps maintain and compare `npl`; skew heaps always swap children during merge and do not store `npl`
- (b) Skew heap operations are `O(log n)` **amortized**
- (c) Leftist heap operations are `O(log n)` **worst-case**
- (d) Skew heap is simpler because it does not store or update null-path lengths

### Q4.4 — Push and Pop on Leftist Heap
- (a) Push 3 by merging the single-node heap with the original heap, giving root 3
- (b) Pop min by removing 3 and merging its left and right subheaps; the resulting root is 5

One valid sequence is:
```
After push 3:
    3
   / \
  5   -
 / \
10  8
 / \
12 15

After pop min:
    5
   / \
 10   8
 / \
12 15
```

### Q4.5 — Comparison Table

| Operation | Binary Heap | Leftist Heap | Skew Heap | Binomial Queue |
|-----------|-------------|--------------|-----------|----------------|
| Push      | O(log n)    | O(log n)     | O(log n)* | O(1)           |
| Pop       | O(log n)    | O(log n)     | O(log n)* | O(log n)       |
| Merge     | O(n)        | O(log n)     | O(log n)* | O(log n)       |
| `FindMin` | O(1)        | O(1)         | O(1)      | O(1)           |

`*` amortized

### Q5.1 — BST Operations
Initial BST after inserting `50, 30, 70, 20, 40, 60, 80, 10`:
```
        50
      /    \
    30      70
   /  \    /  \
 20   40  60  80
 /
10
```
- (a) Height is **3** if height counts edges
- (b) Delete 30 by replacing it with its inorder successor 40:
```
        50
      /    \
    40      70
   /       /  \
 20       60  80
 /
10
```
- (c) Delete 50 by replacing it with its inorder successor 60:
```
        60
      /    \
    30      70
   /  \      \
 20   40      80
 /
10
```

### Q5.2 — Traversal Orders
- Preorder: `50, 30, 20, 40, 70, 60, 80`
- Inorder: `20, 30, 40, 50, 60, 70, 80`
- Postorder: `20, 40, 30, 60, 80, 70, 50`
- Level-order: `50, 30, 70, 20, 40, 60, 80`

### Q5.3 — Reconstruct Tree
```
        A
       / \
      B   C
     / \ /
    D  E F
```
- Postorder: `D, E, B, F, C, A`

### Q5.4 — BST Property
- (a) By common convention, the duplicate 3 is either rejected or consistently placed on one chosen side; many textbook BSTs disallow duplicates
- (b) Yes, by convention, if the implementation defines a duplicate-handling rule
- (c) Inorder visits `left -> root -> right`, which lists BST keys in sorted order because all left-subtree keys are smaller and all right-subtree keys are larger

### Q6.1 — True or False
- (a) **True** — every AVL tree is a BST
- (b) **False** — a BST may be unbalanced
- (c) **False** — a complete binary tree need not satisfy BST ordering, so it need not be AVL
- (d) **True** — binary heaps are complete binary trees by definition
- (e) **True** — if height is measured in edges, a root-to-leaf path has at most `h + 1` nodes total, so it can have at most `h + 1` black nodes
- (f) **False** — leftist heap merge is `O(log n)` worst-case
- (g) **False** — skew heap operations are `O(log n)` amortized, not worst-case
- (h) **False** — heap sort is not stable

### Q6.2 — Complexity Summary

| Data Structure | Search | Insert | Delete | Merge |
|---------------|--------|--------|--------|-------|
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(n) |
| AVL Tree       | O(log n) | O(log n) | O(log n) | O(n) |
| Red-Black Tree | O(log n) | O(log n) | O(log n) | O(n) |
| Binary Heap    | O(n)     | O(log n) | O(log n) | O(n) |
| Leftist Heap   | O(n)     | O(log n) | O(log n) | O(log n) |
| Skew Heap      | O(n)     | O(log n)* | O(log n)* | O(log n)* |

`*` amortized

### Q6.3 — When to Use What
- (a) Need `O(log n)` merge -> **Leftist Heap**, **Skew Heap**, or **Binomial Queue**
- (b) Need fastest single-element search -> **AVL Tree**
- (c) Need priority queue with array-based storage -> **Binary Heap**
- (d) Need self-adjusting tree with no extra storage -> **Splay Tree**
- (e) Need amortized `O(1)` insert and `decreaseKey` -> **Fibonacci Heap**
