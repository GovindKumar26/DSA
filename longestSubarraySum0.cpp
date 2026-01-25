#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Find the length of longest contiguous subarray with sum equal to 0
    // Using prefix sum and hash map
    // Time: O(n), Space: O(n)
    int maxLen(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> prefixSumIndex; // stores first occurrence of each prefix sum
        int prefixSum = 0;
        int maxLength = 0;
        
        for (int i = 0; i < n; i++) {
            prefixSum += arr[i];
            
            // If prefix sum is 0, subarray from index 0 to i has sum 0
            if (prefixSum == 0) {
                maxLength = i + 1;
            }
            
            // If this prefix sum has been seen before
            // subarray between previous occurrence and current index has sum 0
            if (prefixSumIndex.find(prefixSum) != prefixSumIndex.end()) {
                maxLength = max(maxLength, i - prefixSumIndex[prefixSum]);
            } else {
                // Store first occurrence of this prefix sum
                prefixSumIndex[prefixSum] = i;
            }
        }
        
        return maxLength;
    }
};

int main() {
    Solution sol;
    
    // Test case 1
    vector<int> arr1 = {15, -2, 2, -8, 1, 7, 10, 23};
    cout << "Test 1: [15, -2, 2, -8, 1, 7, 10, 23]" << endl;
    cout << "Output: " << sol.maxLen(arr1) << endl;
    cout << "Expected: 5 (subarray [-2, 2, -8, 1, 7])" << endl << endl;
    
    // Test case 2
    vector<int> arr2 = {1, 2, 3};
    cout << "Test 2: [1, 2, 3]" << endl;
    cout << "Output: " << sol.maxLen(arr2) << endl;
    cout << "Expected: 0 (no subarray with sum 0)" << endl << endl;
    
    // Test case 3
    vector<int> arr3 = {1, 0, -1, 2, -2};
    cout << "Test 3: [1, 0, -1, 2, -2]" << endl;
    cout << "Output: " << sol.maxLen(arr3) << endl;
    cout << "Expected: 5 (entire array sums to 0)" << endl << endl;
    
    // Test case 4
    vector<int> arr4 = {1, -1, 3, 4, -4, 0};
    cout << "Test 4: [1, -1, 3, 4, -4, 0]" << endl;
    cout << "Output: " << sol.maxLen(arr4) << endl;
    cout << "Expected: 5 (subarray [3, 4, -4, 0] or [-1, 3, 4, -4, 0])" << endl << endl;
    
    // Test case 5
    vector<int> arr5 = {0, 0, 0};
    cout << "Test 5: [0, 0, 0]" << endl;
    cout << "Output: " << sol.maxLen(arr5) << endl;
    cout << "Expected: 3 (entire array)" << endl << endl;
    
    return 0;
}
