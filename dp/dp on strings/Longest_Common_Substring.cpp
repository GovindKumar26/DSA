// Longest Common Substring (DP-27)
// Problem: Find length of longest common substring (consecutive characters).

#include <bits/stdc++.h>
using namespace std;

// Tabulation with Space Optimization
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