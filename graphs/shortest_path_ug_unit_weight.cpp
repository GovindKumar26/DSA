// Shortest Path in Undirected Graph with Unit Weights
// Problem: Given an undirected graph with V vertices and E edges where all edges have unit weight,
// find the shortest path from a source vertex to all other vertices.
// If a vertex is unreachable, its distance should be -1.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestPath(vector<vector<int>>& edges, int V, int E, int src) {
        // Build adjacency list
        vector<int> adj[V];
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u); // Undirected graph
        }
        
        // Distance array initialized to infinity
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
        
        // BFS queue
        queue<int> q;
        q.push(src);
        
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            
            // Explore all neighbors
            for(int neighbor : adj[node]) {
                // If we found a shorter path
                if(dist[node] + 1 < dist[neighbor]) {
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
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
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    
    int src;
    cin >> src;
    
    Solution obj;
    vector<int> result = obj.shortestPath(edges, V, E, src);
    
    cout << "Shortest distances from source " << src << ":" << endl;
    for(int i = 0; i < V; i++) {
        cout << "Vertex " << i << ": " << result[i] << endl;
    }
    
    return 0;
}

// Time Complexity: O(V + E)
// - Building adjacency list: O(E)
// - BFS traversal: O(V + E)
// - Overall: O(V + E)
//
// Space Complexity: O(V + E)
// - Adjacency list: O(V + E)
// - Distance array: O(V)
// - Queue: O(V) in worst case
// - Overall: O(V + E)
//
// Explanation:
// For undirected graphs with unit weights, BFS naturally finds the shortest path
// because it explores nodes level by level.
//
// Algorithm:
// 1. Build adjacency list from edges (undirected, so add both directions)
// 2. Initialize distance array with infinity, source distance = 0
// 3. Use BFS starting from source:
//    - Process current node
//    - For each neighbor, if we can reach it with shorter distance:
//      * Update its distance to current distance + 1
//      * Add to queue for further exploration
// 4. Convert unreachable vertices (distance = infinity) to -1
// 5. Return distance array
//
// Key Insight:
// - BFS explores nodes in order of increasing distance from source
// - Since all edges have unit weight (weight = 1), the first time we reach
//   a node is guaranteed to be via the shortest path
// - This is why BFS works perfectly for unweighted graphs
//
// Example: Graph with edges [[0,1], [0,3], [1,2], [3,4], [4,5], [5,6], [2,6]]
// Source = 0
// Distances: [0, 1, 2, 1, 2, 3, 3]
// Path to 6: 0 -> 1 -> 2 -> 6 (length 3) or 0 -> 3 -> 4 -> 5 -> 6 (length 4)
// BFS finds the shorter path
