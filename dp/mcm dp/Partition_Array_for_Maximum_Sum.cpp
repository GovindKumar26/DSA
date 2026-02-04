// Partition Array for Maximum Sum (DP-54) - LC 1043
// Problem: Partition array into subarrays of length at most k, change all to max.

#include <bits/stdc++.h>
using namespace std;

// Memoization
int solve(int idx, int k, vector<int>& arr, vector<int>& dp) {
    int n = arr.size();
    if (idx == n) return 0;
    if (dp[idx] != -1) return dp[idx];
    
    int maxSum = 0;
    int maxElement = 0;
    int len = 0;
    
    for (int j = idx; j < min(n, idx + k); j++) {
        len++;
        maxElement = max(maxElement, arr[j]);
        int sum = len * maxElement + solve(j+1, k, arr, dp);
        maxSum = max(maxSum, sum);
    }
    
    return dp[idx] = maxSum;
}

int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> dp(n, -1);
    return solve(0, k, arr, dp);
}

int main() {
    vector<int> arr = {1, 15, 7, 9, 2, 5, 10};
    int k = 3;
    cout << "Maximum sum: " << maxSumAfterPartitioning(arr, k) << endl;
    return 0;
}

// Time Complexity: O(n*k)
// Space Complexity: O(n)