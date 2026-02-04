// Buy and Sell Stocks III (DP-37) - LC 123
// Problem: At most 2 transactions allowed.

#include <bits/stdc++.h>
using namespace std;

// Space Optimized DP
// TC: O(n), SC: O(1)
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> ahead(2, vector<int>(3, 0));
    vector<vector<int>> curr(2, vector<int>(3, 0));
    
    for (int i = n-1; i >= 0; i--) {
        for (int buy = 0; buy <= 1; buy++) {
            for (int cap = 1; cap <= 2; cap++) {
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
    
    return ahead[1][2];
}

int main() {
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "Maximum profit: " << maxProfit(prices) << endl;
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1)