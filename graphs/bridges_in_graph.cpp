// G-55: Bridges in Graph - Using Tarjan's Algorithm
// A bridge is an edge whose removal disconnects the graph
// LeetCode 1192: Critical Connections in a Network
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int timer = 0;
    
    void dfs(int node, int parent, vector<int> adj[], 
             vector<bool>& visited, vector<int>& tin, vector<int>& low,
             vector<vector<int>>& bridges) {
        
        visited[node] = true;
        tin[node] = low[node] = timer++;
        
        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;
            
            if (!visited[neighbor]) {
                dfs(neighbor, node, adj, visited, tin, low, bridges);
                
                // After DFS, update low value
                low[node] = min(low[node], low[neighbor]);
                
                // If lowest reachable from neighbor is greater than
                // insertion time of node, then this edge is a bridge
                if (low[neighbor] > tin[node]) {
                    bridges.push_back({node, neighbor});
                }
            } else {
                // Back edge - update low value
                low[node] = min(low[node], tin[neighbor]);
            }
        }
    }
    
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int> adj[n];
        
        // Build adjacency list
        for (auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }
        
        vector<bool> visited(n, false);
        vector<int> tin(n);   // Time of insertion in DFS
        vector<int> low(n);   // Lowest time reachable from subtree
        vector<vector<int>> bridges;
        
        // Start DFS from node 0 (assuming connected graph)
        dfs(0, -1, adj, visited, tin, low, bridges);
        
        return bridges;
    }
    
    // For disconnected graphs
    vector<vector<int>> findBridges(int n, vector<vector<int>>& edges) {
        vector<int> adj[n];
        
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n, false);
        vector<int> tin(n);
        vector<int> low(n);
        vector<vector<int>> bridges;
        timer = 0;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, -1, adj, visited, tin, low, bridges);
            }
        }
        
        return bridges;
    }
};

int main() {
    Solution sol;
    
    // Example 1: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
    int n1 = 4;
    vector<vector<int>> connections1 = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    
    vector<vector<int>> bridges1 = sol.criticalConnections(n1, connections1);
    
    cout << "Example 1 - Bridges: ";
    for (auto& bridge : bridges1) {
        cout << "[" << bridge[0] << "," << bridge[1] << "] ";
    }
    cout << endl;  // Output: [1,3]
    
    // Example 2: More complex graph
    int n2 = 6;
    vector<vector<int>> connections2 = {
        {0, 1}, {1, 2}, {2, 0},  // Cycle
        {1, 3}, {3, 4}, {4, 5}, {5, 3}  // Another cycle connected via bridge
    };
    
    vector<vector<int>> bridges2 = sol.criticalConnections(n2, connections2);
    
    cout << "Example 2 - Bridges: ";
    for (auto& bridge : bridges2) {
        cout << "[" << bridge[0] << "," << bridge[1] << "] ";
    }
    cout << endl;  // Output: [1,3]
    
    return 0;
}

/*
Tarjan's Algorithm for Bridges:

Key concepts:
- tin[node]: Time when node was first visited (insertion time)
- low[node]: Minimum tin reachable from subtree of node

An edge (u, v) is a bridge if:
- low[v] > tin[u]
- This means there's no back edge from v's subtree to u or u's ancestors
- So removing (u,v) would disconnect v's subtree from the rest

Time Complexity: O(V + E)
Space Complexity: O(V + E)

Note: Don't update low using parent's tin (that's the edge we're checking)
*/
