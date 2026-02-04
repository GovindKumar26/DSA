// Minimum Path Sum in Grid (DP-10) - LC 64
// Problem: Find minimum sum path from top-left to bottom-right.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization
// TC: O(m*n), SC: O(m*n) + O(m+n) stack
int solve(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
    if (i == 0 && j == 0) return grid[0][0];
    if (i < 0 || j < 0) return INT_MAX;
    if (dp[i][j] != -1) return dp[i][j];
    
    int up = solve(i-1, j, grid, dp);
    int left = solve(i, j-1, grid, dp);
    
    return dp[i][j] = grid[i][j] + min(up, left);
}

int minPathSumMemo(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return solve(m-1, n-1, grid, dp);
}

// Approach 2: Space Optimized Tabulation
// TC: O(m*n), SC: O(n)
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    vector<int> prev(n, 0);
    
    for (int i = 0; i < m; i++) {
        vector<int> curr(n, 0);
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                curr[j] = grid[i][j];
            } else {
                int up = (i > 0) ? prev[j] : INT_MAX;
                int left = (j > 0) ? curr[j-1] : INT_MAX;
                curr[j] = grid[i][j] + min(up, left);
            }
        }
        prev = curr;
    }
    
    return prev[n-1];
}

int main() {
    vector<vector<int>> grid = {{1,3,1},{1,5,1},{4,2,1}};
    cout << "Minimum path sum: " << minPathSum(grid) << endl;
    return 0;
}

// Time Complexity: O(m*n)
// Space Complexity: O(n)