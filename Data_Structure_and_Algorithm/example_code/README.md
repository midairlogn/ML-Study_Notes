# Data Structures & Algorithm - Example Code

C++ example programs for exam preparation. Each file illustrates key knowledge points with working implementations and output.

## File List

| # | File | Topic | Key Concepts |
|---|------|-------|-------------|
| 01 | `01_bst.cpp` | **Binary Search Tree** | Insert, find, delete (3 cases: leaf, one child, two children), preorder/inorder/postorder/level-order traversals, tree reconstruction from preorder+inorder |
| 02 | `02_heap.cpp` | **Binary Min-Heap** | Array-based 1-indexed heap, percolate up (push), percolate down (pop), build max-heap O(n), in-place heap sort O(n log n) |
| 03 | `03_avl.cpp` | **AVL Tree** | Balance factor, 4 rotation cases (LL, RR, LR, RL), single and double rotations, O(log n) height guarantee |
| 04 | `04_graph_bfs_dfs.cpp` | **Graph BFS & DFS** | Adjacency list, BFS with queue (shortest path in unweighted graph), DFS recursive & iterative (with stack), cycle detection, connected components |
| 05 | `05_stack.cpp` | **Stack** | Array-based stack, postfix expression evaluation, balanced symbol checking, infix-to-postfix conversion |
| 06 | `06_queue.cpp` | **Queue** | Circular array queue, front/rear pointers with modular arithmetic, BFS level-order tree traversal |
| 07 | `07_sorting.cpp` | **Sorting** | Insertion sort, bubble sort (flagged), selection sort, heap sort, merge sort, quick sort, timing comparison on 10000 elements |
| 08 | `08_hashing.cpp` | **Hashing** | Linear probing, quadratic probing, separate chaining, collision counting, load factor |
| 09 | `09_linkedlist.cpp` | **Linked List** | Singly linked (sorted insert, remove, search), doubly linked (forward & backward traversal, O(1) remove by pointer) |
| 10 | `10_splay_and_rb.cpp` | **Splay Tree & Red-Black Tree** | Splay operations (zig, zig-zig, zig-zag), RB tree properties & rules, comparison table of AVL vs RB vs Splay |
| 11 | `11_disjoint_set.cpp` | **Disjoint Set (Union-Find)** | Array implementation, tree implementation, union-by-height, path compression, amortized O(alpha(n)), maze generation application |
| 12 | `12_leftist_heap.cpp` | **Leftist Heap** | Null-path length (npl), leftist property, merge algorithm (3 cases), push/pop via merge, O(log n) all operations |
| 13 | `13_kd_tree.cpp` | **k-d Tree** | 2D point storage, balanced construction via median, range search with subtree pruning, nearest neighbor, insert |
| 14 | `14_suffix_array.cpp` | **Suffix Array** | Suffix definition, doubling algorithm O(T log T), suffix sorting, binary search pattern matching O(|P| log |T|) |
| 15 | `15_redblack.cpp` | **Red-Black Tree** | Full insert/delete implementation, rotations, color fix (recolor + rotate), NIL sentinel, all 3 RB rules maintained |
| 16 | `16_graph_algorithms.cpp` | **Graph Algorithms** | Dijkstra shortest path O((V+E) log V), Prim's MST O(E log V), Kruskal's MST O(E log E) with Union-Find, topological sort O(V+E) |
| 17 | `17_amortized_advanced_heaps.cpp` | **Amortized Analysis & Heaps** | Three amortized methods (aggregate, accounting, potential), skew heap, binomial queue concept, Fibonacci heap concept |
| 18 | `18_treap_pairing_heap.cpp` | **Treap & Pairing Heap** | Randomized BST (treap): BST by key + heap by random priority; pairing heap: two-pass merge, O(1) insert/merge |
| 19 | `19_external_sorting.cpp` | **External Sorting** | Initial sorted runs, k-way merge with priority queue, replacement selection (average run size 2M), polyphase merge |
| 20 | `20_cuckoo_hashing.cpp` | **Advanced Hashing** | Cuckoo hashing (two tables, O(1) worst-case), extendible hashing (directory with global/local depth, bucket splitting) |

## How to Compile & Run

```bash
# Linux / macOS
g++ -std=c++17 -o 01_bst 01_bst.cpp && ./01_bst

# Windows (MinGW)
g++ -std=c++17 -o 01_bst.exe 01_bst.cpp && 01_bst.exe

# Compile all at once
for f in *.cpp; do g++ -std=c++17 -o "${f%.cpp}" "$f"; done
```

## Knowledge Coverage

| Chapter | Topics | Files |
|---------|--------|-------|
| Trees | BST, traversals, reconstruction | 01 |
| Heaps | Binary heap, heap sort | 02 |
| Balanced Trees | AVL, Splay, Red-Black, Treap | 03, 10, 15, 18 |
| Graphs | BFS, DFS, Dijkstra, MST, Topo Sort | 04, 16 |
| Stacks & Queues | Postfix eval, balanced symbols, circular queue | 05, 06 |
| Sorting | 6 algorithms with timing comparison | 07 |
| Hashing | Linear/quadratic probing, chaining, cuckoo, extendible | 08, 20 |
| Linked Lists | Singly, doubly linked lists | 09 |
| Disjoint Sets | Union-Find with optimizations | 11 |
| Advanced Heaps | Leftist, Skew, Binomial, Pairing, Fibonacci | 12, 17, 18 |
| String Algorithms | Suffix array (doubling algorithm) | 14 |
| Geometric | k-d tree (range search, nearest neighbor) | 13 |
| External | External sorting, replacement selection | 19 |
| Analysis | Amortized analysis (3 methods) | 17 |
