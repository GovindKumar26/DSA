// G-51: Number of Islands II - Online Queries - DSU
// LeetCode 305
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
    
    bool unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        
        if (ulp_u == ulp_v) return false;
        
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
        return true;  // Union happened
    }
};

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        DisjointSet ds(m * n);
        vector<bool> vis(m * n, false);
        vector<int> result;
        int count = 0;
        
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};
        
        for (auto& pos : positions) {
            int row = pos[0], col = pos[1];
            int node = row * n + col;
            
            // If already land, just add current count
            if (vis[node]) {
                result.push_back(count);
                continue;
            }
            
            // Make this cell land
            vis[node] = true;
            count++;
            
            // Try to union with 4 neighbors
            for (int i = 0; i < 4; i++) {
                int nr = row + dr[i];
                int nc = col + dc[i];
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int neighborNode = nr * n + nc;
                    if (vis[neighborNode]) {
                        if (ds.unionByRank(node, neighborNode)) {
                            count--;  // Merged two islands into one
                        }
                    }
                }
            }
            
            result.push_back(count);
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    // Example: m = 3, n = 3
    // positions = [[0,0], [0,1], [1,2], [2,1]]
    vector<vector<int>> positions = {{0, 0}, {0, 1}, {1, 2}, {2, 1}};
    
    vector<int> result = sol.numIslands2(3, 3, positions);
    
    cout << "Number of islands after each operation: ";
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;
    // Output: 1 1 2 3
    
    return 0;
}
