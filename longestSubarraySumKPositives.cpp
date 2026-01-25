#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Sliding Window / Two Pointer Approach
    // Works ONLY for positive integers (no zeros, no negatives)
    // Time: O(n), Space: O(1)
    int longestSubarrayWithSumK(vector<int>& arr, int k) {
        int n = arr.size();
        int left = 0, right = 0;
        int sum = 0;
        int maxLen = 0;
        
        while (right < n) {
            // Expand window by adding current element
            sum += arr[right];
            
            // Shrink window from left while sum > k
            while (sum > k && left <= right) {
                sum -= arr[left];
                left++;
            }
            
            // Check if current window has sum = k
            if (sum == k) {
                maxLen = max(maxLen, right - left + 1);
            }
            
            right++;
        }
        
        return maxLen;
    }
    
    // If array contains zeros along with positives, use this version
    // Time: O(n), Space: O(1)
    int longestSubarrayWithZeros(vector<int>& arr, int k) {
        int n = arr.size();
        int left = 0, right = 0;
        int sum = 0;
        int maxLen = 0;
        
        while (right < n) {
            sum += arr[right];
            
            // Shrink only when sum > k (zeros don't increase sum)
            while (sum > k && left <= right) {
                sum -= arr[left];
                left++;
            }
            
            if (sum == k) {
                maxLen = max(maxLen, right - left + 1);
            }
            
            right++;
        }
        
        return maxLen;
    }
};

int main() {
    Solution sol;
    
    // Test case 1
    vector<int> arr1 = {1, 2, 3, 1, 1, 1, 1};
    int k1 = 3;
    cout << "Array: [1, 2, 3, 1, 1, 1, 1], k = 3" << endl;
    cout << "Longest subarray length: " << sol.longestSubarrayWithSumK(arr1, k1) << endl;
    // Output: 3 (subarray [1, 1, 1])
    
    // Test case 2
    vector<int> arr2 = {1, 2, 3, 4, 5};
    int k2 = 9;
    cout << "\nArray: [1, 2, 3, 4, 5], k = 9" << endl;
    cout << "Longest subarray length: " << sol.longestSubarrayWithSumK(arr2, k2) << endl;
    // Output: 3 (subarray [2, 3, 4])
    
    // Test case 3 - with zeros
    vector<int> arr3 = {1, 0, 0, 2, 3, 0};
    int k3 = 3;
    cout << "\nArray: [1, 0, 0, 2, 3, 0], k = 3" << endl;
    cout << "Longest subarray length: " << sol.longestSubarrayWithZeros(arr3, k3) << endl;
    // Output: 4 (subarray [1, 0, 0, 2])
    
    return 0;
}

/*
Problem: Find the longest subarray with sum = k (array has only positive integers)

Why Sliding Window works for POSITIVES ONLY:
- Adding elements increases sum, removing decreases it
- If sum > k, we MUST shrink the window (no way to reduce sum otherwise)
- This monotonic property doesn't hold with negatives

Example: arr = [1, 2, 3, 1, 1, 1, 1], k = 3

Step-by-step:
left=0, right=0: sum=1, sum<k, continue
left=0, right=1: sum=3, sum==k, maxLen=2 [1,2]
left=0, right=2: sum=6, sum>k, shrink
left=1, right=2: sum=5, sum>k, shrink  
left=2, right=2: sum=3, sum==k, maxLen=2 [3]
left=2, right=3: sum=4, sum>k, shrink
left=3, right=3: sum=1, sum<k, continue
left=3, right=4: sum=2, sum<k, continue
left=3, right=5: sum=3, sum==k, maxLen=3 [1,1,1]
left=3, right=6: sum=4, sum>k, shrink
left=4, right=6: sum=3, sum==k, maxLen=3 [1,1,1]

Answer: 3

For arrays with NEGATIVES: Use prefix sum + hashmap (O(n) time, O(n) space)
See: longestSubarraywithK.cpp

Time Complexity: O(n) - each element visited at most twice
Space Complexity: O(1)
*/
