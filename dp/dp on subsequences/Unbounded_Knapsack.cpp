// Unbounded Knapsack (DP-23)
// Problem: Maximize value with infinite supply of each item.

#include <bits/stdc++.h>
using namespace std;

// Tabulation with Space Optimization
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