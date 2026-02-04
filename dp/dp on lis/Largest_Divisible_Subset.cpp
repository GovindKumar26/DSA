// Largest Divisible Subset (DP-44) - LC 368
// Problem: Find largest subset where every pair (i, j) satisfies nums[i] % nums[j] == 0.

#include <bits/stdc++.h>
using namespace std;

vector<int> largestDivisibleSubset(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    
    vector<int> dp(n, 1);
    vector<int> hash(n);
    int maxLen = 1;
    int lastIndex = 0;
    
    for (int i = 0; i < n; i++) {
        hash[i] = i;
        for (int prev = 0; prev < i; prev++) {
            if (nums[i] % nums[prev] == 0 && 1 + dp[prev] > dp[i]) {
                dp[i] = 1 + dp[prev];
                hash[i] = prev;
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            lastIndex = i;
        }
    }
    
    // Backtrack
    vector<int> result;
    result.push_back(nums[lastIndex]);
    
    while (hash[lastIndex] != lastIndex) {
        lastIndex = hash[lastIndex];
        result.push_back(nums[lastIndex]);
    }
    
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    vector<int> nums = {1, 2, 4, 8};
    vector<int> result = largestDivisibleSubset(nums);
    cout << "Largest divisible subset: ";
    for (int x : result) cout << x << " ";
    cout << endl;
    return 0;
}

// Time Complexity: O(n^2)
// Space Complexity: O(n)