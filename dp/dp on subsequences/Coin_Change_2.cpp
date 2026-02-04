// Coin Change 2 (DP-22) - LC 518
// Problem: Count number of ways to make amount using given coins.

#include <bits/stdc++.h>
using namespace std;

// Tabulation with Space Optimization
// TC: O(n*amount), SC: O(amount)
int change(int amount, vector<int>& coins) {
    int n = coins.size();
    vector<int> prev(amount+1, 0);
    
    // Base case
    for (int a = 0; a <= amount; a++) {
        prev[a] = (a % coins[0] == 0) ? 1 : 0;
    }
    
    for (int idx = 1; idx < n; idx++) {
        vector<int> curr(amount+1, 0);
        for (int a = 0; a <= amount; a++) {
            int notTake = prev[a];
            int take = 0;
            if (coins[idx] <= a) {
                take = curr[a - coins[idx]];
            }
            curr[a] = take + notTake;
        }
        prev = curr;
    }
    
    return prev[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 5;
    cout << "Number of ways: " << change(amount, coins) << endl;
    return 0;
}

// Time Complexity: O(n*amount)
// Space Complexity: O(amount)