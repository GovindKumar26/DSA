// Partition Set Into 2 Subsets With Min Absolute Sum Diff (DP-16)
// Problem: Minimize |S1 - S2| where S1 and S2 are subset sums.

#include <bits/stdc++.h>
using namespace std;

int minSubsetSumDifference(vector<int>& arr, int n) {
    int totalSum = 0;
    for (int num : arr) totalSum += num;
    
    // Find all possible subset sums
    vector<bool> prev(totalSum+1, false);
    prev[0] = true;
    if (arr[0] <= totalSum) prev[arr[0]] = true;
    
    for (int idx = 1; idx < n; idx++) {
        vector<bool> curr(totalSum+1, false);
        curr[0] = true;
        for (int target = 1; target <= totalSum; target++) {
            bool notTake = prev[target];
            bool take = false;
            if (arr[idx] <= target) {
                take = prev[target - arr[idx]];
            }
            curr[target] = take || notTake;
        }
        prev = curr;
    }
    
    // Find minimum difference
    int minDiff = INT_MAX;
    for (int s1 = 0; s1 <= totalSum/2; s1++) {
        if (prev[s1]) {
            int s2 = totalSum - s1;
            minDiff = min(minDiff, abs(s1 - s2));
        }
    }
    
    return minDiff;
}

int main() {
    vector<int> arr = {1, 2, 3, 4};
    cout << "Minimum difference: " << minSubsetSumDifference(arr, arr.size()) << endl;
    return 0;
}

// Time Complexity: O(n*totalSum)
// Space Complexity: O(totalSum)