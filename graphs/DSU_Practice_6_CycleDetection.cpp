// GFG: Detect Cycle in Undirected Graph using DSU
// Problem: Given an undirected graph with V vertices and E edges,
// check whether it contains any cycle or not using DSU.

#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rank;
    
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int node) {
        if(node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }
    
    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU == rootV) return false;  // Cycle detected!
        
        if(rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if(rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        
        return true;
    }
};

class Solution {
public:
    bool detectCycle(int V, vector<pair<int, int>>& edges) {
        DSU dsu(V);
        
        for(auto& edge : edges) {
            int u = edge.first;
            int v = edge.second;
            
            // If u and v are already in same set, adding this edge creates cycle
            if(dsu.find(u) == dsu.find(v)) {
                return true;  // Cycle detected
            }
            
            // Otherwise, union them
            dsu.unite(u, v);
        }
        
        return false;  // No cycle
    }
};

/*
═══════════════════════════════════════════════════════════════════
CYCLE DETECTION USING DSU
═══════════════════════════════════════════════════════════════════

CONCEPT:
In an undirected graph, a cycle exists when we try to add an edge
between two vertices that are already connected (in same component).

ALGORITHM:
1. Initially, each vertex is in its own set
2. For each edge (u, v):
   - Find parent of u and v
   - If same parent: CYCLE! (already connected via some path)
   - If different: Union them (add edge to spanning tree)

VISUALIZATION:
Initial: {0} {1} {2} {3}

Edge (0,1): Different sets → Union → {0,1} {2} {3}
Edge (1,2): Different sets → Union → {0,1,2} {3}
Edge (2,0): SAME SET! → CYCLE DETECTED!

Path exists: 0-1-2, and we're trying to add 2-0
This creates a cycle: 0-1-2-0

WHY THIS WORKS:
- In a tree/forest, no vertex is reachable from itself
- When we try to connect two vertices in same component,
  we create an alternate path between them → cycle

COMPARISON WITH DFS:
DSU Approach:
  + Works with edge list (no need for adjacency list)
  + Better for Kruskal's MST (already using DSU)
  + O(E·α(n)) time
  
DFS Approach:
  + Can detect where the cycle is
  + Works for directed graphs too
  + O(V + E) time

COMPLEXITY:
Time: O(E·α(n)) ≈ O(E)
Space: O(V)

KEY INSIGHT:
DSU naturally tracks connected components. If both endpoints
of an edge are in same component, there's already a path between
them. Adding this edge creates a cycle.

NOTE: This only works for UNDIRECTED graphs!
For directed graphs, use DFS with recursion stack.
═══════════════════════════════════════════════════════════════════
*/

int main() {
    Solution sol;
    
    // Test 1: Has cycle (0-1-2-0)
    int V1 = 3;
    vector<pair<int, int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
    cout << "Test 1 (has cycle): " << (sol.detectCycle(V1, edges1) ? "Yes" : "No") << endl;
    
    // Test 2: No cycle (tree)
    int V2 = 4;
    vector<pair<int, int>> edges2 = {{0, 1}, {1, 2}, {2, 3}};
    cout << "Test 2 (no cycle): " << (sol.detectCycle(V2, edges2) ? "Yes" : "No") << endl;
    
    // Test 3: Has cycle (0-1-2-3-0)
    int V3 = 5;
    vector<pair<int, int>> edges3 = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 4}};
    cout << "Test 3 (has cycle): " << (sol.detectCycle(V3, edges3) ? "Yes" : "No") << endl;
    
    return 0;
}
