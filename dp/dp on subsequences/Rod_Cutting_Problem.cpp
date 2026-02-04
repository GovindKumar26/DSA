// Rod Cutting Problem (DP-24)
// Problem: Cut rod into pieces to maximize profit.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization
// TC: O(n*n), SC: O(n*n) + O(n) stack
int solveMemo(int idx, int N, vector<int>& price, vector<vector<int>>& dp) {
    if (idx == 0) {
        return N * price[0];
    }
    if (dp[idx][N] != -1) return dp[idx][N];
    
    int notTake = solveMemo(idx-1, N, price, dp);
    int take = INT_MIN;
    int rodLength = idx + 1;
    if (rodLength <= N) {
        take = price[idx] + solveMemo(idx, N - rodLength, price, dp);
    }
    
    return dp[idx][N] = max(take, notTake);
}

int cutRodMemo(vector<int>& price, int n) {
    vector<vector<int>> dp(n, vector<int>(n+1, -1));
    return solveMemo(n-1, n, price, dp);
}

// Approach 2: Tabulation with Space Optimization
// TC: O(n*n), SC: O(n)
int cutRod(vector<int>& price, int n) {
    vector<int> prev(n+1, 0);
    
    // Base case: for rod of length 1
    for (int len = 0; len <= n; len++) {
        prev[len] = len * price[0];
    }
    
    for (int idx = 1; idx < n; idx++) {
        vector<int> curr(n+1, 0);
        for (int len = 0; len <= n; len++) {
            int notTake = prev[len];
            int take = 0;
            int rodLength = idx + 1;
            if (rodLength <= len) {
                take = price[idx] + curr[len - rodLength];
            }
            curr[len] = max(take, notTake);
        }
        prev = curr;
    }
    
    return prev[n];
}

int main() {
    vector<int> price = {2, 5, 7, 8, 10};
    int n = price.size();
    cout << "Maximum profit: " << cutRod(price, n) << endl;
    return 0;
}

// Time Complexity: O(n*n)
// Space Complexity: O(n)