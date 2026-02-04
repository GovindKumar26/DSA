// Minimum Path Sum in Triangular Grid (DP-11) - LC 120
// Problem: Find minimum sum path from top to bottom in triangular array.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization
// TC: O(n^2), SC: O(n^2) + O(n) stack
int solve(int i, int j, vector<vector<int>>& triangle, vector<vector<int>>& dp) {
    int n = triangle.size();
    if (i == n-1) return triangle[i][j];
    if (dp[i][j] != -1) return dp[i][j];
    
    int down = solve(i+1, j, triangle, dp);
    int diagonal = solve(i+1, j+1, triangle, dp);
    
    return dp[i][j] = triangle[i][j] + min(down, diagonal);
}

int minimumTotalMemo(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solve(0, 0, triangle, dp);
}

// Approach 2: Space Optimized Tabulation
// TC: O(n^2), SC: O(n)
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> front(n, 0);
    
    // Initialize with last row
    for (int j = 0; j < n; j++) {
        front[j] = triangle[n-1][j];
    }
    
    // Bottom-up approach
    for (int i = n-2; i >= 0; i--) {
        vector<int> curr(n, 0);
        for (int j = i; j >= 0; j--) {
            int down = front[j];
            int diagonal = front[j+1];
            curr[j] = triangle[i][j] + min(down, diagonal);
        }
        front = curr;
    }
    
    return front[0];
}

int main() {
    vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};
    cout << "Minimum path sum: " << minimumTotal(triangle) << endl;
    return 0;
}

// Time Complexity: O(n^2)
// Space Complexity: O(n)