class Solution {
  public:
    // Returns only the maximum sum
    int maxSubarraySum(vector<int> &arr) {
        int maxSum = INT_MIN;
        int currentSum = 0;

        for (int x : arr) {
            currentSum += x;
            maxSum = max(maxSum, currentSum);

            if (currentSum < 0) {
                currentSum = 0;
            }
        }

        return maxSum;
    }
    
    // Returns maximum sum along with the subarray indices [start, end]
    vector<int> maxSubarrayWithIndices(vector<int> &arr) {
        int n = arr.size();
        int maxSum = INT_MIN;
        int currentSum = 0;
        
        int start = 0, end = 0;      // Final answer indices
        int tempStart = 0;            // Potential start of current subarray
        
        for (int i = 0; i < n; i++) {
            currentSum += arr[i];
            
            // Update maxSum and record the subarray
            if (currentSum > maxSum) {
                maxSum = currentSum;
                start = tempStart;
                end = i;
            }
            
            // Reset when sum becomes negative
            if (currentSum < 0) {
                currentSum = 0;
                tempStart = i + 1;  // Next element is potential new start
            }
        }
        
        // Return {maxSum, startIndex, endIndex}
        return {maxSum, start, end};
    }
    
    // Prints the subarray with maximum sum
    void printMaxSubarray(vector<int> &arr) {
        vector<int> result = maxSubarrayWithIndices(arr);
        int maxSum = result[0];
        int start = result[1];
        int end = result[2];
        
        cout << "Maximum Sum: " << maxSum << endl;
        cout << "Subarray: [";
        for (int i = start; i <= end; i++) {
            cout << arr[i];
            if (i < end) cout << ", ";
        }
        cout << "]" << endl;
        cout << "Indices: [" << start << ", " << end << "]" << endl;
    }
};

// Given an array of integers arr, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.
// time complexity: O(n)
// space complexity: O(1)

/*
Example: arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]

Step-by-step:
i=0: currentSum=-2, maxSum=-2, start=0, end=0, reset -> tempStart=1
i=1: currentSum=1, maxSum=1, start=1, end=1
i=2: currentSum=-2, reset -> tempStart=3
i=3: currentSum=4, maxSum=4, start=3, end=3
i=4: currentSum=3
i=5: currentSum=5, maxSum=5, start=3, end=5
i=6: currentSum=6, maxSum=6, start=3, end=6
i=7: currentSum=1
i=8: currentSum=5

Answer: maxSum=6, subarray=[4,-1,2,1], indices=[3,6]
*/