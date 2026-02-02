// LeetCode 1319: Number of Operations to Make Network Connected - MEDIUM
// Problem: There are n computers numbered 0 to n-1. You can remove a cable and 
// use it to connect two computers. Return minimum operations to connect all computers,
// or -1 if impossible.

#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rank;
    int components;
    
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        components = n;
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
        
        if(rootU == rootV) return false;  // Already connected (redundant cable)
        
        components--;
        
        if(rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if(rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        
        return true;  // Successfully connected
    }
    
    int getComponents() {
        return components;
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        DSU dsu(n);
        int redundantCables = 0;
        
        // Process all connections
        for(auto& conn : connections) {
            if(!dsu.unite(conn[0], conn[1])) {
                redundantCables++;  // This cable is redundant
            }
        }
        
        int numComponents = dsu.getComponents();
        
        // To connect k components, we need k-1 cables
        int cablesNeeded = numComponents - 1;
        
        if(redundantCables >= cablesNeeded) {
            return cablesNeeded;
        }
        
        return -1;  // Not enough cables
    }
};

/*
═══════════════════════════════════════════════════════════════════
INTUITION:
═══════════════════════════════════════════════════════════════════
1. Each cable connects two computers (or is redundant if already connected)
2. Redundant cables can be reused
3. To connect k separate networks, we need exactly k-1 cables

EXAMPLE:
n = 4, connections = [[0,1],[0,2],[1,2]]
- Process [0,1]: connect them (1 cable used)
- Process [0,2]: connect them (1 cable used)  
- Process [1,2]: already connected! (1 redundant cable)
- Components: 2 (network {0,1,2} and isolated {3})
- Need 1 cable to connect them
- Have 1 redundant cable
- Answer: 1

ALGORITHM:
1. Use DSU to track connected components
2. Count redundant cables (cables connecting already-connected computers)
3. If we have k components, we need k-1 cables to connect all
4. Check if redundantCables >= cablesNeeded

COMPLEXITY:
Time: O(E·α(n)) where E = number of connections
Space: O(n)

KEY OBSERVATIONS:
- To connect n components into 1: need n-1 edges (spanning tree property)
- A cable is redundant if both ends already in same component
- Minimum cables needed = (number of components) - 1
═══════════════════════════════════════════════════════════════════
*/

int main() {
    Solution sol;
    
    // Test 1
    int n1 = 4;
    vector<vector<int>> conn1 = {{0,1},{0,2},{1,2}};
    cout << "Test 1: " << sol.makeConnected(n1, conn1) << endl;
    // Expected: 1
    
    // Test 2
    int n2 = 6;
    vector<vector<int>> conn2 = {{0,1},{0,2},{0,3},{1,2},{1,3}};
    cout << "Test 2: " << sol.makeConnected(n2, conn2) << endl;
    // Expected: 2
    
    // Test 3
    int n3 = 6;
    vector<vector<int>> conn3 = {{0,1},{0,2},{0,3},{1,2}};
    cout << "Test 3: " << sol.makeConnected(n3, conn3) << endl;
    // Expected: -1 (not enough cables)
    
    return 0;
}
