// G-53: Most Stones Removed with Same Row or Column - DSU
// LeetCode 947
#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
    unordered_map<int, int> parent, rank;
    int components = 0;
    
    int findUPar(int node) {
        if (parent.find(node) == parent.end()) {
            parent[node] = node;
            rank[node] = 0;
            components++;
        }
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        
        if (ulp_u == ulp_v) return;
        
        components--;  // Merging two components
        
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
    
    int getComponents() {
        return components;
    }
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        DisjointSet ds;
        int n = stones.size();
        
        // For each stone, union its row and column
        // To differentiate rows from columns, offset columns by a large number
        int maxCoord = 10001;  // Since coordinates can be 0 to 10^4
        
        for (auto& stone : stones) {
            int row = stone[0];
            int col = stone[1] + maxCoord;  // Offset column to avoid collision
            ds.unionByRank(row, col);
        }
        
        // Answer = total stones - number of connected components
        // In each component with k stones, we can remove k-1 stones
        return n - ds.getComponents();
    }
};

// Alternative approach: Map each stone to a node
class Solution2 {
public:
    vector<int> parent, rank;
    
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
    
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
        
        // Group by row and column
        unordered_map<int, vector<int>> rowMap, colMap;
        for (int i = 0; i < n; i++) {
            rowMap[stones[i][0]].push_back(i);
            colMap[stones[i][1]].push_back(i);
        }
        
        // Union stones in same row
        for (auto& [row, indices] : rowMap) {
            for (int i = 1; i < indices.size(); i++) {
                unionByRank(indices[0], indices[i]);
            }
        }
        
        // Union stones in same column
        for (auto& [col, indices] : colMap) {
            for (int i = 1; i < indices.size(); i++) {
                unionByRank(indices[0], indices[i]);
            }
        }
        
        // Count connected components
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (findUPar(i) == i) components++;
        }
        
        return n - components;
    }
};

int main() {
    Solution sol;
    
    // Example 1
    vector<vector<int>> stones1 = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    cout << "Example 1: " << sol.removeStones(stones1) << endl;  // Output: 5
    
    // Example 2
    vector<vector<int>> stones2 = {{0,0},{0,2},{1,1},{2,0},{2,2}};
    cout << "Example 2: " << sol.removeStones(stones2) << endl;  // Output: 3
    
    // Example 3
    vector<vector<int>> stones3 = {{0,0}};
    cout << "Example 3: " << sol.removeStones(stones3) << endl;  // Output: 0
    
    return 0;
}
