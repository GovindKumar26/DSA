class Solution {
public:
    // Helper function to count elements <= x in the matrix
    int countSmallerOrEqual(vector<vector<int>>& matrix, int x) {
        int count = 0;
        int n = matrix.size();
        int m = matrix[0].size();
        
        for (int i = 0; i < n; i++) {
            // Binary search in each row (since rows are sorted)
            int low = 0, high = m - 1;
            int pos = m; // Position where elements become > x
            
            while (low <= high) {
                int mid = (low + high) >> 1;
                if (matrix[i][mid] <= x) {
                    pos = mid + 1;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            count += pos;
        }
        
        return count;
    }
    
    // Approach 1: Binary Search on Answer Space - Optimal
    // Time: O(n * log m * log(max - min)), Space: O(1)
    int findMedian(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        // Find min and max elements in the matrix
        int low = INT_MAX, high = INT_MIN;
        for (int i = 0; i < n; i++) {
            low = min(low, matrix[i][0]);           // First element (smallest in row)
            high = max(high, matrix[i][m - 1]);     // Last element (largest in row)
        }
        
        int required = (n * m) / 2; // Median position (0-indexed count)
        
        // Binary search on the answer (value range)
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = countSmallerOrEqual(matrix, mid);
            
            // If count <= required, median must be larger
            if (count <= required) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        return low;
    }
    
    // Approach 2: Merge all rows and find median - Brute Force
    // Time: O(n * m * log(n * m)), Space: O(n * m)
    int findMedianBruteForce(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> arr;
        
        // Collect all elements
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                arr.push_back(matrix[i][j]);
            }
        }
        
        // Sort and find median
        sort(arr.begin(), arr.end());
        return arr[(n * m) / 2];
    }
    
    // Approach 3: Min-Heap (Similar to merge k sorted arrays)
    // Time: O(n * m * log n), Space: O(n)
    int findMedianMinHeap(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int medianPos = (n * m) / 2;
        
        // Min-heap: {value, row, col}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        
        // Initialize heap with first element of each row
        for (int i = 0; i < n; i++) {
            pq.push({matrix[i][0], i, 0});
        }
        
        int count = 0;
        int median = 0;
        
        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            
            int val = top[0];
            int row = top[1];
            int col = top[2];
            
            if (count == medianPos) {
                median = val;
                break;
            }
            count++;
            
            // Add next element from the same row
            if (col + 1 < m) {
                pq.push({matrix[row][col + 1], row, col + 1});
            }
        }
        
        return median;
    }
};

// Problem: Median in a Row-Wise Sorted Matrix
// Given an n×m matrix where each row is sorted in ascending order,
// find the median of the matrix. Assume n*m is always odd.
//
// Example:
// matrix = [[1,  3,  5],
//           [2,  6,  9],
//           [3,  6,  9]]
// Sorted: [1, 2, 3, 3, 5, 6, 6, 9, 9]
// Median: 5 (middle element at index 4)
//
// Approach Comparison:
//
// 1. Binary Search on Answer Space - O(n × log m × log(max - min)) ⭐ OPTIMAL
//    Key Insight: The median has exactly (n*m)/2 elements smaller than it
//    
//    Algorithm:
//    - Binary search on the value range [min_element, max_element]
//    - For each mid value, count how many elements are <= mid
//    - If count <= (n*m)/2: median must be larger → search right
//    - If count > (n*m)/2: median might be smaller → search left
//    - The answer is the smallest value with count > (n*m)/2
//    
//    Why it works:
//    - Median is the smallest number with more than half elements ≤ it
//    - We don't need the actual sorted array, just counts
//    - Each row is sorted, so we can binary search in each row
//    
//    Time breakdown:
//    - Outer binary search: O(log(max - min)) ≈ O(log(10^9)) ≈ 32 iterations
//    - For each iteration: count elements in n rows × O(log m) = O(n × log m)
//    - Total: O(32 × n × log m) = O(n × log m)
//
// 2. Brute Force - O(n × m × log(n × m))
//    - Collect all elements into array
//    - Sort the array
//    - Return middle element
//    - Space: O(n × m)
//
// 3. Min-Heap (Merge k sorted lists) - O(n × m × log n)
//    - Use min-heap to merge n sorted rows
//    - Extract (n×m)/2 + 1 elements
//    - Last extracted is the median
//    - Space: O(n) for heap
//
// The binary search approach is optimal because:
// - No extra space needed for storing all elements
// - Leverages the sorted property of rows
// - Value range is fixed (10^9), so log iterations are constant
// - Much faster than sorting all elements for large matrices
//
// Example walkthrough:
// matrix = [[1, 3, 5], [2, 6, 9], [3, 6, 9]]
// min = 1, max = 9, required = 4 (need 5 elements, 0-indexed)
// 
// mid = 5: count = 5 (1,2,3,3,5) > 4 → median ≤ 5, high = 4
// mid = 2: count = 2 (1,2) ≤ 4 → median > 2, low = 3
// mid = 3: count = 4 (1,2,3,3) ≤ 4 → median > 3, low = 4
// mid = 4: count = 4 (1,2,3,3) ≤ 4 → median > 4, low = 5
// Answer: 5
