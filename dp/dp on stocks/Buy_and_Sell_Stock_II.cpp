// Buy and Sell Stock II (DP-36) - LC 122
// Problem: Buy and sell unlimited times (no cooldown).

#include <bits/stdc++.h>
using namespace std;

// Space Optimized DP
// TC: O(n), SC: O(1)
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    int aheadBuy = 0, aheadNotBuy = 0;
    int currBuy, currNotBuy;
    
    for (int i = n-1; i >= 0; i--) {
        currBuy = max(-prices[i] + aheadNotBuy, aheadBuy);
        currNotBuy = max(prices[i] + aheadBuy, aheadNotBuy);
        
        aheadBuy = currBuy;
        aheadNotBuy = currNotBuy;
    }
    
    return aheadBuy;
}

// Greedy approach - Add all positive differences
int maxProfitGreedy(vector<int>& prices) {
    int profit = 0;
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > prices[i-1]) {
            profit += prices[i] - prices[i-1];
        }
    }
    return profit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Maximum profit: " << maxProfitGreedy(prices) << endl;
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1)