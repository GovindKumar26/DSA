// Minimum Insertions to Make String Palindrome (DP-29) - LC 1312
// Problem: Minimum insertions to make string palindrome.
// Answer: n - LPS(s)

#include <bits/stdc++.h>
using namespace std;

int longestPalindromeSubseq(string s) {
    string t = s;
    reverse(t.begin(), t.end());
    
    int n = s.size();
    vector<int> prev(n+1, 0), curr(n+1, 0);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i-1] == t[j-1]) {
                curr[j] = 1 + prev[j-1];
            } else {
                curr[j] = max(prev[j], curr[j-1]);
            }
        }
        prev = curr;
    }
    
    return prev[n];
}

int minInsertions(string s) {
    int n = s.size();
    int lps = longestPalindromeSubseq(s);
    return n - lps;
}

int main() {
    string s = "mbadm";
    cout << "Minimum insertions: " << minInsertions(s) << endl;
    return 0;
}

// Time Complexity: O(n^2)
// Space Complexity: O(n)