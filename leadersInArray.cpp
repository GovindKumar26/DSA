#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Traverse from right to left
    // Time: O(n), Space: O(1) excluding result
    vector<int> leaders(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        
        // Rightmost element is always a leader
        int maxFromRight = nums[n - 1];
        result.push_back(nums[n - 1]);
        
        // Traverse from right to left
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] > maxFromRight) {
                result.push_back(nums[i]);
                maxFromRight = nums[i];
            }
        }
        
        // Reverse to maintain original order
        reverse(result.begin(), result.end());
        
        return result;
    }
};

int main() {
    Solution sol;
    
    vector<int> nums1 = {16, 17, 4, 3, 5, 2};
    cout << "Input: [16, 17, 4, 3, 5, 2]" << endl;
    vector<int> res1 = sol.leaders(nums1);
    cout << "Leaders: [";
    for (int i = 0; i < res1.size(); i++) {
        cout << res1[i];
        if (i < res1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [17, 5, 2]
    
    vector<int> nums2 = {1, 2, 3, 4, 5};
    cout << "\nInput: [1, 2, 3, 4, 5]" << endl;
    vector<int> res2 = sol.leaders(nums2);
    cout << "Leaders: [";
    for (int i = 0; i < res2.size(); i++) {
        cout << res2[i];
        if (i < res2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [5]
    
    vector<int> nums3 = {5, 4, 3, 2, 1};
    cout << "\nInput: [5, 4, 3, 2, 1]" << endl;
    vector<int> res3 = sol.leaders(nums3);
    cout << "Leaders: [";
    for (int i = 0; i < res3.size(); i++) {
        cout << res3[i];
        if (i < res3.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [5, 4, 3, 2, 1]
    
    return 0;
}

/*
Problem: Leaders in an Array

A leader is an element STRICTLY GREATER than all elements to its right.
The rightmost element is always a leader.

Example: [16, 17, 4, 3, 5, 2]

Check each element:
- 16: elements to right = [17,4,3,5,2], 17 > 16, NOT a leader
- 17: elements to right = [4,3,5,2], 17 > all, LEADER ✓
- 4:  elements to right = [3,5,2], 5 > 4, NOT a leader
- 3:  elements to right = [5,2], 5 > 3, NOT a leader
- 5:  elements to right = [2], 5 > 2, LEADER ✓
- 2:  rightmost element, LEADER ✓

Output: [17, 5, 2]

Algorithm (Right to Left):
1. Start from rightmost, it's always a leader
2. Track maxFromRight
3. If nums[i] > maxFromRight, it's a leader
4. Reverse result to maintain original order

Step-by-step for [16, 17, 4, 3, 5, 2]:
i=5: 2, maxFromRight=2, leader → result=[2]
i=4: 5 > 2, maxFromRight=5, leader → result=[2,5]
i=3: 3 < 5, not a leader
i=2: 4 < 5, not a leader
i=1: 17 > 5, maxFromRight=17, leader → result=[2,5,17]
i=0: 16 < 17, not a leader

Reverse: [17, 5, 2]

Time Complexity: O(n)
Space Complexity: O(1) excluding result array
*/
