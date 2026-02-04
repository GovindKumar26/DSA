// Grid Unique Paths (DP-8) - LC 62
// Problem: Find number of unique paths from top-left to bottom-right in m×n grid.
// Can only move right or down.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Recursion with Memoization
// TC: O(m*n), SC: O(m*n) + O(m+n) stack space
int solve(int i, int j, vector<vector<int>>& dp) {
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    
    int up = solve(i-1, j, dp);
    int left = solve(i, j-1, dp);
    
    return dp[i][j] = up + left;
}

int uniquePathsMemo(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return solve(m-1, n-1, dp);
}

// Approach 2: Tabulation
// TC: O(m*n), SC: O(m*n)
int uniquePathsTabulation(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
            } else {
                int up = (i > 0) ? dp[i-1][j] : 0;
                int left = (j > 0) ? dp[i][j-1] : 0;
                dp[i][j] = up + left;
            }
        }
    }
    
    return dp[m-1][n-1];
}

// Approach 3: Space Optimized
// TC: O(m*n), SC: O(n)
int uniquePathsOptimized(int m, int n) {
    vector<int> prev(n, 0);
    
    for (int i = 0; i < m; i++) {
        vector<int> curr(n, 0);
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                curr[j] = 1;
            } else {
                int up = (i > 0) ? prev[j] : 0;
                int left = (j > 0) ? curr[j-1] : 0;
                curr[j] = up + left;
            }
        }
        prev = curr;
    }
    
    return prev[n-1];
}

int main() {
    int m = 3, n = 7;
    cout << "Unique paths in " << m << "x" << n << " grid: " << uniquePathsOptimized(m, n) << endl;
    return 0;
}

// Time Complexity: O(m*n)
// Space Complexity: O(n) for optimized