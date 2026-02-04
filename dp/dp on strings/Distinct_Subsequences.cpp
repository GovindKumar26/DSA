// Distinct Subsequences (DP-32) - LC 115
// Problem: Count distinct subsequences of t in s.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization
// TC: O(n*m), SC: O(n*m) + O(n+m) stack
int solveMemo(int i, int j, string& s, string& t, vector<vector<int>>& dp) {
    if (j < 0) return 1; // Found a valid subsequence
    if (i < 0) return 0; // s exhausted, t not matched
    if (dp[i][j] != -1) return dp[i][j];
    
    if (s[i] == t[j]) {
        return dp[i][j] = solveMemo(i-1, j-1, s, t, dp) + solveMemo(i-1, j, s, t, dp);
    }
    return dp[i][j] = solveMemo(i-1, j, s, t, dp);
}

int numDistinctMemo(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo(n-1, m-1, s, t, dp);
}

// Approach 2: Tabulation with Space Optimization
// TC: O(n*m), SC: O(m)
int numDistinct(string s, string t) {
    int n = s.size(), m = t.size();
    vector<double> prev(m+1, 0), curr(m+1, 0);
    
    prev[0] = curr[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        curr[0] = 1;
        for (int j = 1; j <= m; j++) {
            if (s[i-1] == t[j-1]) {
                curr[j] = prev[j-1] + prev[j];
            } else {
                curr[j] = prev[j];
            }
        }
        prev = curr;
    }
    
    return (int)prev[m];
}

int main() {
    string s = "rabbbit";
    string t = "rabbit";
    cout << "Distinct subsequences: " << numDistinct(s, t) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(m)