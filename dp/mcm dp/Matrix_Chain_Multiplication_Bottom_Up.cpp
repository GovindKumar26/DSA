// Matrix Chain Multiplication Bottom-Up (DP-49)
// Problem: Tabulation approach for MCM.

#include <bits/stdc++.h>
using namespace std;

// Tabulation
// TC: O(n^3), SC: O(n^2)
int matrixMultiplication(int n, vector<int>& arr) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // Fill the table
    for (int i = n-1; i >= 1; i--) {
        for (int j = i+1; j < n; j++) {
            int mini = INT_MAX;
            for (int k = i; k < j; k++) {
                int steps = arr[i-1] * arr[k] * arr[j] +
                           dp[i][k] + dp[k+1][j];
                mini = min(mini, steps);
            }
            dp[i][j] = mini;
        }
    }
    
    return dp[1][n-1];
}

int main() {
    vector<int> arr = {10, 20, 30, 40, 30};
    int n = arr.size();
    cout << "Minimum multiplications: " << matrixMultiplication(n, arr) << endl;
    return 0;
}

// Time Complexity: O(n^3)
// Space Complexity: O(n^2)