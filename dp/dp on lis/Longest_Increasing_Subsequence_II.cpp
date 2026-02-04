// Longest Increasing Subsequence II (DP-43)
// Problem: LIS with constraint |nums[i] - nums[j]| <= k
// This is a variation, typically solved with segment tree or coordinate compression.

#include <bits/stdc++.h>
using namespace std;

// Using map for coordinate compression
// TC: O(n log n), SC: O(n)
int lengthOfLIS(vector<int>& nums, int k) {
    map<int, int> dp; // value -> max length ending at this value
    
    for (int num : nums) {
        auto it = dp.lower_bound(num - k);
        int maxLen = 0;
        
        while (it != dp.end() && it->first < num) {
            maxLen = max(maxLen, it->second);
            it++;
        }
        
        dp[num] = maxLen + 1;
        
        // Remove entries that are dominated
        it = dp.find(num);
        it++;
        while (it != dp.end() && it->second <= dp[num]) {
            it = dp.erase(it);
        }
    }
    
    int result = 0;
    for (auto& p : dp) {
        result = max(result, p.second);
    }
    
    return result;
}

int main() {
    vector<int> nums = {4, 2, 1, 4, 3, 4, 5, 8, 15};
    int k = 3;
    cout << "LIS with k constraint: " << lengthOfLIS(nums, k) << endl;
    return 0;
}

// Time Complexity: O(n log n)
// Space Complexity: O(n)