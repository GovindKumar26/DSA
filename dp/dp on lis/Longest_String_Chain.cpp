// Longest String Chain (DP-45) - LC 1048
// Problem: Find longest chain where each word is formed by adding one letter.

#include <bits/stdc++.h>
using namespace std;

bool isPredecessor(string& s1, string& s2) {
    if (s1.size() + 1 != s2.size()) return false;
    
    int i = 0, j = 0;
    while (j < s2.size()) {
        if (i < s1.size() && s1[i] == s2[j]) {
            i++;
            j++;
        } else {
            j++;
        }
    }
    
    return i == s1.size();
}

int longestStrChain(vector<string>& words) {
    int n = words.size();
    sort(words.begin(), words.end(), [](string& a, string& b) {
        return a.size() < b.size();
    });
    
    vector<int> dp(n, 1);
    int maxLen = 1;
    
    for (int i = 1; i < n; i++) {
        for (int prev = 0; prev < i; prev++) {
            if (isPredecessor(words[prev], words[i])) {
                dp[i] = max(dp[i], 1 + dp[prev]);
            }
        }
        maxLen = max(maxLen, dp[i]);
    }
    
    return maxLen;
}

int main() {
    vector<string> words = {"a", "b", "ba", "bca", "bda", "bdca"};
    cout << "Longest string chain: " << longestStrChain(words) << endl;
    return 0;
}

// Time Complexity: O(n^2 * L) where L is average string length
// Space Complexity: O(n)