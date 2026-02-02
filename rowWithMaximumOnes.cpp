class Solution {
public:
    // Approach 1: Binary Search - Optimal for sorted rows
    // Time: O(n * log m), Space: O(1)
    int rowWithMax1s(vector<vector<int>>& arr) {
        int n = arr.size();
        int m = arr[0].size();
        int maxCount = 0;
        int maxRowIndex = -1;
        
        for (int i = 0; i < n; i++) {
            // Binary search to find first occurrence of 1
            int low = 0, high = m - 1;
            int firstOne = m; // If no 1 found, firstOne = m (count = 0)
            
            while (low <= high) {
                int mid = (low + high) >> 1;
                if (arr[i][mid] == 1) {
                    firstOne = mid;
                    high = mid - 1; // Look for earlier 1
                } else {
                    low = mid + 1;
                }
            }
            
            int count = m - firstOne; // Number of 1s
            if (count > maxCount) {
                maxCount = count;
                maxRowIndex = i;
            }
        }
        
        return maxRowIndex;
    }
    
    // Approach 2: Optimized traversal - Better when rows are sorted
    // Time: O(n + m), Space: O(1)
    int rowWithMax1sOptimized(vector<vector<int>>& arr) {
        int n = arr.size();
        int m = arr[0].size();
        int maxRowIndex = -1;
        int j = m - 1; // Start from top-right corner
        
        for (int i = 0; i < n; i++) {
            // Move left while we see 1s
            while (j >= 0 && arr[i][j] == 1) {
                j--;
                maxRowIndex = i; // Update the row with more 1s
            }
        }
        
        return maxRowIndex;
    }
    
    // Approach 3: Brute Force - Count 1s in each row
    // Time: O(n * m), Space: O(1)
    int rowWithMax1sBruteForce(vector<vector<int>>& arr) {
        int n = arr.size();
        int m = arr[0].size();
        int maxCount = 0;
        int maxRowIndex = -1;
        
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < m; j++) {
                count += arr[i][j];
            }
            if (count > maxCount) {
                maxCount = count;
                maxRowIndex = i;
            }
        }
        
        return maxRowIndex;
    }
};

// Problem: Given a 2D binary matrix where each row is sorted (0s followed by 1s),
// find the index of the row with the maximum number of 1s.
// Return -1 if no row contains any 1.
//
// Example:
// arr = [[0, 0, 0, 1],
//        [0, 1, 1, 1],
//        [1, 1, 1, 1],
//        [0, 0, 1, 1]]
// Output: 2 (row index 2 has four 1s)
//
// Approach Comparison:
//
// 1. Binary Search (rowWithMax1s):
//    - For each row, binary search to find first 1
//    - Count = m - firstOneIndex
//    - Time: O(n * log m), Space: O(1)
//    - Good when m is large
//
// 2. Optimized Traversal (rowWithMax1sOptimized):
//    - Start from top-right corner
//    - Move left when we see 1 (and update maxRowIndex)
//    - Move down when we see 0
//    - Time: O(n + m), Space: O(1)
//    - BEST approach when rows are sorted
//    - Key insight: If row i has more 1s than previous best,
//      we must move left, so we never revisit columns
//
// 3. Brute Force (rowWithMax1sBruteForce):
//    - Count all 1s in each row
//    - Time: O(n * m), Space: O(1)
//    - Works even if rows are not sorted
//
// The optimized traversal is the most efficient for sorted rows because:
// - Each element is visited at most once
// - We leverage the sorted property to skip elements
// - Total movements: at most n down + m left = O(n + m)
