// Longest Common Subsequence (DP-25) - LC 1143
// Problem: Find length of longest common subsequence between two strings.

#include <bits/stdc++.h>
using namespace std;

// Tabulation with Space Optimization
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