// Buy and Sell Stocks With Transaction Fee (DP-40) - LC 714
// Problem: Pay transaction fee on each sale.

#include <bits/stdc++.h>
using namespace std;

// Space Optimized DP
// TC: O(n), SC: O(1)
int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    int aheadBuy = 0, aheadNotBuy = 0;
    int currBuy, currNotBuy;
    
    for (int i = n-1; i >= 0; i--) {
        currBuy = max(-prices[i] + aheadNotBuy, aheadBuy);
        currNotBuy = max(prices[i] - fee + aheadBuy, aheadNotBuy);
        
        aheadBuy = currBuy;
        aheadNotBuy = currNotBuy;
    }
    
    return aheadBuy;
}

int main() {
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fee = 2;
    cout << "Maximum profit: " << maxProfit(prices, fee) << endl;
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1)