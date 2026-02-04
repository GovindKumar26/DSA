// Minimum Cost to Cut the Stick (DP-50) - LC 1547
// Problem: Cut stick at given positions with minimum cost.

#include <bits/stdc++.h>
using namespace std;

// Memoization
int solve(int i, int j, vector<int>& cuts, vector<vector<int>>& dp) {
    if (i > j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    
    int mini = INT_MAX;
    for (int k = i; k <= j; k++) {
        int cost = cuts[j+1] - cuts[i-1] +
                   solve(i, k-1, cuts, dp) +
                   solve(k+1, j, cuts, dp);
        mini = min(mini, cost);
    }
    
    return dp[i][j] = mini;
}

int minCost(int n, vector<int>& cuts) {
    int c = cuts.size();
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    
    vector<vector<int>> dp(c+1, vector<int>(c+1, -1));
    return solve(1, c, cuts, dp);
}

int main() {
    int n = 7;
    vector<int> cuts = {1, 3, 4, 5};
    cout << "Minimum cost: " << minCost(n, cuts) << endl;
    return 0;
}

// Time Complexity: O(c^3)
// Space Complexity: O(c^2)