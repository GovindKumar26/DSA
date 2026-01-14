// Find Eventual Safe States (LeetCode 802)
// Problem: There is a directed graph of n nodes with each node labeled from 0 to n - 1.
// A node is a terminal node if there are no outgoing edges. A node is a safe node if every 
// possible path starting from that node leads to a terminal node (or another safe node).
// Return an array containing all the safe nodes of the graph in sorted order.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        
        // Reverse the graph and calculate indegree
        vector<vector<int>> reverseAdj(n);
        vector<int> indegree(n, 0);
        
        for(int i = 0; i < n; i++) {
            for(int neighbor : graph[i]) {
                reverseAdj[neighbor].push_back(i);
                indegree[i]++;
            }
        }
        
        // Add all terminal nodes (indegree 0 in original graph) to queue
        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> safeNodes;
        
        // Process nodes using BFS
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            safeNodes.push_back(node);
            
            // Process nodes that point to current safe node
            for(int neighbor : reverseAdj[node]) {
                indegree[neighbor]--;
                if(indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // Sort the result
        sort(safeNodes.begin(), safeNodes.end());
        
        return safeNodes;
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
// - Reversing graph: O(V + E)
// - BFS traversal: O(V + E)
// - Sorting result: O(V log V)
// - Overall: O(V + E + V log V) = O(V log V + E)
//
// Space Complexity: O(V + E)
// - Reverse adjacency list: O(V + E)
// - Indegree array: O(V)
// - Queue: O(V) in worst case
// - Result array: O(V)
// - Overall: O(V + E)
//
// Explanation:
// A safe node is one from which all paths lead to terminal nodes (nodes with no outgoing edges).
// Nodes in a cycle or leading to a cycle are NOT safe.
//
// Algorithm:
// 1. Reverse the graph (if A -> B, make B -> A in reversed graph)
// 2. Calculate indegree in the original graph (outgoing edges)
// 3. Terminal nodes have indegree 0 (no outgoing edges) - these are safe
// 4. Use BFS (similar to topological sort):
//    - Start with terminal nodes (indegree 0)
//    - Process nodes that point to safe nodes
//    - If all outgoing edges lead to safe nodes, the node is safe
// 5. Sort and return all safe nodes
//
// Key Insight: By reversing the graph, we can use topological sort logic.
// Terminal nodes are safe. Nodes that only point to safe nodes are also safe.
// Nodes in cycles will never have indegree 0, so they won't be marked as safe.
