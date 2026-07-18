// 16_graph_algorithms.cpp - Dijkstra, MST (Prim/Kruskal), Topological Sort
// Knowledge points: shortest path, minimum spanning tree, DAG ordering

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <functional>
using namespace std;

// ===== Graph Representation =====
struct Edge {
    int to, weight;
};

struct weightedEdge {
    int from, to, weight;
    bool operator<(const weightedEdge& o) const { return weight < o.weight; }
};

class WeightedGraph {
    int V;
    vector<vector<Edge>> adj;
public:
    WeightedGraph(int v) : V(v), adj(v) {}
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // undirected
    }
    void addDirectedEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }
    const vector<Edge>& neighbors(int v) const { return adj[v]; }
    int vertices() const { return V; }
};

// ===== 1. Dijkstra's Shortest Path - O((V+E) log V) =====
// Greedy: always process the closest unvisited vertex
void dijkstra(const WeightedGraph& g, int src) {
    int V = g.vertices();
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    // min-heap: (distance, vertex)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

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

    cout << "Dijkstra from vertex " << src << ":" << endl;
    for (int i = 0; i < V; i++) {
        cout << "  to " << i << ": dist=" << (dist[i] == INT_MAX ? -1 : dist[i])
             << ", path=";
        // Reconstruct path
        vector<int> path;
        for (int v = i; v != -1; v = parent[v]) path.push_back(v);
        for (int j = path.size()-1; j >= 0; j--)
            cout << path[j] << (j > 0 ? " -> " : "");
        cout << endl;
    }
}

// ===== 2. Prim's MST - O(E log V) =====
// Greedy: always add the cheapest edge connecting tree to non-tree
void primMST(const WeightedGraph& g) {
    int V = g.vertices();
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

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

    cout << "Prim's MST:" << endl;
    int totalWeight = 0;
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            cout << "  " << parent[i] << " -- " << i << " (weight " << key[i] << ")" << endl;
            totalWeight += key[i];
        }
    }
    cout << "Total MST weight: " << totalWeight << endl;
}

// ===== 3. Kruskal's MST - O(E log E) =====
// Greedy: sort all edges, add cheapest that doesn't form cycle
class KruskalUF {
    vector<int> parent, rank;
public:
    KruskalUF(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] != i) parent[i] = find(parent[i]);
        return parent[i];
    }
    bool unite(int i, int j) {
        int ri = find(i), rj = find(j);
        if (ri == rj) return false;
        if (rank[ri] < rank[rj]) swap(ri, rj);
        parent[rj] = ri;
        if (rank[ri] == rank[rj]) rank[ri]++;
        return true;
    }
};

void kruskalMST(const WeightedGraph& g) {
    int V = g.vertices();
    vector<weightedEdge> edges;
    for (int u = 0; u < V; u++)
        for (auto [v, w] : g.neighbors(u))
            if (u < v) edges.push_back({u, v, w});

    sort(edges.begin(), edges.end());

    KruskalUF uf(V);
    cout << "Kruskal's MST:" << endl;
    int totalWeight = 0, count = 0;
    for (auto [u, v, w] : edges) {
        if (uf.unite(u, v)) {
            cout << "  " << u << " -- " << v << " (weight " << w << ")" << endl;
            totalWeight += w;
            if (++count == V - 1) break;
        }
    }
    cout << "Total MST weight: " << totalWeight << endl;
}

// ===== 4. Topological Sort (DFS-based) =====
void topologicalSortUtil(int v, const vector<vector<int>>& adj,
                         vector<bool>& visited, vector<int>& result) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u])
            topologicalSortUtil(u, adj, visited, result);
    }
    result.push_back(v);
}

void topologicalSort(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    vector<int> result;
    for (int i = 0; i < V; i++) {
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, result);
    }
    reverse(result.begin(), result.end());
    cout << "Topological order: ";
    for (int v : result) cout << v << " ";
    cout << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  Graph Algorithms Demo" << endl;
    cout << "========================================" << endl;

    // Weighted graph:
    //   0 --10-- 1 --20-- 3
    //   |        |        |
    //   5       15       8
    //   |        |        |
    //   2 --30-- 4 --50-- 3
    WeightedGraph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 15);
    g.addEdge(1, 3, 20);
    g.addEdge(1, 4, 15);
    g.addEdge(2, 4, 30);
    g.addEdge(3, 4, 8);
    g.addEdge(3, 0, 12);

    cout << "\n--- Dijkstra's Shortest Path ---" << endl;
    dijkstra(g, 0);

    cout << "\n--- Prim's MST ---" << endl;
    primMST(g);

    cout << "\n--- Kruskal's MST ---" << endl;
    kruskalMST(g);

    // Topological Sort
    cout << "\n--- Topological Sort ---" << endl;
    // DAG: course prerequisites
    // 0->1, 0->2, 1->3, 2->3, 2->4, 3->5, 4->5
    int n = 6;
    vector<vector<int>> dag(n);
    dag[0] = {1, 2};
    dag[1] = {3};
    dag[2] = {3, 4};
    dag[3] = {5};
    dag[4] = {5};

    cout << "DAG (course prerequisites):" << endl;
    cout << "  0->1, 0->2, 1->3, 2->3, 2->4, 3->5, 4->5" << endl;
    topologicalSort(n, dag);

    cout << "\n========================================" << endl;
    cout << "  Graph Algorithm Complexity" << endl;
    cout << "========================================" << endl;
    cout << "Dijkstra:   O((V+E) log V) - no negative weights" << endl;
    cout << "Prim:       O(E log V) - greedy edge selection" << endl;
    cout << "Kruskal:    O(E log E) - sort edges, union-find" << endl;
    cout << "Topo Sort:  O(V+E) - DFS on DAG" << endl;

    return 0;
}
