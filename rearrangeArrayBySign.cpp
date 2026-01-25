#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Optimal: Single pass with two pointers
    // Time: O(n), Space: O(n) for result array
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        
        int posIdx = 0;  // Positive numbers go at even indices: 0, 2, 4...
        int negIdx = 1;  // Negative numbers go at odd indices: 1, 3, 5...
        
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                ans[posIdx] = nums[i];
                posIdx += 2;
            } else {
                ans[negIdx] = nums[i];
                negIdx += 2;
            }
        }
        
        return ans;
    }
    
    // Alternative: Using separate vectors (easier to understand)
    vector<int> rearrangeArraySimple(vector<int>& nums) {
        vector<int> pos, neg;
        
        // Separate positives and negatives
        for (int x : nums) {
            if (x > 0) pos.push_back(x);
            else neg.push_back(x);
        }
        
        // Merge alternately starting with positive
        vector<int> ans;
        for (int i = 0; i < pos.size(); i++) {
            ans.push_back(pos[i]);
            ans.push_back(neg[i]);
        }
        
        return ans;
    }
};

int main() {
    Solution sol;
    
    vector<int> nums1 = {3, 1, -2, -5, 2, -4};
    cout << "Input: [3, 1, -2, -5, 2, -4]" << endl;
    vector<int> res1 = sol.rearrangeArray(nums1);
    cout << "Output: [";
    for (int i = 0; i < res1.size(); i++) {
        cout << res1[i];
        if (i < res1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [3, -2, 1, -5, 2, -4]
    
    vector<int> nums2 = {-1, 1};
    cout << "\nInput: [-1, 1]" << endl;
    vector<int> res2 = sol.rearrangeArray(nums2);
    cout << "Output: [";
    for (int i = 0; i < res2.size(); i++) {
        cout << res2[i];
        if (i < res2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [1, -1]
    
    return 0;
}

/*
LeetCode 2149 - Rearrange Array Elements by Sign

Conditions:
1. Every consecutive pair has opposite signs
2. Order preserved for same-sign integers
3. Array begins with positive

Example:
Input: [3, 1, -2, -5, 2, -4]

Positives (in order): 3, 1, 2
Negatives (in order): -2, -5, -4

Result: [3, -2, 1, -5, 2, -4]
         +   -  +   -  +   -

Algorithm (Optimal):
- posIdx starts at 0, increments by 2 (even positions)
- negIdx starts at 1, increments by 2 (odd positions)
- Place each number at its corresponding index

Step-by-step for [3, 1, -2, -5, 2, -4]:
i=0: 3 > 0  → ans[0] = 3,  posIdx = 2
i=1: 1 > 0  → ans[2] = 1,  posIdx = 4
i=2: -2 < 0 → ans[1] = -2, negIdx = 3
i=3: -5 < 0 → ans[3] = -5, negIdx = 5
i=4: 2 > 0  → ans[4] = 2,  posIdx = 6
i=5: -4 < 0 → ans[5] = -4, negIdx = 7

ans = [3, -2, 1, -5, 2, -4]

Time Complexity: O(n)
Space Complexity: O(n) for the result array
*/
