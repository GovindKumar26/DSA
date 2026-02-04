// Frog Jump with K distances (DP-4)
// Problem: Frog can jump from 1 to k steps. Find minimum cost to reach last stone.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Recursion with Memoization
// TC: O(n*k), SC: O(n) + O(n) stack space
int solve(int idx, vector<int>& heights, int k, vector<int>& dp) {
    if (idx == 0) return 0;
    if (dp[idx] != -1) return dp[idx];
    
    int minCost = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if (idx - j >= 0) {
            int cost = solve(idx-j, heights, k, dp) + abs(heights[idx] - heights[idx-j]);
            minCost = min(minCost, cost);
        }
    }
    
    return dp[idx] = minCost;
}

int frogJumpKMemo(int n, vector<int>& heights, int k) {
    vector<int> dp(n, -1);
    return solve(n-1, heights, k, dp);
}

// Approach 2: Tabulation
// TC: O(n*k), SC: O(n)
int frogJumpKTabulation(int n, vector<int>& heights, int k) {
    vector<int> dp(n);
    dp[0] = 0;
    
    for (int i = 1; i < n; i++) {
        int minCost = INT_MAX;
        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                int cost = dp[i-j] + abs(heights[i] - heights[i-j]);
                minCost = min(minCost, cost);
            }
        }
        dp[i] = minCost;
    }
    
    return dp[n-1];
}

int main() {
    vector<int> heights = {10, 30, 40, 50, 20};
    int n = heights.size();
    int k = 3;
    cout << "Minimum cost with k=" << k << ": " << frogJumpKTabulation(n, heights, k) << endl;
    return 0;
}

// Time Complexity: O(n*k)
// Space Complexity: O(n)
// Key insight: Try all k possible jumps and take minimum.