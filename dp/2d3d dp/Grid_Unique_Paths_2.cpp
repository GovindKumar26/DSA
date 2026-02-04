// Grid Unique Paths 2 (DP-9) - LC 63
// Problem: Grid with obstacles. Find unique paths from top-left to bottom-right.
// 1 = obstacle, 0 = free cell

#include <bits/stdc++.h>
using namespace std;

// Tabulation with Space Optimization
// TC: O(m*n), SC: O(n)
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    
    if (obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) return 0;
    
    vector<int> prev(n, 0);
    
    for (int i = 0; i < m; i++) {
        vector<int> curr(n, 0);
        for (int j = 0; j < n; j++) {
            if (obstacleGrid[i][j] == 1) {
                curr[j] = 0;
            } else if (i == 0 && j == 0) {
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
    vector<vector<int>> obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}};
    cout << "Unique paths with obstacles: " << uniquePathsWithObstacles(obstacleGrid) << endl;
    return 0;
}

// Time Complexity: O(m*n)
// Space Complexity: O(n)