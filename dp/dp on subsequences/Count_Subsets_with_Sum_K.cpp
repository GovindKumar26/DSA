// Count Subsets with Sum K (DP-17)
// Problem: Count number of subsets with given sum.

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Tabulation with Space Optimization
// TC: O(n*k), SC: O(k)
int countSubsets(vector<int>& arr, int n, int k) {
    vector<int> prev(k+1, 0);
    prev[0] = 1;
    if (arr[0] <= k) prev[arr[0]] = 1;
    if (arr[0] == 0) prev[0] = 2; // Two ways: include or exclude 0
    
    for (int idx = 1; idx < n; idx++) {
        vector<int> curr(k+1, 0);
        curr[0] = 1;
        for (int target = 0; target <= k; target++) {
            int notTake = prev[target];
            int take = 0;
            if (arr[idx] <= target) {
                take = prev[target - arr[idx]];
            }
            curr[target] = (take + notTake) % MOD;
        }
        prev = curr;
    }
    
    return prev[k];
}

int main() {
    vector<int> arr = {1, 2, 2, 3};
    int k = 3;
    cout << "Count of subsets with sum " << k << ": " << countSubsets(arr, arr.size(), k) << endl;
    return 0;
}

// Time Complexity: O(n*k)
// Space Complexity: O(k)