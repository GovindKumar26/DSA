// Edit Distance (DP-33) - LC 72
// Problem: Minimum operations (insert, delete, replace) to convert word1 to word2.

#include <bits/stdc++.h>
using namespace std;

// Tabulation with Space Optimization
// TC: O(n*m), SC: O(m)
int minDistance(string word1, string word2) {
    int n = word1.size(), m = word2.size();
    vector<int> prev(m+1, 0), curr(m+1, 0);
    
    // Base case
    for (int j = 0; j <= m; j++) prev[j] = j;
    
    for (int i = 1; i <= n; i++) {
        curr[0] = i;
        for (int j = 1; j <= m; j++) {
            if (word1[i-1] == word2[j-1]) {
                curr[j] = prev[j-1];
            } else {
                int insert = curr[j-1];
                int deletee = prev[j];
                int replace = prev[j-1];
                curr[j] = 1 + min({insert, deletee, replace});
            }
        }
        prev = curr;
    }
    
    return prev[m];
}

int main() {
    string word1 = "horse";
    string word2 = "ros";
    cout << "Edit distance: " << minDistance(word1, word2) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(m)