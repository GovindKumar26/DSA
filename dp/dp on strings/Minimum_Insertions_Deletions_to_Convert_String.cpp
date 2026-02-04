// Minimum Insertions/Deletions to Convert String (DP-30) - LC 583
// Problem: Min operations to convert word1 to word2.
// Delete from word1: n - LCS, Insert to word1: m - LCS

#include <bits/stdc++.h>
using namespace std;

int lcs(string text1, string text2) {
    int n = text1.size(), m = text2.size();
    vector<int> prev(m+1, 0), curr(m+1, 0);
    
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

int minDistance(string word1, string word2) {
    int n = word1.size(), m = word2.size();
    int lcsLen = lcs(word1, word2);
    
    int deletions = n - lcsLen;
    int insertions = m - lcsLen;
    
    return deletions + insertions;
}

int main() {
    string word1 = "sea";
    string word2 = "eat";
    cout << "Minimum operations: " << minDistance(word1, word2) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(m)