// G-50: Accounts Merge - DSU
// LeetCode 721
#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DisjointSet ds(n);
        
        // Map email to account index
        unordered_map<string, int> emailToIndex;
        
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];
                if (emailToIndex.find(email) == emailToIndex.end()) {
                    emailToIndex[email] = i;
                } else {
                    // This email belongs to another account, merge them
                    ds.unionByRank(i, emailToIndex[email]);
                }
            }
        }
        
        // Group emails by ultimate parent
        vector<set<string>> mergedEmails(n);
        for (auto& [email, idx] : emailToIndex) {
            int parent = ds.findUPar(idx);
            mergedEmails[parent].insert(email);
        }
        
        // Build result
        vector<vector<string>> result;
        for (int i = 0; i < n; i++) {
            if (mergedEmails[i].empty()) continue;
            
            vector<string> account;
            account.push_back(accounts[i][0]); // Name
            for (const string& email : mergedEmails[i]) {
                account.push_back(email);
            }
            result.push_back(account);
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    vector<vector<string>> accounts = {
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"Mary", "mary@mail.com"},
        {"John", "johnnybravo@mail.com"}
    };
    
    vector<vector<string>> result = sol.accountsMerge(accounts);
    
    for (auto& account : result) {
        for (auto& s : account) {
            cout << s << " ";
        }
        cout << endl;
    }
    
    return 0;
}
