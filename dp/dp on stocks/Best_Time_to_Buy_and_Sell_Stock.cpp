// Best Time to Buy and Sell Stock (DP-35) - LC 121
// Problem: Buy once and sell once to maximize profit.

#include <bits/stdc++.h>
using namespace std;

// Simple approach - Track minimum price
// TC: O(n), SC: O(1)
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    
    return maxProfit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Maximum profit: " << maxProfit(prices) << endl;
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1)