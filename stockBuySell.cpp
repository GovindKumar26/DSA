#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Maximum profit with at most ONE transaction
    // Time: O(n), Space: O(1)
    int stockBuySell(vector<int> arr, int n) {
        int minPrice = INT_MAX;   // Minimum price seen so far (best day to buy)
        int maxProfit = 0;        // Maximum profit achievable
        
        for (int i = 0; i < n; i++) {
            // Update minimum price if current is lower
            minPrice = min(minPrice, arr[i]);
            
            // Calculate profit if we sell today
            int profit = arr[i] - minPrice;
            
            // Update max profit
            maxProfit = max(maxProfit, profit);
        }
        
        return maxProfit;
    }
};

int main() {
    Solution sol;
    
    vector<int> arr1 = {7, 1, 5, 3, 6, 4};
    cout << "Prices: [7, 1, 5, 3, 6, 4]" << endl;
    cout << "Max Profit: " << sol.stockBuySell(arr1, arr1.size()) << endl;
    // Output: 5 (Buy at 1, Sell at 6)
    
    vector<int> arr2 = {7, 6, 4, 3, 1};
    cout << "\nPrices: [7, 6, 4, 3, 1]" << endl;
    cout << "Max Profit: " << sol.stockBuySell(arr2, arr2.size()) << endl;
    // Output: 0 (No profit possible, prices only decrease)
    
    vector<int> arr3 = {1, 2, 3, 4, 5};
    cout << "\nPrices: [1, 2, 3, 4, 5]" << endl;
    cout << "Max Profit: " << sol.stockBuySell(arr3, arr3.size()) << endl;
    // Output: 4 (Buy at 1, Sell at 5)
    
    return 0;
}

/*
Problem: Best Time to Buy and Sell Stock (Single Transaction)

Given stock prices for n days, find max profit by buying and selling ONCE.
Must buy before selling, cannot buy and sell on same day.

Example 1:
Input: [7, 1, 5, 3, 6, 4]
Output: 5

Explanation:
Day 1: price=7, minPrice=7, profit=0
Day 2: price=1, minPrice=1, profit=0
Day 3: price=5, minPrice=1, profit=4
Day 4: price=3, minPrice=1, profit=2
Day 5: price=6, minPrice=1, profit=5 ← Maximum
Day 6: price=4, minPrice=1, profit=3

Buy on day 2 (price=1), sell on day 5 (price=6), profit=5

Key Insight:
- For each day, we want to know the minimum price BEFORE this day
- Profit = current price - minimum price so far
- Track maximum of all such profits

Time Complexity: O(n)
Space Complexity: O(1)
*/
