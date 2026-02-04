// Subset Sum Equal to Target (DP-14)
// Problem: Check if there exists a subset with given sum.

#include <bits/stdc++.h>
using namespace std;

// Memoization
// TC: O(n*target), SC: O(n*target) + O(n) stack
bool solve(int idx, int target, vector<int>& arr, vector<vector<int>>& dp) {
    if (target == 0) return true;
    if (idx == 0) return arr[0] == target;
    if (dp[idx][target] != -1) return dp[idx][target];
    
    bool notTake = solve(idx-1, target, arr, dp);
    bool take = false;
    if (arr[idx] <= target) {
        take = solve(idx-1, target-arr[idx], arr, dp);
    }
    
    return dp[idx][target] = take || notTake;
}

// Tabulation with Space Optimization
// TC: O(n*target), SC: O(target)
bool subsetSumToK(int n, int k, vector<int>& arr) {
    vector<bool> prev(k+1, false);
    prev[0] = true;
    if (arr[0] <= k) prev[arr[0]] = true;
    
    for (int idx = 1; idx < n; idx++) {
        vector<bool> curr(k+1, false);
        curr[0] = true;
        for (int target = 1; target <= k; target++) {
            bool notTake = prev[target];
            bool take = false;
            if (arr[idx] <= target) {
                take = prev[target - arr[idx]];
            }
            curr[target] = take || notTake;
        }
        prev = curr;
    }
    
    return prev[k];
}

int main() {
    vector<int> arr = {1, 2, 3, 4};
    int target = 4;
    cout << "Subset with sum " << target << ": " << (subsetSumToK(arr.size(), target, arr) ? "Yes" : "No") << endl;
    return 0;
}