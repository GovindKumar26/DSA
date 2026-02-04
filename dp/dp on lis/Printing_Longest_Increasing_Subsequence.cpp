// Printing Longest Increasing Subsequence (DP-42)
// Problem: Print the actual LIS.

#include <bits/stdc++.h>
using namespace std;

vector<int> printLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    vector<int> hash(n);
    int maxLen = 1;
    int lastIndex = 0;
    
    for (int i = 0; i < n; i++) {
        hash[i] = i;
        for (int prev = 0; prev < i; prev++) {
            if (nums[prev] < nums[i] && 1 + dp[prev] > dp[i]) {
                dp[i] = 1 + dp[prev];
                hash[i] = prev;
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            lastIndex = i;
        }
    }
    
    // Backtrack to find LIS
    vector<int> lis;
    lis.push_back(nums[lastIndex]);
    
    while (hash[lastIndex] != lastIndex) {
        lastIndex = hash[lastIndex];
        lis.push_back(nums[lastIndex]);
    }
    
    reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> lis = printLIS(nums);
    cout << "LIS: ";
    for (int x : lis) cout << x << " ";
    cout << endl;
    return 0;
}

// Time Complexity: O(n^2)
// Space Complexity: O(n)