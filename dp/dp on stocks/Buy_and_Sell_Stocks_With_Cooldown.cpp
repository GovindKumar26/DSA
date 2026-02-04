// Buy and Sell Stocks With Cooldown (DP-39) - LC 309
// Problem: After selling, must cooldown for 1 day.

#include <bits/stdc++.h>
using namespace std;

// Space Optimized DP
// TC: O(n), SC: O(1)
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<int> ahead1(2, 0), ahead2(2, 0), curr(2, 0);
    
    for (int i = n-1; i >= 0; i--) {
        // Can buy
        curr[1] = max(-prices[i] + ahead1[0], ahead1[1]);
        
        // Can sell (need ahead2 for cooldown)
        curr[0] = max(prices[i] + ahead2[1], ahead1[0]);
        
        ahead2 = ahead1;
        ahead1 = curr;
    }
    
    return ahead1[1];
}

int main() {
    vector<int> prices = {1, 2, 3, 0, 2};
    cout << "Maximum profit: " << maxProfit(prices) << endl;
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1)