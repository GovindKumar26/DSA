// Wildcard Matching (DP-34) - LC 44
// Problem: Match string with pattern containing '?' and '*'.
// '?' matches any single character, '*' matches any sequence.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization
// TC: O(n*m), SC: O(n*m) + O(n+m) stack
bool solveMemo(int i, int j, string& s, string& p, vector<vector<int>>& dp) {
    if (i < 0 && j < 0) return true;
    if (j < 0) return false;
    if (i < 0) {
        // Check if remaining pattern is all '*'
        for (int k = 0; k <= j; k++) {
            if (p[k] != '*') return false;
        }
        return true;
    }
    if (dp[i][j] != -1) return dp[i][j];
    
    if (s[i] == p[j] || p[j] == '?') {
        return dp[i][j] = solveMemo(i-1, j-1, s, p, dp);
    }
    if (p[j] == '*') {
        return dp[i][j] = solveMemo(i-1, j, s, p, dp) || solveMemo(i, j-1, s, p, dp);
    }
    return dp[i][j] = false;
}

bool isMatchMemo(string s, string p) {
    int n = s.size(), m = p.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo(n-1, m-1, s, p, dp);
}

// Approach 2: Tabulation with Space Optimization
// TC: O(n*m), SC: O(m)
bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    vector<bool> prev(m+1, false), curr(m+1, false);
    
    prev[0] = true;
    for (int j = 1; j <= m; j++) {
        if (p[j-1] == '*') {
            prev[j] = prev[j-1];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        curr[0] = false;
        for (int j = 1; j <= m; j++) {
            if (s[i-1] == p[j-1] || p[j-1] == '?') {
                curr[j] = prev[j-1];
            } else if (p[j-1] == '*') {
                curr[j] = prev[j] || curr[j-1];
            } else {
                curr[j] = false;
            }
        }
        prev = curr;
    }
    
    return prev[m];
}

int main() {
    string s = "aa";
    string p = "a*";
    cout << "Match: " << (isMatch(s, p) ? "Yes" : "No") << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(m)