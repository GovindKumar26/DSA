#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Time: O(m*n), Space: O(1) excluding result
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int m = matrix.size();
        int n = matrix[0].size();
        
        int top = 0, bottom = m - 1;
        int left = 0, right = n - 1;
        
        while (top <= bottom && left <= right) {
            // Traverse Right: top row, left to right
            for (int j = left; j <= right; j++) {
                result.push_back(matrix[top][j]);
            }
            top++;
            
            // Traverse Down: right column, top to bottom
            for (int i = top; i <= bottom; i++) {
                result.push_back(matrix[i][right]);
            }
            right--;
            
            // Traverse Left: bottom row, right to left
            if (top <= bottom) {  // Check if row still exists
                for (int j = right; j >= left; j--) {
                    result.push_back(matrix[bottom][j]);
                }
                bottom--;
            }
            
            // Traverse Up: left column, bottom to top
            if (left <= right) {  // Check if column still exists
                for (int i = bottom; i >= top; i--) {
                    result.push_back(matrix[i][left]);
                }
                left++;
            }
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "Matrix:" << endl;
    for (auto& row : matrix1) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    vector<int> res1 = sol.spiralOrder(matrix1);
    cout << "Spiral Order: [";
    for (int i = 0; i < res1.size(); i++) {
        cout << res1[i];
        if (i < res1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [1, 2, 3, 6, 9, 8, 7, 4, 5]
    
    cout << "\n------------------------\n" << endl;
    
    vector<vector<int>> matrix2 = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    cout << "Matrix:" << endl;
    for (auto& row : matrix2) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    vector<int> res2 = sol.spiralOrder(matrix2);
    cout << "Spiral Order: [";
    for (int i = 0; i < res2.size(); i++) {
        cout << res2[i];
        if (i < res2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]
    
    return 0;
}

/*
LeetCode 54 - Spiral Matrix

Problem: Print matrix elements in clockwise spiral order

Algorithm: Use 4 boundaries (top, bottom, left, right)

Visual for 3x3 matrix:
    left      right
      ↓         ↓
     [1, 2, 3] ← top
     [4, 5, 6]
     [7, 8, 9] ← bottom

Traversal order in each iteration:
1. → Right: top row (left to right), then top++
2. ↓ Down:  right column (top to bottom), then right--
3. ← Left:  bottom row (right to left), then bottom--
4. ↑ Up:    left column (bottom to top), then left++

Example: [[1,2,3],[4,5,6],[7,8,9]]

Iteration 1:
- Right: 1, 2, 3 (top=0, left=0→2), top becomes 1
- Down:  6, 9 (right=2, top=1→2), right becomes 1
- Left:  8, 7 (bottom=2, right=1→0), bottom becomes 1
- Up:    4 (left=0, bottom=1→1), left becomes 1

Iteration 2:
- Right: 5 (top=1, left=1→1), top becomes 2
- Now top > bottom, loop ends

Result: [1, 2, 3, 6, 9, 8, 7, 4, 5]

Why check conditions before Left and Up?
- For non-square matrices, we might have already processed all rows/columns
- Example: 1x4 matrix - after going right, no bottom row exists

Time Complexity: O(m * n) - each element visited once
Space Complexity: O(1) - excluding result array
*/
