// Buy and Stock Sell IV (DP-38) - LC 188
// Problem: At most k transactions allowed.

#include <bits/stdc++.h>
using namespace std;

// Space Optimized DP
// TC: O(n*k), SC: O(k)
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    if (n == 0 || k == 0) return 0;
    
    vector<vector<int>> ahead(2, vector<int>(k+1, 0));
    vector<vector<int>> curr(2, vector<int>(k+1, 0));
    
    for (int i = n-1; i >= 0; i--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int cap = 1; cap <= k; cap++) {
                if (buy) {
                    curr[buy][cap] = max(-prices[i] + ahead[0][cap],
                                        ahead[1][cap]);
                } else {
                    curr[buy][cap] = max(prices[i] + ahead[1][cap-1],
                                        ahead[0][cap]);
                }
            }
        }
        ahead = curr;
    }
    
    return ahead[1][k];
}

int main() {
    vector<int> prices = {3, 2, 6, 5, 0, 3};
    int k = 2;
    cout << "Maximum profit: " << maxProfit(k, prices) << endl;
    return 0;
}

// Time Complexity: O(n*k)
// Space Complexity: O(k)