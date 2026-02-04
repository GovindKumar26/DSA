// Minimum Coins (DP-20) - LC 322
// Problem: Find minimum number of coins to make amount. Infinite supply of each coin.

#include <bits/stdc++.h>
using namespace std;

// Tabulation with Space Optimization
// TC: O(n*amount), SC: O(amount)
int coinChange(vector<int>& coins, int amount) {
    int n = coins.size();
    vector<int> prev(amount+1, 0);
    
    // Base case: for first coin
    for (int a = 0; a <= amount; a++) {
        if (a % coins[0] == 0) {
            prev[a] = a / coins[0];
        } else {
            prev[a] = 1e9;
        }
    }
    
    for (int idx = 1; idx < n; idx++) {
        vector<int> curr(amount+1, 0);
        for (int a = 0; a <= amount; a++) {
            int notTake = prev[a];
            int take = 1e9;
            if (coins[idx] <= a) {
                take = 1 + curr[a - coins[idx]];
            }
            curr[a] = min(take, notTake);
        }
        prev = curr;
    }
    
    return prev[amount] >= 1e9 ? -1 : prev[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    cout << "Minimum coins: " << coinChange(coins, amount) << endl;
    return 0;
}

// Time Complexity: O(n*amount)
// Space Complexity: O(amount)