// Climbing Stairs - DP Problem
// Problem: Count ways to reach the nth step. Can climb 1 or 2 steps at a time.
// LC 70

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Recursion with Memoization (Top-Down)
// TC: O(n), SC: O(n) + O(n) stack space
int solve(int n, vector<int>& dp) {
    if (n <= 1) return 1;
    if (dp[n] != -1) return dp[n];
    
    return dp[n] = solve(n-1, dp) + solve(n-2, dp);
}

int climbStairsMemo(int n) {
    vector<int> dp(n+1, -1);
    return solve(n, dp);
}

// Approach 2: Tabulation (Bottom-Up)
// TC: O(n), SC: O(n)
int climbStairsTabulation(int n) {
    if (n <= 1) return 1;
    
    vector<int> dp(n+1);
    dp[0] = 1;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}

// Approach 3: Space Optimized
// TC: O(n), SC: O(1)
int climbStairsOptimized(int n) {
    if (n <= 1) return 1;
    
    int prev2 = 1, prev1 = 1;
    
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

int main() {
    int n = 5;
    cout << "Ways to climb " << n << " stairs: " << climbStairsOptimized(n) << endl;
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1) for optimized version
// Intuition: Similar to Fibonacci. At each step, we can come from (i-1) or (i-2).