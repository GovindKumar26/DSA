// House Robber (DP-6) - LC 198, 213
// Problem: Houses arranged in a circle. Can't rob adjacent houses. Find max money.

#include <bits/stdc++.h>
using namespace std;

// Helper function for linear array
int robLinear(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);
    
    for (int i = 2; i < n; i++) {
        int curr = max(nums[i] + prev2, prev1);
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

// House Robber I (Linear houses)
// TC: O(n), SC: O(1)
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return max(nums[0], nums[1]);
    
    return robLinear(nums);
}

// House Robber II (Circular houses)
// TC: O(n), SC: O(n)
int robCircular(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return max(nums[0], nums[1]);
    
    // Case 1: Rob houses from 0 to n-2 (exclude last house)
    vector<int> temp1(nums.begin(), nums.end()-1);
    int case1 = robLinear(temp1);
    
    // Case 2: Rob houses from 1 to n-1 (exclude first house)
    vector<int> temp2(nums.begin()+1, nums.end());
    int case2 = robLinear(temp2);
    
    return max(case1, case2);
}

int main() {
    vector<int> nums1 = {2, 7, 9, 3, 1};
    cout << "House Robber I: " << rob(nums1) << endl;
    
    vector<int> nums2 = {2, 3, 2};
    cout << "House Robber II (Circular): " << robCircular(nums2) << endl;
    
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1)
// Key insight for circular: Either include first (exclude last) or include last (exclude first).