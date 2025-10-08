class Solution {
  public:
    int maxSubarraySum(vector<int> &arr) {
        // Code here
        int maxSum = arr[0];     // in case all numbers are negative
        int currentSum = arr[0];
        
        for(int i = 1; i < arr.size(); i++) {
            currentSum = max(arr[i], currentSum + arr[i]);
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    } 
};

// Given an array of integers arr, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.
// time complexity: O(n)
// space complexity: O(1)