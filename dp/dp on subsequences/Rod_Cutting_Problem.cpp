// Rod Cutting Problem (DP-24)
// Problem: Cut rod into pieces to maximize profit.

#include <bits/stdc++.h>
using namespace std;

// Tabulation with Space Optimization
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