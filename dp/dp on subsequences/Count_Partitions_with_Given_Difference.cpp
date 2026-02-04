// Count Partitions with Given Difference (DP-18)
// Problem: Count partitions where S1 - S2 = D.
// S1 - S2 = D and S1 + S2 = totalSum => S1 = (totalSum + D)/2

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int countSubsetsWithSum(vector<int>& arr, int n, int target) {
    vector<int> prev(target+1, 0);
    prev[0] = 1;
    if (arr[0] == 0) prev[0] = 2;
    else if (arr[0] <= target) prev[arr[0]] = 1;
    
    for (int idx = 1; idx < n; idx++) {
        vector<int> curr(target+1, 0);
        for (int sum = 0; sum <= target; sum++) {
            int notTake = prev[sum];
            int take = 0;
            if (arr[idx] <= sum) {
                take = prev[sum - arr[idx]];
            }
            curr[sum] = (take + notTake) % MOD;
        }
        prev = curr;
    }
    
    return prev[target];
}

int countPartitions(int n, int d, vector<int>& arr) {
    int totalSum = 0;
    for (int num : arr) totalSum += num;
    
    // Check validity
    if (totalSum - d < 0 || (totalSum - d) % 2 != 0) return 0;
    
    int target = (totalSum - d) / 2;
    return countSubsetsWithSum(arr, n, target);
}

int main() {
    vector<int> arr = {5, 2, 6, 4};
    int d = 3;
    cout << "Count of partitions with difference " << d << ": " << countPartitions(arr.size(), d, arr) << endl;
    return 0;
}

// Time Complexity: O(n*target)
// Space Complexity: O(target)