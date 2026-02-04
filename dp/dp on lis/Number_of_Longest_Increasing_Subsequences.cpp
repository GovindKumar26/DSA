// Number of Longest Increasing Subsequences (DP-47) - LC 673
// Problem: Count number of LIS.

#include <bits/stdc++.h>
using namespace std;

int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);    // Length of LIS ending at i
    vector<int> count(n, 1); // Count of LIS ending at i
    int maxLen = 1;
    
    for (int i = 1; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (nums[prev] < nums[i]) {
                if (dp[prev] + 1 > dp[i]) {
                    dp[i] = dp[prev] + 1;
                    count[i] = count[prev];
                } else if (dp[prev] + 1 == dp[i]) {
                    count[i] += count[prev];
                }
            }
        }
        maxLen = max(maxLen, dp[i]);
    }
    
    // Count all LIS with length = maxLen
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] == maxLen) {
            result += count[i];
        }
    }
    
    return result;
}

int main() {
    vector<int> nums = {1, 3, 5, 4, 7};
    cout << "Number of LIS: " << findNumberOfLIS(nums) << endl;
    return 0;
}

// Time Complexity: O(n^2)
// Space Complexity: O(n)