#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Optimal: Use first row and first column as markers
    // Time: O(m*n), Space: O(1)
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        bool firstRowZero = false;
        bool firstColZero = false;
        
        // Check if first row has any zero
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }
        
        // Check if first column has any zero
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }
        
        // Use first row and column as markers for rest of matrix
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;  // Mark row
                    matrix[0][j] = 0;  // Mark column
                }
            }
        }
        
        // Set zeros based on markers (process from 1,1)
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        // Handle first row
        if (firstRowZero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }
        
        // Handle first column
        if (firstColZero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

int main() {
    Solution sol;
    
    vector<vector<int>> matrix1 = {{1,1,1},{1,0,1},{1,1,1}};
    cout << "Input:" << endl;
    for (auto& row : matrix1) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    sol.setZeroes(matrix1);
    cout << "Output:" << endl;
    for (auto& row : matrix1) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    
    cout << endl;
    
    vector<vector<int>> matrix2 = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    cout << "Input:" << endl;
    for (auto& row : matrix2) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    sol.setZeroes(matrix2);
    cout << "Output:" << endl;
    for (auto& row : matrix2) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    
    return 0;
}

/*
LeetCode 73 - Set Matrix Zeroes

Problem: If an element is 0, set its entire row and column to 0.

Approaches:
1. Brute Force: O(m*n) space - store positions of zeros
2. Better: O(m+n) space - use separate arrays for row/col markers
3. Optimal: O(1) space - use first row/column as markers

Optimal Algorithm:
1. Check if first row/column originally have zeros (save in flags)
2. Use first row & column as markers for rest of matrix
3. Fill zeros based on markers (starting from 1,1)
4. Finally handle first row and column using saved flags

Example: 
Input:          After marking:      After filling:
[1, 1, 1]       [1, 0, 1]          [1, 0, 1]
[1, 0, 1]  -->  [0, 0, 1]    -->   [0, 0, 0]
[1, 1, 1]       [1, 1, 1]          [1, 0, 1]

Why use separate flags for first row/col?
- First row and column are used as markers
- But they might originally contain zeros
- We need to know their original state before overwriting

Visual of markers:
         col markers (first row)
              ↓ ↓ ↓
            [1, 0, 1]  ← if matrix[0][1]=0, column 1 should be zero
row markers [0, 0, 1]  ← if matrix[1][0]=0, row 1 should be zero  
(first col) [1, 1, 1]

Time Complexity: O(m * n)
Space Complexity: O(1)
*/
