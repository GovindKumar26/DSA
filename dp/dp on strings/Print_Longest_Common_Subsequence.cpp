// Print Longest Common Subsequence (DP-26)
// Problem: Print the actual LCS string.

#include <bits/stdc++.h>
using namespace std;

string printLCS(string text1, string text2) {
    int n = text1.size(), m = text2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    
    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Backtrack to find LCS
    string lcs = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (text1[i-1] == text2[j-1]) {
            lcs = text1[i-1] + lcs;
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return lcs;
}

int main() {
    string text1 = "abcde";
    string text2 = "ace";
    cout << "LCS: " << printLCS(text1, text2) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(n*m)