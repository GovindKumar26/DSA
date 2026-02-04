// Frog Jump (DP-3)
// Problem: Frog can jump 1 or 2 steps. Find minimum cost to reach last stone.
// Cost is absolute difference in heights.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Recursion with Memoization
// TC: O(n), SC: O(n) + O(n) stack space
int solve(int idx, vector<int>& heights, vector<int>& dp) {
    if (idx == 0) return 0;
    if (dp[idx] != -1) return dp[idx];
    
    int jumpOne = solve(idx-1, heights, dp) + abs(heights[idx] - heights[idx-1]);
    int jumpTwo = INT_MAX;
    if (idx > 1) {
        jumpTwo = solve(idx-2, heights, dp) + abs(heights[idx] - heights[idx-2]);
    }
    
    return dp[idx] = min(jumpOne, jumpTwo);
}

int frogJumpMemo(int n, vector<int>& heights) {
    vector<int> dp(n, -1);
    return solve(n-1, heights, dp);
}

// Approach 2: Tabulation
// TC: O(n), SC: O(n)
int frogJumpTabulation(int n, vector<int>& heights) {
    vector<int> dp(n);
    dp[0] = 0;
    
    for (int i = 1; i < n; i++) {
        int jumpOne = dp[i-1] + abs(heights[i] - heights[i-1]);
        int jumpTwo = INT_MAX;
        if (i > 1) {
            jumpTwo = dp[i-2] + abs(heights[i] - heights[i-2]);
        }
        dp[i] = min(jumpOne, jumpTwo);
    }
    
    return dp[n-1];
}

// Approach 3: Space Optimized
// TC: O(n), SC: O(1)
int frogJumpOptimized(int n, vector<int>& heights) {
    int prev2 = 0, prev1 = 0;
    
    for (int i = 1; i < n; i++) {
        int jumpOne = prev1 + abs(heights[i] - heights[i-1]);
        int jumpTwo = INT_MAX;
        if (i > 1) {
            jumpTwo = prev2 + abs(heights[i] - heights[i-2]);
        }
        int curr = min(jumpOne, jumpTwo);
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

int main() {
    vector<int> heights = {10, 20, 30, 10};
    int n = heights.size();
    cout << "Minimum cost: " << frogJumpOptimized(n, heights) << endl;
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1) for optimized
// Key insight: At each position, choose minimum cost from last 1 or 2 jumps.