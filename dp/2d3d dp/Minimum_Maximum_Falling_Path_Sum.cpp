// Minimum/Maximum Falling Path Sum (DP-12) - LC 931
// Problem: Find minimum falling path sum. Can move to i+1, j-1, j, or j+1.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization
// TC: O(n*m), SC: O(n*m) + O(n) stack
int solveMemo(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    if (j < 0 || j >= m) return 1e8;
    if (i == 0) return matrix[0][j];
    if (dp[i][j] != -1) return dp[i][j];
    
    int up = solveMemo(i-1, j, matrix, dp);
    int leftDiag = solveMemo(i-1, j-1, matrix, dp);
    int rightDiag = solveMemo(i-1, j+1, matrix, dp);
    
    return dp[i][j] = matrix[i][j] + min({up, leftDiag, rightDiag});
}

int minFallingPathSumMemo(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    
    int mini = INT_MAX;
    for (int j = 0; j < m; j++) {
        mini = min(mini, solveMemo(n-1, j, matrix, dp));
    }
    return mini;
}

// Approach 2: Minimum Falling Path Sum (Tabulation)
// TC: O(n*m), SC: O(m)
int minFallingPathSum(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    vector<int> prev = matrix[0];
    
    for (int i = 1; i < n; i++) {
        vector<int> curr(m, 0);
        for (int j = 0; j < m; j++) {
            int up = prev[j];
            int leftDiag = (j > 0) ? prev[j-1] : INT_MAX;
            int rightDiag = (j < m-1) ? prev[j+1] : INT_MAX;
            
            curr[j] = matrix[i][j] + min({up, leftDiag, rightDiag});
        }
        prev = curr;
    }
    
    return *min_element(prev.begin(), prev.end());
}

// Maximum Falling Path Sum (similar approach)
int maxFallingPathSum(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    vector<int> prev = matrix[0];
    
    for (int i = 1; i < n; i++) {
        vector<int> curr(m, 0);
        for (int j = 0; j < m; j++) {
            int up = prev[j];
            int leftDiag = (j > 0) ? prev[j-1] : INT_MIN;
            int rightDiag = (j < m-1) ? prev[j+1] : INT_MIN;
            
            curr[j] = matrix[i][j] + max({up, leftDiag, rightDiag});
        }
        prev = curr;
    }
    
    return *max_element(prev.begin(), prev.end());
}

int main() {
    vector<vector<int>> matrix = {{2,1,3},{6,5,4},{7,8,9}};
    cout << "Minimum falling path sum: " << minFallingPathSum(matrix) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(m)