#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Rotate array to the right by k places
    // Time: O(n), Space: O(1)
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;  // Handle k > n
        
        // Reversal Algorithm:
        // 1. Reverse entire array
        // 2. Reverse first k elements
        // 3. Reverse remaining n-k elements
        
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
    
    // Rotate array to the left by k places
    void rotateLeft(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        
        // Reversal Algorithm for left rotation:
        // 1. Reverse first k elements
        // 2. Reverse remaining n-k elements
        // 3. Reverse entire array
        
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
        reverse(nums.begin(), nums.end());
    }
};

int main() {
    Solution sol;
    
    // Test right rotation
    vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7};
    int k1 = 3;
    cout << "Original array: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;
    
    sol.rotate(arr1, k1);
    cout << "After right rotation by " << k1 << ": ";
    for (int x : arr1) cout << x << " ";
    cout << endl;
    
    // Test left rotation
    vector<int> arr2 = {1, 2, 3, 4, 5, 6, 7};
    int k2 = 2;
    cout << "\nOriginal array: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;
    
    sol.rotateLeft(arr2, k2);
    cout << "After left rotation by " << k2 << ": ";
    for (int x : arr2) cout << x << " ";
    cout << endl;
    
    return 0;
}

/*
Example 1 (Right Rotation):
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]

Explanation:
- Original: [1, 2, 3, 4, 5, 6, 7]
- Reverse all: [7, 6, 5, 4, 3, 2, 1]
- Reverse first k=3: [5, 6, 7, 4, 3, 2, 1]
- Reverse remaining: [5, 6, 7, 1, 2, 3, 4]

Example 2 (Left Rotation):
Input: nums = [1,2,3,4,5,6,7], k = 2
Output: [3,4,5,6,7,1,2]

Time Complexity: O(n)
Space Complexity: O(1)
*/
