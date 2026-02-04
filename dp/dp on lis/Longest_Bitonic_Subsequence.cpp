// Longest Bitonic Subsequence (DP-46) - LC 1671
// Problem: Find longest subsequence that first increases then decreases.

#include <bits/stdc++.h>
using namespace std;

int longestBitonicSequence(vector<int>& nums) {
    int n = nums.size();
    
    // LIS from left
    vector<int> dp1(n, 1);
    for (int i = 0; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (nums[prev] < nums[i]) {
                dp1[i] = max(dp1[i], 1 + dp1[prev]);
            }
        }
    }
    
    // LIS from right (LDS from left)
    vector<int> dp2(n, 1);
    for (int i = n-1; i >= 0; i--) {
        for (int prev = n-1; prev > i; prev--) {
            if (nums[prev] < nums[i]) {
                dp2[i] = max(dp2[i], 1 + dp2[prev]);
            }
        }
    }
    
    // Find maximum bitonic length
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        if (dp1[i] > 1 && dp2[i] > 1) { // Both sides should exist
            maxLen = max(maxLen, dp1[i] + dp2[i] - 1);
        }
    }
    
    return maxLen;
}

int main() {
    vector<int> nums = {1, 11, 2, 10, 4, 5, 2, 1};
    cout << "Longest bitonic sequence: " << longestBitonicSequence(nums) << endl;
    return 0;
}

// Time Complexity: O(n^2)
// Space Complexity: O(n)