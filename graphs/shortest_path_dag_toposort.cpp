// Shortest Path in Directed Acyclic Graph (DAG) using Topological Sort
// Problem: Given a weighted Directed Acyclic Graph (DAG) with V vertices and E edges,
// find the shortest path from a source vertex to all other vertices.
// If a vertex is unreachable, its distance should be -1.

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void topoSort(int node, vector<pair<int, int>> adj[], vector<int>& vis, stack<int>& st) {
        vis[node] = 1;
        
        for(auto& [neighbor, weight] : adj[node]) {
            if(!vis[neighbor]) {
                topoSort(neighbor, adj, vis, st);
            }
        }
        
        st.push(node);
    }
    
public:
    vector<int> shortestPath(int V, int E, vector<vector<int>>& edges, int src) {
        // Build adjacency list with weights
        vector<pair<int, int>> adj[V];
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            adj[u].push_back({v, wt});
        }
        
        // Get topological sort
        vector<int> vis(V, 0);
        stack<int> st;
        
        for(int i = 0; i < V; i++) {
            if(!vis[i]) {
                topoSort(i, adj, vis, st);
            }
        }
        
        // Initialize distances
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
        
        // Process nodes in topological order
        while(!st.empty()) {
            int node = st.top();
            st.pop();
            
            // If this node is reachable
            if(dist[node] != INT_MAX) {
                // Update distances of all neighbors
                for(auto& [neighbor, weight] : adj[node]) {
                    if(dist[node] + weight < dist[neighbor]) {
                        dist[neighbor] = dist[node] + weight;
                    }
                }
            }
        }
        
        // Convert unreachable vertices to -1
        for(int i = 0; i < V; i++) {
            if(dist[i] == INT_MAX) {
                dist[i] = -1;
            }
        }
        
        return dist;
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    
    vector<vector<int>> edges;
    
    for(int i = 0; i < E; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back({u, v, wt});
    }
    
    int src;
    cin >> src;
    
    Solution obj;
    vector<int> result = obj.shortestPath(V, E, edges, src);
    
    cout << "Shortest distances from source " << src << ":" << endl;
    for(int i = 0; i < V; i++) {
        cout << "Vertex " << i << ": " << result[i] << endl;
    }
    
    return 0;
}

// Time Complexity: O(V + E)
// - Topological sort (DFS): O(V + E)
// - Processing nodes in topo order: O(V + E)
// - Overall: O(V + E)
//
// Space Complexity: O(V + E)
// - Adjacency list: O(V + E)
// - Visited array: O(V)
// - Stack: O(V)
// - Distance array: O(V)
// - Recursion stack: O(V)
// - Overall: O(V + E)
//
// Explanation:
// For DAGs, we can find shortest paths more efficiently than Dijkstra's algorithm
// by using topological sort. This works because in a DAG, we can process nodes
// in an order where all predecessors are processed before successors.
//
// Algorithm:
// 1. Build adjacency list with weights
// 2. Perform topological sort using DFS to get ordering of vertices
// 3. Initialize distance array with infinity, source distance = 0
// 4. Process nodes in topological order:
//    - For each node, if it's reachable (distance != infinity):
//      * Relax all outgoing edges
//      * Update neighbor's distance if we found a shorter path
// 5. Convert unreachable vertices (distance = infinity) to -1
// 6. Return distance array
//
// Key Insight:
// - Topological sort ensures we process nodes in dependency order
// - When we process a node, all paths to it have already been considered
// - This means we only need to visit each edge once (no need for priority queue)
// - This is more efficient than Dijkstra for DAGs: O(V + E) vs O((V + E) log V)
//
// Why it works:
// - In topological order, if there's an edge u -> v, u comes before v
// - When we process u, we've already found the shortest path to u
// - So we can correctly update the distance to v
// - No node needs to be processed more than once
//
// Example: DAG with edges [[0,1,2], [0,4,1], [4,5,4], [4,2,2], [1,2,3], [2,3,6], [5,3,1]]
// Source = 0
// Topo order: 0, 4, 1, 5, 2, 3
// Distances: [0, 2, 3, 6, 1, 5]
// Path to 3: 0 -> 4 -> 5 -> 3 (distance = 1 + 4 + 1 = 6)
