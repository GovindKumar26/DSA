// Matrix Chain Multiplication (DP-48)
// Problem: Find minimum multiplications to multiply chain of matrices.

#include <bits/stdc++.h>
using namespace std;

// Memoization
// TC: O(n^3), SC: O(n^2) + O(n) stack
int solve(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
    if (i == j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    
    int mini = INT_MAX;
    for (int k = i; k < j; k++) {
        int steps = arr[i-1] * arr[k] * arr[j] +
                    solve(i, k, arr, dp) +
                    solve(k+1, j, arr, dp);
        mini = min(mini, steps);
    }
    
    return dp[i][j] = mini;
}

int matrixMultiplication(int n, vector<int>& arr) {
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solve(1, n-1, arr, dp);
}

int main() {
    vector<int> arr = {10, 20, 30, 40, 30};
    int n = arr.size();
    cout << "Minimum multiplications: " << matrixMultiplication(n, arr) << endl;
    return 0;
}

// Time Complexity: O(n^3)
// Space Complexity: O(n^2)