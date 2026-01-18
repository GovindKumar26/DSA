// G-52: Making a Large Island - DSU
// LeetCode 827
#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
    vector<int> parent, size;
    
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
    
    int getSize(int node) {
        return size[findUPar(node)];
    }
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        DisjointSet ds(n * n);
        
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};
        
        // Step 1: Connect all existing islands
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (grid[row][col] == 0) continue;
                
                int node = row * n + col;
                for (int i = 0; i < 4; i++) {
                    int nr = row + dr[i];
                    int nc = col + dc[i];
                    
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        int neighborNode = nr * n + nc;
                        ds.unionBySize(node, neighborNode);
                    }
                }
            }
        }
        
        // Step 2: Try converting each 0 to 1 and find max island
        int maxSize = 0;
        
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (grid[row][col] == 1) {
                    // Update max for existing islands
                    maxSize = max(maxSize, ds.getSize(row * n + col));
                    continue;
                }
                
                // Try converting this 0 to 1
                set<int> uniqueParents;
                for (int i = 0; i < 4; i++) {
                    int nr = row + dr[i];
                    int nc = col + dc[i];
                    
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        uniqueParents.insert(ds.findUPar(nr * n + nc));
                    }
                }
                
                int totalSize = 1;  // The cell we're converting
                for (int parent : uniqueParents) {
                    totalSize += ds.getSize(parent);
                }
                maxSize = max(maxSize, totalSize);
            }
        }
        
        return maxSize;
    }
};

int main() {
    Solution sol;
    
    // Example 1
    vector<vector<int>> grid1 = {{1, 0}, {0, 1}};
    cout << "Example 1: " << sol.largestIsland(grid1) << endl;  // Output: 3
    
    // Example 2
    vector<vector<int>> grid2 = {{1, 1}, {1, 0}};
    cout << "Example 2: " << sol.largestIsland(grid2) << endl;  // Output: 4
    
    // Example 3
    vector<vector<int>> grid3 = {{1, 1}, {1, 1}};
    cout << "Example 3: " << sol.largestIsland(grid3) << endl;  // Output: 4
    
    return 0;
}
