// Target Sum (DP-21) - LC 494
// Problem: Assign + or - to each element to get target sum.
// This is same as Count Partitions with Given Difference.

#include <bits/stdc++.h>
using namespace std;

int countSubsetsWithSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<int> prev(target+1, 0);
    prev[0] = 1;
    if (nums[0] == 0) prev[0] = 2;
    else if (nums[0] <= target) prev[nums[0]] = 1;
    
    for (int idx = 1; idx < n; idx++) {
        vector<int> curr(target+1, 0);
        for (int sum = 0; sum <= target; sum++) {
            int notTake = prev[sum];
            int take = 0;
            if (nums[idx] <= sum) {
                take = prev[sum - nums[idx]];
            }
            curr[sum] = take + notTake;
        }
        prev = curr;
    }
    
    return prev[target];
}

int findTargetSumWays(vector<int>& nums, int target) {
    int n = nums.size();
    int totalSum = 0;
    for (int num : nums) totalSum += num;
    
    // Check validity
    if (totalSum - target < 0 || (totalSum - target) % 2 != 0) return 0;
    
    int s1 = (totalSum - target) / 2;
    return countSubsetsWithSum(nums, s1);
}

int main() {
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    cout << "Ways to achieve target: " << findTargetSumWays(nums, target) << endl;
    return 0;
}

// Time Complexity: O(n*sum)
// Space Complexity: O(sum)