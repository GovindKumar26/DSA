// LeetCode 827: Making A Large Island - HARD
// Problem: You are given an n x n binary matrix grid. You can change at most one 0 to 1.
// Return the size of the largest island in grid after applying this operation.

#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, size;
    
public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int node) {
        if(node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }
    
    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU == rootV) return;
        
        if(size[rootU] < size[rootV]) {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        } else {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }
    
    int getSize(int node) {
        return size[find(node)];
    }
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        DSU dsu(n * n);
        int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        // Step 1: Union all existing islands
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    int idx = i * n + j;
                    
                    // Check right and down neighbors only (to avoid double counting)
                    if(i + 1 < n && grid[i + 1][j] == 1) {
                        dsu.unite(idx, (i + 1) * n + j);
                    }
                    if(j + 1 < n && grid[i][j + 1] == 1) {
                        dsu.unite(idx, i * n + (j + 1));
                    }
                }
            }
        }
        
        // Step 2: Find current maximum island size
        int maxIsland = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    maxIsland = max(maxIsland, dsu.getSize(i * n + j));
                }
            }
        }
        
        // Step 3: Try flipping each 0 and calculate resulting island size
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 0) {
                    unordered_set<int> neighborRoots;
                    int newSize = 1;  // The flipped cell itself
                    
                    // Check all 4 neighbors
                    for(auto& dir : dirs) {
                        int ni = i + dir[0], nj = j + dir[1];
                        if(ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] == 1) {
                            int root = dsu.find(ni * n + nj);
                            neighborRoots.insert(root);
                        }
                    }
                    
                    // Sum sizes of unique neighboring islands
                    for(int root : neighborRoots) {
                        newSize += dsu.getSize(root);
                    }
                    
                    maxIsland = max(maxIsland, newSize);
                }
            }
        }
        
        return maxIsland;
    }
};

/*
═══════════════════════════════════════════════════════════════════
INTUITION:
═══════════════════════════════════════════════════════════════════
1. First, group all existing 1s into islands using DSU
2. For each 0, calculate what island size we'd get if we flip it:
   - Count 1 for the flipped cell
   - Add sizes of all unique neighboring islands
3. Use a set to avoid counting same island multiple times

EXAMPLE:
Grid: [[1,0],
       [0,1]]

Initial islands: {0} and {3} each size 1
Try flipping position (0,1):
  - Neighbors: 0 (size 1) and 3 (size 1)
  - New size: 1 + 1 + 1 = 3

COMPLEXITY:
Time: O(n²) - process each cell constant times
Space: O(n²) - DSU arrays

KEY INSIGHT:
Use a set to track unique neighboring islands. Without it, we might
count the same island multiple times if a 0 has multiple neighbors
from the same island.
═══════════════════════════════════════════════════════════════════
*/

int main() {
    Solution sol;
    
    vector<vector<int>> grid1 = {{1, 0}, {0, 1}};
    cout << "Test 1: " << sol.largestIsland(grid1) << endl;  // Expected: 3
    
    vector<vector<int>> grid2 = {{1, 1}, {1, 0}};
    cout << "Test 2: " << sol.largestIsland(grid2) << endl;  // Expected: 4
    
    vector<vector<int>> grid3 = {{1, 1}, {1, 1}};
    cout << "Test 3: " << sol.largestIsland(grid3) << endl;  // Expected: 4
    
    return 0;
}
