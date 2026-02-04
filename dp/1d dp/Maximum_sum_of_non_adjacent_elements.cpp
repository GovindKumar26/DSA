// Maximum Sum of Non-Adjacent Elements (DP-5)
// Problem: Find maximum sum of non-adjacent elements in array.
// Also known as: House Robber problem

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Recursion with Memoization
// TC: O(n), SC: O(n) + O(n) stack space
int solve(int idx, vector<int>& nums, vector<int>& dp) {
    if (idx == 0) return nums[0];
    if (idx < 0) return 0;
    if (dp[idx] != -1) return dp[idx];
    
    int pick = nums[idx] + solve(idx-2, nums, dp);
    int notPick = solve(idx-1, nums, dp);
    
    return dp[idx] = max(pick, notPick);
}

int maxSumMemo(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    vector<int> dp(n, -1);
    return solve(n-1, nums, dp);
}

// Approach 2: Tabulation
// TC: O(n), SC: O(n)
int maxSumTabulation(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    
    for (int i = 2; i < n; i++) {
        int pick = nums[i] + dp[i-2];
        int notPick = dp[i-1];
        dp[i] = max(pick, notPick);
    }
    
    return dp[n-1];
}

// Approach 3: Space Optimized
// TC: O(n), SC: O(1)
int maxSumOptimized(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);
    
    for (int i = 2; i < n; i++) {
        int pick = nums[i] + prev2;
        int notPick = prev1;
        int curr = max(pick, notPick);
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

int main() {
    vector<int> nums = {2, 1, 4, 9};
    cout << "Maximum sum: " << maxSumOptimized(nums) << endl;
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1) for optimized
// Key insight: At each index, either pick (add to i-2) or don't pick (take i-1).