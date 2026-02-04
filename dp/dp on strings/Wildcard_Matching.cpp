// Wildcard Matching (DP-34) - LC 44
// Problem: Match string with pattern containing '?' and '*'.
// '?' matches any single character, '*' matches any sequence.

#include <bits/stdc++.h>
using namespace std;

// Tabulation with Space Optimization
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