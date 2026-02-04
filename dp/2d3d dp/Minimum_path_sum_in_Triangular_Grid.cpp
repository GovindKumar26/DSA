// Minimum Path Sum in Triangular Grid (DP-11) - LC 120
// Problem: Find minimum sum path from top to bottom in triangular array.

#include <bits/stdc++.h>
using namespace std;

// Space Optimized Tabulation
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