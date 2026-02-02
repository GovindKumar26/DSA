// LeetCode 1202: Smallest String With Swaps - MEDIUM
// Problem: You can swap characters at any pair of indices in 'pairs' any number of times.
// Return the lexicographically smallest string possible.

#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rank;
    
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int node) {
        if(node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }
    
    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU == rootV) return;
        
        if(rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if(rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
};

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.length();
        DSU dsu(n);
        
        // Step 1: Group indices that can be swapped (they're in same component)
        for(auto& pair : pairs) {
            dsu.unite(pair[0], pair[1]);
        }
        
        // Step 2: Group characters by their root component
        unordered_map<int, vector<int>> components;  // root -> indices
        for(int i = 0; i < n; i++) {
            components[dsu.find(i)].push_back(i);
        }
        
        // Step 3: For each component, sort characters and assign back
        string result = s;
        for(auto& [root, indices] : components) {
            // Collect characters at these indices
            string chars = "";
            for(int idx : indices) {
                chars += s[idx];
            }
            
            // Sort characters
            sort(chars.begin(), chars.end());
            
            // Sort indices
            sort(indices.begin(), indices.end());
            
            // Assign sorted characters to sorted indices
            for(int i = 0; i < indices.size(); i++) {
                result[indices[i]] = chars[i];
            }
        }
        
        return result;
    }
};

/*
═══════════════════════════════════════════════════════════════════
INTUITION:
═══════════════════════════════════════════════════════════════════
Key insight: If we can swap (i, j) and (j, k), we can rearrange i, j, k
in any order through multiple swaps. This forms transitive connectivity.

DSU groups all indices that are transitively swappable.
Within each group, we can arrange characters in any order.
To get lexicographically smallest: sort characters in each group.

EXAMPLE:
s = "dcab", pairs = [[0,3],[1,2]]
- Union(0, 3) -> components: {0,3}, {1,2}
- Component {0,3}: chars 'd','b' -> sorted: 'b','d'
- Component {1,2}: chars 'c','a' -> sorted: 'a','c'
- Result: "bacd"

STEPS:
1. Use DSU to group swappable indices
2. For each component:
   - Extract characters
   - Sort them
   - Place back in sorted order

COMPLEXITY:
Time: O(E·α(n) + n·log(n)) where E = pairs
  - Building DSU: O(E·α(n))
  - Sorting each component: O(n·log(n)) total
Space: O(n)

WHY THIS WORKS:
If indices are in same DSU component, they can be rearranged freely.
Sorting gives lexicographically smallest arrangement.
═══════════════════════════════════════════════════════════════════
*/

int main() {
    Solution sol;
    
    string s1 = "dcab";
    vector<vector<int>> pairs1 = {{0,3},{1,2}};
    cout << "Test 1: " << sol.smallestStringWithSwaps(s1, pairs1) << endl;
    // Expected: "bacd"
    
    string s2 = "dcab";
    vector<vector<int>> pairs2 = {{0,3},{1,2},{0,2}};
    cout << "Test 2: " << sol.smallestStringWithSwaps(s2, pairs2) << endl;
    // Expected: "abcd" (all connected)
    
    string s3 = "cba";
    vector<vector<int>> pairs3 = {{0,1},{1,2}};
    cout << "Test 3: " << sol.smallestStringWithSwaps(s3, pairs3) << endl;
    // Expected: "abc"
    
    return 0;
}
