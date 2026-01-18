// G-49: Number of Operations to Make Network Connected
// LeetCode 1319
#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        // Need at least n-1 edges to connect n nodes
        if (connections.size() < n - 1) return -1;
        
        DisjointSet ds(n);
        int extraEdges = 0;
        
        for (auto& edge : connections) {
            int u = edge[0], v = edge[1];
            // If already connected, this is an extra edge
            if (ds.findUPar(u) == ds.findUPar(v)) {
                extraEdges++;
            } else {
                ds.unionByRank(u, v);
            }
        }
        
        // Count number of connected components
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (ds.findUPar(i) == i) {
                components++;
            }
        }
        
        // Need (components - 1) edges to connect all components
        int neededEdges = components - 1;
        
        if (extraEdges >= neededEdges) {
            return neededEdges;
        }
        return -1;
    }
};

int main() {
    Solution sol;
    
    // Example 1: n = 4, connections = [[0,1],[0,2],[1,2]]
    vector<vector<int>> connections1 = {{0, 1}, {0, 2}, {1, 2}};
    cout << "Example 1: " << sol.makeConnected(4, connections1) << endl; // Output: 1
    
    // Example 2: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
    vector<vector<int>> connections2 = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}};
    cout << "Example 2: " << sol.makeConnected(6, connections2) << endl; // Output: 2
    
    // Example 3: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
    vector<vector<int>> connections3 = {{0, 1}, {0, 2}, {0, 3}, {1, 2}};
    cout << "Example 3: " << sol.makeConnected(6, connections3) << endl; // Output: -1
    
    return 0;
}
