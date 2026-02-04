// Longest Common Subsequence (DP-25) - LC 1143
// Problem: Find length of longest common subsequence between two strings.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization
// TC: O(n*m), SC: O(n*m) + O(n+m) stack
int solveMemo(int i, int j, string& s1, string& s2, vector<vector<int>>& dp) {
    if (i < 0 || j < 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    
    if (s1[i] == s2[j]) {
        return dp[i][j] = 1 + solveMemo(i-1, j-1, s1, s2, dp);
    }
    
    return dp[i][j] = max(solveMemo(i-1, j, s1, s2, dp), solveMemo(i, j-1, s1, s2, dp));
}

int longestCommonSubsequenceMemo(string text1, string text2) {
    int n = text1.size(), m = text2.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo(n-1, m-1, text1, text2, dp);
}

// Approach 2: Tabulation with Space Optimization
// TC: O(n*m), SC: O(m)
int longestCommonSubsequence(string text1, string text2) {
    int n = text1.size(), m = text2.size();
    vector<int> prev(m+1, 0), curr(m+1, 0);
    
    // Base case: already initialized to 0
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (text1[i-1] == text2[j-1]) {
                curr[j] = 1 + prev[j-1];
            } else {
                curr[j] = max(prev[j], curr[j-1]);
            }
        }
        prev = curr;
    }
    
    return prev[m];
}

int main() {
    string text1 = "abcde";
    string text2 = "ace";
    cout << "LCS length: " << longestCommonSubsequence(text1, text2) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(m)