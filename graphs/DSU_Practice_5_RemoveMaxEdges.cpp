// LeetCode 1579: Remove Max Number of Edges to Keep Graph Fully Traversable - HARD
// Problem: Alice and Bob have an undirected graph with n nodes. There are three types
// of edges: Type 1 (Alice only), Type 2 (Bob only), Type 3 (both can use).
// Return maximum number of edges you can remove so that graph remains fully traversable
// for both Alice and Bob, or -1 if impossible.

#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rank;
    int components;
    
public:
    DSU(int n) {
        parent.resize(n + 1);  // 1-indexed
        rank.resize(n + 1, 0);
        components = n;
        for(int i = 1; i <= n; i++) {
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
        
        if(rootU == rootV) return false;  // Already connected (redundant edge)
        
        components--;
        
        if(rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if(rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        
        return true;  // Edge was necessary
    }
    
    bool isConnected() {
        return components == 1;
    }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        DSU alice(n), bob(n);
        int edgesUsed = 0;
        
        // Step 1: Process Type 3 edges first (most valuable - helps both)
        for(auto& edge : edges) {
            if(edge[0] == 3) {
                int u = edge[1], v = edge[2];
                
                // Try to add to both Alice and Bob
                bool aliceAdded = alice.unite(u, v);
                bool bobAdded = bob.unite(u, v);
                
                // Edge is useful if it helps at least one of them
                if(aliceAdded || bobAdded) {
                    edgesUsed++;
                }
            }
        }
        
        // Step 2: Process Type 1 edges (Alice only)
        for(auto& edge : edges) {
            if(edge[0] == 1) {
                int u = edge[1], v = edge[2];
                if(alice.unite(u, v)) {
                    edgesUsed++;
                }
            }
        }
        
        // Step 3: Process Type 2 edges (Bob only)
        for(auto& edge : edges) {
            if(edge[0] == 2) {
                int u = edge[1], v = edge[2];
                if(bob.unite(u, v)) {
                    edgesUsed++;
                }
            }
        }
        
        // Check if both graphs are fully connected
        if(!alice.isConnected() || !bob.isConnected()) {
            return -1;
        }
        
        // Maximum edges we can remove = total - used
        return edges.size() - edgesUsed;
    }
};

/*
═══════════════════════════════════════════════════════════════════
INTUITION:
═══════════════════════════════════════════════════════════════════
Goal: Keep minimum edges so both Alice and Bob can traverse entire graph.

Key insight: Type 3 edges are most valuable (help both people).
Process them first to maximize their impact.

STRATEGY:
1. Process Type 3 edges first - they help both Alice and Bob
2. Then process Type 1 edges - help only Alice
3. Then process Type 2 edges - help only Bob
4. Count how many edges we actually needed (not redundant)
5. Return: total edges - edges needed

EXAMPLE:
n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]

Type 3 edges: [3,1,2], [3,2,3]
  - Both connect new components for Alice and Bob
  - Used: 2 edges

Type 1 edges: [1,1,3], [1,2,4], [1,1,2]
  - [1,1,3]: connects 1-3 for Alice (used)
  - [1,2,4]: connects 2-4 for Alice (used)
  - [1,1,2]: 1-2 already connected for Alice (redundant)
  - Used: 2 more edges

Type 2 edges: [2,3,4]
  - Connects 3-4 for Bob (used)
  - Used: 1 more edge

Total used: 5 edges
Can remove: 6 - 5 = 1 edge

WHY PROCESS TYPE 3 FIRST?
- Type 3 edges help both people simultaneously
- By processing them first, we maximize dual benefit
- Then we only add type 1/2 edges if still needed

COMPLEXITY:
Time: O(E·α(n)) where E = number of edges
Space: O(n) for two DSU structures

EDGE CASES:
- If either person can't reach all nodes: return -1
- All edges are type 3 and redundant: return count of redundant
- No type 3 edges: process type 1 and 2 independently
═══════════════════════════════════════════════════════════════════
*/

int main() {
    Solution sol;
    
    // Test 1
    int n1 = 4;
    vector<vector<int>> edges1 = {{3,1,2},{3,2,3},{1,1,3},{1,2,4},{1,1,2},{2,3,4}};
    cout << "Test 1: " << sol.maxNumEdgesToRemove(n1, edges1) << endl;
    // Expected: 2
    
    // Test 2
    int n2 = 4;
    vector<vector<int>> edges2 = {{3,1,2},{3,2,3},{1,1,4},{2,1,4}};
    cout << "Test 2: " << sol.maxNumEdgesToRemove(n2, edges2) << endl;
    // Expected: 0 (all edges needed)
    
    // Test 3
    int n3 = 4;
    vector<vector<int>> edges3 = {{3,2,3},{1,1,2},{2,3,4}};
    cout << "Test 3: " << sol.maxNumEdgesToRemove(n3, edges3) << endl;
    // Expected: -1 (can't fully connect)
    
    return 0;
}
