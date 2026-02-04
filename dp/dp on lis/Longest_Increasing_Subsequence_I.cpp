// Longest Increasing Subsequence I (DP-41) - LC 300
// Problem: Find length of longest strictly increasing subsequence.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: DP
// TC: O(n^2), SC: O(n)
int lengthOfLIS_DP(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    int maxLen = 1;
    
    for (int i = 1; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (nums[prev] < nums[i]) {
                dp[i] = max(dp[i], 1 + dp[prev]);
            }
        }
        maxLen = max(maxLen, dp[i]);
    }
    
    return maxLen;
}

// Approach 2: Binary Search
// TC: O(n log n), SC: O(n)
int lengthOfLIS(vector<int>& nums) {
    vector<int> temp;
    temp.push_back(nums[0]);
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > temp.back()) {
            temp.push_back(nums[i]);
        } else {
            int idx = lower_bound(temp.begin(), temp.end(), nums[i]) - temp.begin();
            temp[idx] = nums[i];
        }
    }
    
    return temp.size();
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS length: " << lengthOfLIS(nums) << endl;
    return 0;
}

// Time Complexity: O(n log n)
// Space Complexity: O(n)