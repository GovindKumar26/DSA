#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Rotate 90 degrees clockwise (in-place)
    // Time: O(n²), Space: O(1)
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // Step 1: Transpose the matrix (swap rows and columns)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {  // j starts from i+1 to avoid double swap
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        // Step 2: Reverse each row
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
    
    // Rotate 90 degrees counter-clockwise (in-place)
    void rotateCounterClockwise(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // Step 1: Transpose the matrix
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        // Step 2: Reverse each column
        for (int j = 0; j < n; j++) {
            int top = 0, bottom = n - 1;
            while (top < bottom) {
                swap(matrix[top][j], matrix[bottom][j]);
                top++;
                bottom--;
            }
        }
    }
};

void printMatrix(vector<vector<int>>& matrix) {
    for (auto& row : matrix) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
}

int main() {
    Solution sol;
    
    vector<vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "Original:" << endl;
    printMatrix(matrix1);
    
    sol.rotate(matrix1);
    cout << "\nAfter 90° clockwise rotation:" << endl;
    printMatrix(matrix1);
    
    cout << "\n------------------------\n" << endl;
    
    vector<vector<int>> matrix2 = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "Original:" << endl;
    printMatrix(matrix2);
    
    sol.rotateCounterClockwise(matrix2);
    cout << "\nAfter 90° counter-clockwise rotation:" << endl;
    printMatrix(matrix2);
    
    return 0;
}

/*
LeetCode 48 - Rotate Image

Problem: Rotate an n x n matrix by 90 degrees clockwise (in-place)

90° Clockwise Rotation = Transpose + Reverse each row

Example:
Original:       Transpose:       Reverse rows:
[1, 2, 3]       [1, 4, 7]        [7, 4, 1]
[4, 5, 6]  -->  [2, 5, 8]  -->   [8, 5, 2]
[7, 8, 9]       [3, 6, 9]        [9, 6, 3]

Transpose: swap matrix[i][j] with matrix[j][i]
  - Only swap upper triangle (j > i) to avoid double swapping

Why it works:
- Transpose: rows become columns
- Reverse rows: puts elements in correct clockwise position

For 90° Counter-clockwise:
- Transpose + Reverse each column
  OR
- Reverse each row + Transpose

For 180° rotation:
- Reverse each row, then reverse each column
  OR
- Rotate 90° twice

Time Complexity: O(n²)
Space Complexity: O(1) - in-place
*/
