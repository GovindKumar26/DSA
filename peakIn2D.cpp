class Solution {
public:
    // Helper function to check if an element is a peak
    bool isPeakElement(vector<vector<int>>& mat, int row, int col) {
        int n = mat.size();
        int m = mat[0].size();
        int dxdy[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        
        for (int i = 0; i < 4; i++) {
            int newrow = row + dxdy[i][0];
            int newcol = col + dxdy[i][1];
            if (newrow >= 0 && newcol >= 0 && newrow < n && newcol < m && 
                mat[newrow][newcol] > mat[row][col]) {
                return false;
            }
        }
        return true;
    }

    // Approach 1: Binary Search on Columns - Optimal
    // Time: O(n * log m), Space: O(1)
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int low = 0, high = m - 1;
        
        while (low <= high) {
            int midCol = (low + high) >> 1;
            
            // Find the maximum element in the midCol
            int maxRow = 0;
            for (int row = 0; row < n; row++) {
                if (mat[row][midCol] > mat[maxRow][midCol]) {
                    maxRow = row;
                }
            }
            
            // Get neighboring elements
            int currElement = mat[maxRow][midCol];
            int leftElement = midCol == 0 ? -1 : mat[maxRow][midCol - 1];
            int rightElement = midCol == m - 1 ? -1 : mat[maxRow][midCol + 1];
            
            // Check if current element is a peak
            if (currElement > leftElement && currElement > rightElement) {
                return {maxRow, midCol};
            }
            // Move towards the larger neighbor
            else if (currElement < leftElement) {
                high = midCol - 1;
            }
            else {
                low = midCol + 1;
            }
        }
        
        return {-1, -1};
    }
    
    // Approach 2: Brute Force - Check every element
    // Time: O(n * m), Space: O(1)
    vector<int> findPeakGridBruteForce(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (isPeakElement(mat, i, j)) {
                    return {i, j};
                }
            }
        }
        
        return {-1, -1};
    }
};


// Problem: Find Peak Element II (Leetcode 1901)
// A peak element in a 2D grid is an element that is strictly greater than all of 
// its adjacent neighbors (left, right, top, bottom). Given an m×n matrix where 
// no two adjacent cells are equal, find any peak element and return its position [i,j].
//
// Example:
// mat = [[1,  4],
//        [3,  2]]
// Output: [0,1] (element 4 is greater than 1, 3, 2)
//
// Approach Comparison:
//
// 1. Binary Search on Columns - O(n × log m) ⭐ OPTIMAL
//    Algorithm:
//    - Binary search on column indices
//    - For each middle column, find the maximum element
//    - Check if it's greater than left and right neighbors
//    - If yes: it's a peak (max element in column is always greater than top/bottom)
//    - If left neighbor is larger: peak must be in left half
//    - If right neighbor is larger: peak must be in right half
//
//    Key Insight: The maximum element in any column only needs to check 
//    left and right (not top/bottom) because it's already the tallest in that column!
//
//    Why this works:
//    - Max element in column is greater than all elements above/below it
//    - We only need to check left/right neighbors
//    - Moving towards larger neighbor guarantees finding a peak
//
// 2. Brute Force - O(n × m)
//    - Check every element to see if it's greater than all 4 neighbors
//    - Simple but inefficient
//
// Time Complexity: O(n × log m)
// Space Complexity: O(1)
//
// Why Binary Search Works:
// - If current element < left neighbor → peak must exist in left half
// - If current element < right neighbor → peak must exist in right half
// - This is similar to 1D peak finding but we pick the max in each column
//   to ensure we're already handling the vertical dimension