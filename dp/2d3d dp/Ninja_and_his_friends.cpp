// 3D DP: Ninja and his friends (DP-13)
// Problem: Two people start from (0,0) and (0,m-1), collect chocolates, find max sum.
// Both move down, left-diagonal, or right-diagonal.

#include <bits/stdc++.h>
using namespace std;

// Recursion with Memoization
// TC: O(n*m*m * 9), SC: O(n*m*m)
int solve(int i, int j1, int j2, int n, int m, vector<vector<int>>& grid, vector<vector<vector<int>>>& dp) {
    // Out of bounds
    if (j1 < 0 || j1 >= m || j2 < 0 || j2 >= m) return -1e8;
    
    // Base case: reached last row
    if (i == n-1) {
        if (j1 == j2) return grid[i][j1];
        else return grid[i][j1] + grid[i][j2];
    }
    
    if (dp[i][j1][j2] != -1) return dp[i][j1][j2];
    
    // Try all 9 combinations
    int maxi = -1e8;
    for (int dj1 = -1; dj1 <= 1; dj1++) {
        for (int dj2 = -1; dj2 <= 1; dj2++) {
            int value = 0;
            if (j1 == j2) value = grid[i][j1];
            else value = grid[i][j1] + grid[i][j2];
            
            value += solve(i+1, j1+dj1, j2+dj2, n, m, grid, dp);
            maxi = max(maxi, value);
        }
    }
    
    return dp[i][j1][j2] = maxi;
}

int maximumChocolates(int n, int m, vector<vector<int>>& grid) {
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
    return solve(0, 0, m-1, n, m, grid, dp);
}

int main() {
    vector<vector<int>> grid = {{2,3,1,2},{3,4,2,2},{5,6,3,5}};
    int n = grid.size(), m = grid[0].size();
    cout << "Maximum chocolates: " << maximumChocolates(n, m, grid) << endl;
    return 0;
}

// Time Complexity: O(n*m*m*9)
// Space Complexity: O(n*m*m)