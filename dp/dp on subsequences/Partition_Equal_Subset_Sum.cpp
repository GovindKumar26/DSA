// Partition Equal Subset Sum (DP-15) - LC 416
// Problem: Check if array can be partitioned into two subsets with equal sum.

#include <bits/stdc++.h>
using namespace std;

bool canPartition(vector<int>& nums) {
    int n = nums.size();
    int totalSum = 0;
    for (int num : nums) totalSum += num;
    
    // If odd sum, can't partition equally
    if (totalSum % 2 != 0) return false;
    
    int target = totalSum / 2;
    vector<bool> prev(target+1, false);
    prev[0] = true;
    if (nums[0] <= target) prev[nums[0]] = true;
    
    for (int idx = 1; idx < n; idx++) {
        vector<bool> curr(target+1, false);
        curr[0] = true;
        for (int sum = 1; sum <= target; sum++) {
            bool notTake = prev[sum];
            bool take = false;
            if (nums[idx] <= sum) {
                take = prev[sum - nums[idx]];
            }
            curr[sum] = take || notTake;
        }
        prev = curr;
    }
    
    return prev[target];
}

int main() {
    vector<int> nums = {1, 5, 11, 5};
    cout << "Can partition: " << (canPartition(nums) ? "Yes" : "No") << endl;
    return 0;
}

// Time Complexity: O(n*sum/2)
// Space Complexity: O(sum/2)