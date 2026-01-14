// Find Eventual Safe States - DFS Solution (LeetCode 802)
// Problem: There is a directed graph of n nodes with each node labeled from 0 to n - 1.
// A node is a terminal node if there are no outgoing edges. A node is a safe node if every 
// possible path starting from that node leads to a terminal node (or another safe node).
// Return an array containing all the safe nodes of the graph in sorted order.

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool dfs(int node, vector<vector<int>>& graph, vector<int>& vis, vector<int>& pathVis, vector<int>& safe) {
        vis[node] = 1;
        pathVis[node] = 1;
        
        // Explore all neighbors
        for(int neighbor : graph[node]) {
            // If neighbor not visited, do DFS
            if(!vis[neighbor]) {
                if(dfs(neighbor, graph, vis, pathVis, safe)) {
                    // Cycle detected in path from neighbor
                    return true;
                }
            }
            // If neighbor is in current path, cycle detected
            else if(pathVis[neighbor]) {
                return true;
            }
        }
        
        // No cycle found from this node
        pathVis[node] = 0;
        safe[node] = 1;
        return false;
    }
    
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> vis(n, 0);
        vector<int> pathVis(n, 0);
        vector<int> safe(n, 0);
        
        // Check each node
        for(int i = 0; i < n; i++) {
            if(!vis[i]) {
                dfs(i, graph, vis, pathVis, safe);
            }
        }
        
        // Collect all safe nodes
        vector<int> result;
        for(int i = 0; i < n; i++) {
            if(safe[i]) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<vector<int>> graph(n);
    
    for(int i = 0; i < n; i++) {
        int edges;
        cin >> edges;
        for(int j = 0; j < edges; j++) {
            int neighbor;
            cin >> neighbor;
            graph[i].push_back(neighbor);
        }
    }
    
    Solution obj;
    vector<int> result = obj.eventualSafeNodes(graph);
    
    cout << "Safe nodes: ";
    for(int node : result) {
        cout << node << " ";
    }
    cout << endl;
    
    return 0;
}

// Time Complexity: O(V + E)
// where V = number of nodes and E = number of edges
// - DFS traversal visits each node once: O(V)
// - Each edge is explored once: O(E)
// - Overall: O(V + E)
//
// Space Complexity: O(V)
// - Visited array: O(V)
// - Path visited array: O(V)
// - Safe array: O(V)
// - Recursion stack: O(V) in worst case
// - Overall: O(V)
//
// Explanation:
// A safe node is one from which all paths lead to terminal nodes (nodes with no outgoing edges).
// Nodes in a cycle or leading to a cycle are NOT safe.
//
// Algorithm (DFS with Cycle Detection):
// 1. Use three arrays:
//    - vis[]: tracks if node has been visited
//    - pathVis[]: tracks nodes in current DFS path (for cycle detection)
//    - safe[]: marks nodes that are safe
// 2. For each unvisited node, perform DFS:
//    - Mark node as visited and add to current path
//    - Recursively visit all neighbors
//    - If neighbor is in current path, cycle detected (return true)
//    - If DFS from neighbor returns true, cycle exists (return true)
//    - After exploring all neighbors, remove from current path
//    - If no cycle found, mark node as safe
// 3. Collect all safe nodes and return
//
// Key Insight: 
// - pathVis[] helps detect cycles (if we encounter a node already in current path)
// - A node is safe only if:
//   a) It's a terminal node (no outgoing edges), OR
//   b) All paths from it lead to safe nodes (no cycles)
// - We mark a node as safe AFTER exploring all its neighbors without finding cycles
//
// Example: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
// Node 0 -> 1 -> 2 -> 5 (terminal) ✓ but also 0 -> 2 -> 5 ✓
// Node 0 -> 1 -> 2 -> 3 -> 0 (cycle!) ✗
// So nodes 0,1,2,3 are NOT safe (part of cycle)
// Nodes 4,5,6 are safe (5,6 are terminal, 4 leads to terminal)
