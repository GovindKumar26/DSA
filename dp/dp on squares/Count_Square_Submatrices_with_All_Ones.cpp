// Count Square Submatrices with All Ones (DP-56) - LC 1277
// Problem: Count all square submatrices with all ones.

#include <bits/stdc++.h>
using namespace std;

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