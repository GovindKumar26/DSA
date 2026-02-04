// Unbounded Knapsack (DP-23)
// Problem: Maximize value with infinite supply of each item.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization
// TC: O(n*W), SC: O(n*W) + O(n) stack
int solveMemo(int idx, int W, vector<int>& val, vector<int>& wt, vector<vector<int>>& dp) {
    if (idx == 0) {
        return (W / wt[0]) * val[0];
    }
    if (dp[idx][W] != -1) return dp[idx][W];
    
    int notTake = solveMemo(idx-1, W, val, wt, dp);
    int take = 0;
    if (wt[idx] <= W) {
        take = val[idx] + solveMemo(idx, W - wt[idx], val, wt, dp);
    }
    
    return dp[idx][W] = max(take, notTake);
}

int unboundedKnapsackMemo(int n, int W, vector<int>& val, vector<int>& wt) {
    vector<vector<int>> dp(n, vector<int>(W+1, -1));
    return solveMemo(n-1, W, val, wt, dp);
}

// Approach 2: Tabulation with Space Optimization
// TC: O(n*W), SC: O(W)
int unboundedKnapsack(int n, int W, vector<int>& val, vector<int>& wt) {
    vector<int> prev(W+1, 0);
    
    // Base case: for first item
    for (int w = 0; w <= W; w++) {
        prev[w] = (w / wt[0]) * val[0];
    }
    
    for (int idx = 1; idx < n; idx++) {
        vector<int> curr(W+1, 0);
        for (int w = 0; w <= W; w++) {
            int notTake = prev[w];
            int take = 0;
            if (wt[idx] <= w) {
                take = val[idx] + curr[w - wt[idx]];
            }
            curr[w] = max(take, notTake);
        }
        prev = curr;
    }
    
    return prev[W];
}

int main() {
    vector<int> val = {10, 40, 50, 70};
    vector<int> wt = {1, 3, 4, 5};
    int W = 8;
    cout << "Maximum value: " << unboundedKnapsack(val.size(), W, val, wt) << endl;
    return 0;
}

// Time Complexity: O(n*W)
// Space Complexity: O(W)