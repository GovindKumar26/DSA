// Palindrome Partitioning III (DP-53) - LC 1278
// Problem: Partition string into k palindromic substrings with minimum changes.

#include <bits/stdc++.h>
using namespace std;

// Cost to make s[i..j] palindrome
int cost(string& s, int i, int j, vector<vector<int>>& costDP) {
    if (costDP[i][j] != -1) return costDP[i][j];
    
    int cnt = 0;
    while (i < j) {
        if (s[i] != s[j]) cnt++;
        i++;
        j--;
    }
    return costDP[i][j] = cnt;
}

// Memoization
int solve(int idx, int k, string& s, vector<vector<int>>& dp, vector<vector<int>>& costDP) {
    if (k == 1) {
        return cost(s, idx, s.size()-1, costDP);
    }
    if (dp[idx][k] != -1) return dp[idx][k];
    
    int mini = INT_MAX;
    for (int j = idx; j < s.size() - k + 1; j++) {
        int c = cost(s, idx, j, costDP) + solve(j+1, k-1, s, dp, costDP);
        mini = min(mini, c);
    }
    
    return dp[idx][k] = mini;
}

int palindromePartition(string s, int k) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(k+1, -1));
    vector<vector<int>> costDP(n, vector<int>(n, -1));
    return solve(0, k, s, dp, costDP);
}

int main() {
    string s = "abc";
    int k = 2;
    cout << "Minimum changes: " << palindromePartition(s, k) << endl;
    return 0;
}

// Time Complexity: O(n^2 * k)
// Space Complexity: O(n^2 + n*k)