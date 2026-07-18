// 04_graph_bfs_dfs.cpp - Graph Traversal: BFS and DFS
// Knowledge points: BFS (queue, level-order), DFS (stack/recursion, depth-first)

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
using namespace std;

// ===== Adjacency List Representation =====
class Graph {
private:
    int V;  // number of vertices
    vector<vector<int>> adj;  // adjacency list

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);  // undirected graph
    }

    // ===== BFS: Breadth-First Search =====
    // Uses Queue - explores all neighbors at current depth before going deeper
    // Time: O(V + E), Space: O(V)
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS from " << start << ": ";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            // Enqueue all unvisited neighbors
            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // BFS: Find shortest path in unweighted graph
    void BFS_ShortestPath(int start, int target) {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            if (v == target) {
                // Reconstruct path
                vector<int> path;
                for (int curr = target; curr != -1; curr = parent[curr])
                    path.push_back(curr);

                cout << "Shortest path from " << start << " to " << target << ": ";
                for (int i = path.size() - 1; i >= 0; i--)
                    cout << path[i] << (i > 0 ? " -> " : "");
                cout << " (length: " << path.size() - 1 << ")" << endl;
                return;
            }

            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = v;
                    q.push(neighbor);
                }
            }
        }
        cout << "No path from " << start << " to " << target << endl;
    }

    // ===== DFS: Depth-First Search (Recursive) =====
    // Uses Recursion (implicit stack) - explores as deep as possible first
    // Time: O(V + E), Space: O(V) for recursion stack
    void DFS_Recursive(int start) {
        vector<bool> visited(V, false);
        cout << "DFS (recursive) from " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    // ===== DFS: Depth-First Search (Iterative with Stack) =====
    void DFS_Iterative(int start) {
        vector<bool> visited(V, false);
        stack<int> s;

        s.push(start);
        cout << "DFS (iterative) from " << start << ": ";

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (visited[v]) continue;
            visited[v] = true;
            cout << v << " ";

            // Push neighbors in reverse order to match recursive DFS
            for (int i = adj[v].size() - 1; i >= 0; i--) {
                if (!visited[adj[v][i]]) {
                    s.push(adj[v][i]);
                }
            }
        }
        cout << endl;
    }

    // ===== Detect Cycle (DFS) =====
    bool hasCycle() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (hasCycleUtil(i, visited, -1))
                    return true;
            }
        }
        return false;
    }

    bool hasCycleUtil(int v, vector<bool>& visited, int parent) {
        visited[v] = true;
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (hasCycleUtil(neighbor, visited, v))
                    return true;
            } else if (neighbor != parent) {
                return true;  // back edge = cycle
            }
        }
        return false;
    }

    // ===== Connected Components =====
    int countComponents() {
        vector<bool> visited(V, false);
        int count = 0;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFSUtil(i, visited);
                count++;
            }
        }
        return count;
    }
};

// ===== BFS on Binary Tree (Level-Order Traversal) =====
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

void levelOrderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    queue<TreeNode*> q;
    q.push(root);

    cout << "Level-order: ";
    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    cout << endl;
}

// Print tree by levels
void printByLevels(TreeNode* root) {
    if (root == nullptr) return;
    queue<TreeNode*> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int size = q.size();
        cout << "Level " << level << ": ";
        for (int i = 0; i < size; i++) {
            TreeNode* curr = q.front();
            q.pop();
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << endl;
        level++;
    }
}

int main() {
    // ===== Graph BFS/DFS Demo =====
    cout << "========================================" << endl;
    cout << "  Graph BFS & DFS Demo" << endl;
    cout << "========================================" << endl;

    // Graph:
    //     0 --- 1 --- 2
    //     |     |     |
    //     3 --- 4     5
    //           |
    //           6
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 4);
    g.addEdge(4, 6);

    cout << "\nGraph structure:" << endl;
    cout << "    0 --- 1 --- 2" << endl;
    cout << "    |     |     |" << endl;
    cout << "    3 --- 4     5" << endl;
    cout << "          |" << endl;
    cout << "          6" << endl;

    cout << "\n--- BFS (Queue-based, level by level) ---" << endl;
    g.BFS(0);

    cout << "\n--- DFS (Recursive, depth first) ---" << endl;
    g.DFS_Recursive(0);

    cout << "\n--- DFS (Iterative with Stack) ---" << endl;
    g.DFS_Iterative(0);

    cout << "\n--- BFS Shortest Path ---" << endl;
    g.BFS_ShortestPath(0, 5);
    g.BFS_ShortestPath(0, 6);

    cout << "\n--- Cycle Detection ---" << endl;
    cout << "Has cycle: " << (g.hasCycle() ? "Yes" : "No") << endl;

    cout << "\n--- Connected Components ---" << endl;
    cout << "Number of components: " << g.countComponents() << endl;

    // ===== BFS on Binary Tree =====
    cout << "\n========================================" << endl;
    cout << "  BFS on Binary Tree (Level-Order)" << endl;
    cout << "========================================" << endl;

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

    levelOrderTraversal(root);
    cout << endl;
    printByLevels(root);

    cout << "\n========================================" << endl;
    cout << "  BFS vs DFS Summary" << endl;
    cout << "========================================" << endl;
    cout << "BFS: Queue, level-by-level, shortest path (unweighted)" << endl;
    cout << "DFS: Stack/Recursion, branch-by-branch, cycle detection" << endl;
    cout << "Both: O(V + E) time, O(V) space" << endl;

    // Clean up tree
    delete root->left->left;
    delete root->left->right;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
