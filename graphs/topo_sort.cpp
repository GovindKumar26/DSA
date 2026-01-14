// Topological Sort (DFS-based)
// Problem: Given a Directed Acyclic Graph (DAG) with V vertices and E edges, 
// find any valid topological ordering of vertices.

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void dfs(int node, vector<int> adj[], vector<int>& vis, stack<int>& st) {
        vis[node] = 1;
        
        for(auto neighbor : adj[node]) {
            if(!vis[neighbor]) {
                dfs(neighbor, adj, vis, st);
            }
        }
        
        st.push(node);
    }
    
public:
    vector<int> topoSort(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        stack<int> st;
        
        // Perform DFS from all unvisited nodes
        for(int i = 0; i < V; i++) {
            if(!vis[i]) {
                dfs(i, adj, vis, st);
            }
        }
        
        // Extract elements from stack to get topological order
        vector<int> result;
        while(!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }
        
        return result;
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    
    vector<int> adj[V];
    
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    Solution obj;
    vector<int> result = obj.topoSort(V, adj);
    
    for(auto node : result) {
        cout << node << " ";
    }
    cout << endl;
    
    return 0;
}

// Time Complexity: O(V + E)
// - We visit each vertex once: O(V)
// - We traverse all edges: O(E)
// - Overall: O(V + E)
//
// Space Complexity: O(V)
// - Visited array: O(V)
// - Stack for storing result: O(V)
// - Recursion stack in worst case: O(V)
// - Overall: O(V)
//
// Explanation:
// Topological sorting is a linear ordering of vertices in a DAG such that for every 
// directed edge u -> v, vertex u comes before v in the ordering.
// 
// Algorithm (DFS-based):
// 1. Mark the current node as visited
// 2. Recursively visit all unvisited neighbors
// 3. After visiting all neighbors, push current node to stack
// 4. The stack will contain nodes in reverse topological order
// 5. Pop all elements from stack to get the final topological order
//
// Key Insight: A node is added to the stack only after all its descendants are processed.
