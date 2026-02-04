// Shortest Common Supersequence (DP-31) - LC 1092
// Problem: Find shortest string that has both str1 and str2 as subsequences.
// Length = n + m - LCS(str1, str2)

#include <bits/stdc++.h>
using namespace std;

string shortestCommonSupersequence(string str1, string str2) {
    int n = str1.size(), m = str2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    
    // Fill DP table for LCS
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Build the supersequence
    string result = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (str1[i-1] == str2[j-1]) {
            result = str1[i-1] + result;
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            result = str1[i-1] + result;
            i--;
        } else {
            result = str2[j-1] + result;
            j--;
        }
    }
    
    while (i > 0) {
        result = str1[i-1] + result;
        i--;
    }
    while (j > 0) {
        result = str2[j-1] + result;
        j--;
    }
    
    return result;
}

int main() {
    string str1 = "abac";
    string str2 = "cab";
    cout << "Shortest common supersequence: " << shortestCommonSupersequence(str1, str2) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(n*m)