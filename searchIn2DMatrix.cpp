class Solution {
public:
    // Approach 1: Binary Search (Treat as 1D array) - Optimal
    // Time: O(log(m * n)), Space: O(1)
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        int low = 0, high = m * n - 1;
        
        while (low <= high) {
            int mid = (low + high) >> 1;
            int row = mid / n;
            int col = mid % n;
            int midVal = matrix[row][col];
            
            if (midVal == target) {
                return true;
            } else if (midVal < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        return false;
    }
    
    // Approach 2: Two Binary Searches
    // Time: O(log m + log n), Space: O(1)
    bool searchMatrixTwoBinarySearches(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        // First binary search: Find the row
        int rowLow = 0, rowHigh = m - 1;
        int targetRow = -1;
        
        while (rowLow <= rowHigh) {
            int mid = (rowLow + rowHigh) >> 1;
            if (matrix[mid][0] <= target && target <= matrix[mid][n - 1]) {
                targetRow = mid;
                break;
            } else if (matrix[mid][0] > target) {
                rowHigh = mid - 1;
            } else {
                rowLow = mid + 1;
            }
        }
        
        if (targetRow == -1) return false;
        
        // Second binary search: Find in the row
        int colLow = 0, colHigh = n - 1;
        while (colLow <= colHigh) {
            int mid = (colLow + colHigh) >> 1;
            if (matrix[targetRow][mid] == target) {
                return true;
            } else if (matrix[targetRow][mid] < target) {
                colLow = mid + 1;
            } else {
                colHigh = mid - 1;
            }
        }
        
        return false;
    }
    
    // Approach 3: Brute Force
    // Time: O(m * n), Space: O(1)
    bool searchMatrixBruteForce(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == target) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

// Problem: Search in a 2D Matrix I
// Given an m x n matrix with the following properties:
// 1. Each row is sorted in ascending order
// 2. The first integer of each row is greater than the last integer of the previous row
// Return true if target exists in the matrix, false otherwise.
//
// Example:
// matrix = [[1,  3,  5,  7],
//           [10, 11, 16, 20],
//           [23, 30, 34, 60]]
// target = 3 → true
// target = 13 → false
//
// Key Insight: The matrix can be viewed as a sorted 1D array!
// [1, 3, 5, 7, 10, 11, 16, 20, 23, 30, 34, 60]
//
// Approach Comparison:
//
// 1. Binary Search on Virtual 1D Array (BEST):
//    - Treat m×n matrix as a sorted array of size m*n
//    - Convert index: row = mid / n, col = mid % n
//    - Time: O(log(m * n)), Space: O(1)
//    - Most elegant and efficient
//
// 2. Two Binary Searches:
//    - First: Find which row might contain target
//    - Second: Binary search within that row
//    - Time: O(log m + log n), Space: O(1)
//    - Note: log m + log n ≈ log(m * n), so similar to approach 1
//
// 3. Brute Force:
//    - Linear scan through all elements
//    - Time: O(m * n), Space: O(1)
//    - Simple but inefficient
//
// Index Conversion Formula:
// - 1D index to 2D: row = index / cols, col = index % cols
// - 2D index to 1D: index = row * cols + col
//
// Example: m=3, n=4 (12 elements)
// mid = 5 → row = 5/4 = 1, col = 5%4 = 1 → matrix[1][1]
// matrix[1][1] → index = 1*4 + 1 = 5
