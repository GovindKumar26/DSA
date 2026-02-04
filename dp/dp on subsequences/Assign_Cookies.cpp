// Assign Cookies - LC 455 (Greedy, not DP)
// Problem: Maximize number of content children.

#include <bits/stdc++.h>
using namespace std;

int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    
    int child = 0, cookie = 0;
    while (child < g.size() && cookie < s.size()) {
        if (s[cookie] >= g[child]) {
            child++;
        }
        cookie++;
    }
    
    return child;
}

int main() {
    vector<int> g = {1, 2, 3};
    vector<int> s = {1, 1};
    cout << "Content children: " << findContentChildren(g, s) << endl;
    return 0;
}

// Time Complexity: O(nlogn + mlogm)
// Space Complexity: O(1)