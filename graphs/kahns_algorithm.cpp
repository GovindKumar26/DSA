// Kahn's Algorithm (BFS-based Topological Sort)
// Problem: Given a Directed Acyclic Graph (DAG) with V vertices and E edges,
// find topological ordering using BFS (Kahn's Algorithm).

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topoSort(int V, vector<int> adj[]) {
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
        
        vector<int> result;
        
        // Process vertices in BFS manner
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);
            
            // Reduce indegree of neighbors
            for(auto neighbor : adj[node]) {
                indegree[neighbor]--;
                if(indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
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
// - Calculating indegree: O(V + E)
// - BFS traversal: O(V + E)
// - Overall: O(V + E)
//
// Space Complexity: O(V)
// - Indegree array: O(V)
// - Queue: O(V) in worst case
// - Result array: O(V)
// - Overall: O(V)
//
// Explanation:
// Kahn's Algorithm is a BFS-based approach for topological sorting.
//
// Algorithm:
// 1. Calculate indegree (number of incoming edges) for each vertex
// 2. Add all vertices with indegree 0 to a queue (these have no dependencies)
// 3. While queue is not empty:
//    a. Remove a vertex from queue and add to result
//    b. For each neighbor, decrease its indegree by 1
//    c. If neighbor's indegree becomes 0, add it to queue
// 4. The result contains the topological order
//
// Key Insight: We process nodes only when all their dependencies are satisfied.
// This algorithm can also detect cycles - if result size < V, graph has a cycle.
