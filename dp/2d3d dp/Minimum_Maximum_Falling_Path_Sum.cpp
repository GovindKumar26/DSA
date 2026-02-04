// Minimum/Maximum Falling Path Sum (DP-12) - LC 931
// Problem: Find minimum falling path sum. Can move to i+1, j-1, j, or j+1.

#include <bits/stdc++.h>
using namespace std;

// Minimum Falling Path Sum
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