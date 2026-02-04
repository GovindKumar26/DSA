// Count Square Submatrices with All Ones (DP-56) - LC 1277
// Problem: Count all square submatrices with all ones.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization
// TC: O(n*m), SC: O(n*m) + O(n+m) stack
int solveMemo(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
    if (i < 0 || j < 0 || matrix[i][j] == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    
    int up = solveMemo(i-1, j, matrix, dp);
    int left = solveMemo(i, j-1, matrix, dp);
    int diag = solveMemo(i-1, j-1, matrix, dp);
    
    return dp[i][j] = 1 + min({up, left, diag});
}

int countSquaresMemo(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 1) {
                count += solveMemo(i, j, matrix, dp);
            }
        }
    }
    
    return count;
}

// Approach 2: Tabulation
// TC: O(n*m), SC: O(n*m)
int countSquares(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 1) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                }
                count += dp[i][j];
            }
        }
    }
    
    return count;
}

int main() {
    vector<vector<int>> matrix = {
        {0,1,1,1},
        {1,1,1,1},
        {0,1,1,1}
    };
    cout << "Count of square submatrices: " << countSquares(matrix) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(n*m)