// Cycle Detection in Directed Graph (BFS - Kahn's Algorithm)
// Problem: Given a directed graph with V vertices and E edges, 
// detect if the graph contains a cycle.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int> indegree(V, 0);
        
        // Calculate indegree for all vertices
        for(int i = 0; i < V; i++) {
            for(auto neighbor : adj[i]) {
                indegree[neighbor]++;
            }
        }
        
        // Push all vertices with indegree 0 to queue
        queue<int> q;
        for(int i = 0; i < V; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int count = 0; // Count of vertices in topological order
        
        // Process vertices in BFS manner
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            count++;
            
            // Reduce indegree of neighbors
            for(auto neighbor : adj[node]) {
                indegree[neighbor]--;
                if(indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // If count != V, there's a cycle
        return count != V;
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
    
    if(obj.isCyclic(V, adj)) {
        cout << "Graph contains cycle" << endl;
    } else {
        cout << "Graph doesn't contain cycle" << endl;
    }
    
    return 0;
}

// Time Complexity: O(V + E)
// - Calculating indegree: O(V + E)
// - BFS traversal: O(V + E)
// - Overall: O(V + E)
//
// Space Complexity: O(V)
// - Indegree array: O(V)
// - Queue: O(V) in worst case
// - Overall: O(V)
//
// Explanation:
// This approach uses Kahn's Algorithm (BFS-based topological sort) to detect cycles.
//
// Algorithm:
// 1. Calculate indegree for all vertices
// 2. Add all vertices with indegree 0 to queue
// 3. Process vertices in BFS manner:
//    - Remove vertex from queue and increment count
//    - Reduce indegree of all neighbors
//    - Add neighbors with indegree 0 to queue
// 4. If count of processed vertices != V, graph has a cycle
//
// Key Insight: In a DAG, we can process all V vertices using topological sort.
// If we can't process all vertices (count < V), it means some vertices are part
// of a cycle and will never have indegree 0, hence they won't be processed.
