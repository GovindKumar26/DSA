// Longest Common Substring (DP-27)
// Problem: Find length of longest common substring (consecutive characters).

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Memoization (not typical but for completeness)
// TC: O(n*m), SC: O(n*m) + O(n+m) stack
int maxLen; // Global to track max

int solveMemo(int i, int j, string& s1, string& s2, vector<vector<int>>& dp) {
    if (i < 0 || j < 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    
    solveMemo(i-1, j, s1, s2, dp);
    solveMemo(i, j-1, s1, s2, dp);
    
    if (s1[i] == s2[j]) {
        dp[i][j] = 1 + solveMemo(i-1, j-1, s1, s2, dp);
        maxLen = max(maxLen, dp[i][j]);
    } else {
        dp[i][j] = 0;
    }
    
    return dp[i][j];
}

int longestCommonSubstringMemo(string text1, string text2) {
    int n = text1.size(), m = text2.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    maxLen = 0;
    solveMemo(n-1, m-1, text1, text2, dp);
    return maxLen;
}

// Approach 2: Tabulation with Space Optimization
// TC: O(n*m), SC: O(m)
int longestCommonSubstring(string text1, string text2) {
    int n = text1.size(), m = text2.size();
    vector<int> prev(m+1, 0), curr(m+1, 0);
    int maxLen = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (text1[i-1] == text2[j-1]) {
                curr[j] = 1 + prev[j-1];
                maxLen = max(maxLen, curr[j]);
            } else {
                curr[j] = 0;
            }
        }
        prev = curr;
    }
    
    return maxLen;
}

int main() {
    string text1 = "abcjklp";
    string text2 = "acjkp";
    cout << "Longest common substring length: " << longestCommonSubstring(text1, text2) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(m)