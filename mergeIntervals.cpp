#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Approach 1: Single pass with last interval check
    // Time: O(n log n), Space: O(1) excluding result
    vector<vector<int>> mergeOverlap(vector<vector<int>>& arr) {
        int n = arr.size();
        if (n <= 1) return arr;
        
        // Sort intervals by start time
        sort(arr.begin(), arr.end());
        
        vector<vector<int>> result;
        result.push_back(arr[0]);
        
        for (int i = 1; i < n; i++) {
            vector<int>& lastInterval = result.back();
            vector<int>& currentInterval = arr[i];
            
            // Check if current interval overlaps with last merged interval
            if (currentInterval[0] <= lastInterval[1]) {
                // Merge: extend the end time to maximum of both
                lastInterval[1] = max(lastInterval[1], currentInterval[1]);
            } else {
                // No overlap, add current interval as new
                result.push_back(currentInterval);
            }
        }
        
        return result;
    }
    
    // Approach 2: Look-ahead merging approach
    // Time: O(n log n) - Each interval is examined at most twice across all iterations
    // The continue statement skips already-merged intervals, making the merging pass O(n)
    // Space: O(1) excluding result
    vector<vector<int>> mergeOverlapLookAhead(vector<vector<int>>& arr) {
        int n = arr.size();
        if (n <= 1) return arr;
        
        // Sort intervals by start time
        sort(arr.begin(), arr.end());
        
        vector<vector<int>> ans;
        
        for (int i = 0; i < n; i++) {
            int start = arr[i][0];
            int end = arr[i][1];
            
            // Skip if current interval is already covered by last merged interval
            if (!ans.empty() && end <= ans.back()[1]) {
                continue;
            }
            
            // Look ahead and merge all overlapping intervals
            for (int j = i + 1; j < n; j++) {
                if (arr[j][0] <= end) {
                    end = max(end, arr[j][1]);
                } else {
                    break;
                }
            }
            
            ans.push_back({start, end});
        }
        
        return ans;
    }
};

int main() {
    Solution sol;
    
    cout << "===== Approach 1: Single Pass =====\n" << endl;
    
    // Test case 1
    vector<vector<int>> intervals1 = {{1, 5}, {3, 6}, {8, 10}, {15, 18}};
    cout << "Test 1: [[1,5],[3,6],[8,10],[15,18]]" << endl;
    vector<vector<int>> result1 = sol.mergeOverlap(intervals1);
    cout << "Output: [";
    for (int i = 0; i < result1.size(); i++) {
        cout << "[" << result1[i][0] << "," << result1[i][1] << "]";
        if (i < result1.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "Expected: [[1,6],[8,10],[15,18]]" << endl << endl;
    
    // Test case 2
    vector<vector<int>> intervals2 = {{1, 4}, {4, 5}};
    cout << "Test 2: [[1,4],[4,5]]" << endl;
    vector<vector<int>> result2 = sol.mergeOverlap(intervals2);
    cout << "Output: [";
    for (int i = 0; i < result2.size(); i++) {
        cout << "[" << result2[i][0] << "," << result2[i][1] << "]";
        if (i < result2.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "Expected: [[1,5]]" << endl << endl;
    
    // Test case 3
    vector<vector<int>> intervals3 = {{1, 4}, {0, 4}};
    cout << "Test 3: [[1,4],[0,4]]" << endl;
    vector<vector<int>> result3 = sol.mergeOverlap(intervals3);
    cout << "Output: [";
    for (int i = 0; i < result3.size(); i++) {
        cout << "[" << result3[i][0] << "," << result3[i][1] << "]";
        if (i < result3.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "Expected: [[0,4]]" << endl << endl;
    
    // Test case 4
    vector<vector<int>> intervals4 = {{1, 4}, {2, 3}};
    cout << "Test 4: [[1,4],[2,3]]" << endl;
    vector<vector<int>> result4 = sol.mergeOverlap(intervals4);
    cout << "Output: [";
    for (int i = 0; i < result4.size(); i++) {
        cout << "[" << result4[i][0] << "," << result4[i][1] << "]";
        if (i < result4.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "Expected: [[1,4]]" << endl << endl;
    
    // Test case 5
    vector<vector<int>> intervals5 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    cout << "Test 5: [[1,3],[2,6],[8,10],[15,18]]" << endl;
    vector<vector<int>> result5 = sol.mergeOverlap(intervals5);
    cout << "Output: [";
    for (int i = 0; i < result5.size(); i++) {
        cout << "[" << result5[i][0] << "," << result5[i][1] << "]";
        if (i < result5.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "Expected: [[1,6],[8,10],[15,18]]" << endl << endl;
    
    cout << "\n===== Approach 2: Look-Ahead Merging =====\n" << endl;
    
    // Test case 1
    vector<vector<int>> intervals6 = {{1, 5}, {3, 6}, {8, 10}, {15, 18}};
    cout << "Test 1: [[1,5],[3,6],[8,10],[15,18]]" << endl;
    vector<vector<int>> result6 = sol.mergeOverlapLookAhead(intervals6);
    cout << "Output: [";
    for (int i = 0; i < result6.size(); i++) {
        cout << "[" << result6[i][0] << "," << result6[i][1] << "]";
        if (i < result6.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "Expected: [[1,6],[8,10],[15,18]]" << endl << endl;
    
    // Test case 2
    vector<vector<int>> intervals7 = {{1, 4}, {2, 3}};
    cout << "Test 2: [[1,4],[2,3]]" << endl;
    vector<vector<int>> result7 = sol.mergeOverlapLookAhead(intervals7);
    cout << "Output: [";
    for (int i = 0; i < result7.size(); i++) {
        cout << "[" << result7[i][0] << "," << result7[i][1] << "]";
        if (i < result7.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    cout << "Expected: [[1,4]]" << endl << endl;
    
    return 0;
}

/*
Algorithm Explanation:

Step 1: Sort intervals by start time
- Ensures we process intervals in chronological order
- Makes it easy to detect overlaps

Step 2: Iterate and merge
- Keep track of last merged interval
- For each new interval:
  - If it overlaps with last (start <= last.end), merge them
  - Otherwise, add it as a new separate interval

Overlap condition: currentStart <= lastEnd
Example: [1,5] and [3,6]
- 3 <= 5, so they overlap
- Merge to [1, max(5,6)] = [1,6]

Example walkthrough: [[1,5],[3,6],[8,10],[15,18]]

After sorting: [[1,5],[3,6],[8,10],[15,18]] (already sorted)

i=0: result = [[1,5]]
i=1: [3,6] - 3 <= 5, overlap! Merge to [1,6]
     result = [[1,6]]
i=2: [8,10] - 8 > 6, no overlap. Add new
     result = [[1,6],[8,10]]
i=3: [15,18] - 15 > 10, no overlap. Add new
     result = [[1,6],[8,10],[15,18]]

Edge cases:
1. Intervals touch at boundary: [1,4] and [4,5] → merge to [1,5]
2. One interval completely inside another: [1,4] and [2,3] → [1,4]
3. Unsorted input: [1,4] and [0,4] → after sort: [0,4], [1,4] → [0,4]

Time Complexity: O(n log n) for sorting + O(n) for merging = O(n log n)
Space Complexity: O(1) excluding output array (or O(n) for sorting depending on implementation)
*/
