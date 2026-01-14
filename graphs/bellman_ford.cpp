// Bellman-Ford Algorithm - Shortest Path with Negative Weights
// Problem: Given a weighted graph with V vertices and E edges, find the shortest path
// from a source vertex to all other vertices. Can handle negative edge weights.
// Also detects negative weight cycles.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        // Distance array initialized to infinity
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
        
        // Relax all edges V-1 times
        for(int i = 0; i < V - 1; i++) {
            for(auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int wt = edge[2];
                
                // Relaxation step
                if(dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }
        
        // Check for negative weight cycle
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            
            if(dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                // Negative cycle detected
                return {-1};
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
    vector<int> result = obj.bellmanFord(V, edges, src);
    
    if(result.size() == 1 && result[0] == -1) {
        cout << "Negative weight cycle detected!" << endl;
    } else {
        cout << "Shortest distances from source " << src << ":" << endl;
        for(int i = 0; i < V; i++) {
            if(result[i] == INT_MAX) {
                cout << "Vertex " << i << ": INF (unreachable)" << endl;
            } else {
                cout << "Vertex " << i << ": " << result[i] << endl;
            }
        }
    }
    
    return 0;
}

// Time Complexity: O(V × E)
// - Relaxing all edges V-1 times: O(V × E)
// - Checking for negative cycle: O(E)
// - Overall: O(V × E)
//
// Space Complexity: O(V)
// - Distance array: O(V)
// - Overall: O(V)
//
// Explanation:
// Bellman-Ford algorithm finds shortest paths from a source vertex to all other vertices.
// Unlike Dijkstra, it can handle negative edge weights and detect negative cycles.
//
// Algorithm:
// 1. Initialize distance array with infinity, source distance = 0
// 2. Relax all edges V-1 times:
//    - For each edge (u, v, weight):
//      * If dist[u] + weight < dist[v], update dist[v]
// 3. Check for negative weight cycles:
//    - Try relaxing all edges one more time
//    - If any distance can still be reduced, negative cycle exists
// 4. Return distance array (or -1 if negative cycle found)
//
// Key Insight:
// - In a graph with V vertices, shortest path has at most V-1 edges
// - After i iterations, we have correct distances for all paths with ≤ i edges
// - After V-1 iterations, all shortest paths are found
// - If we can still relax edges after V-1 iterations, there's a negative cycle
//
// Why V-1 iterations?
// - Shortest path between any two vertices uses at most V-1 edges
// - If it uses V or more edges, it must revisit a vertex (cycle)
// - Each iteration finds shortest paths with one more edge
//
// Negative Weight Cycle:
// - A cycle whose total weight is negative
// - If such a cycle is reachable from source, shortest path is undefined
//   (we can keep going around the cycle to get smaller distances)
// - Bellman-Ford detects this by checking if distances can still improve
//   after V-1 iterations
//
// Comparison with Dijkstra:
// - Dijkstra: O((V+E) log V), but only non-negative weights
// - Bellman-Ford: O(V×E), but handles negative weights
// - Use Dijkstra when all weights are non-negative (faster)
// - Use Bellman-Ford when negative weights exist or need cycle detection
//
// Example 1 (No negative cycle):
// Edges: [[0,1,4], [0,2,3], [1,2,-2], [1,3,2], [2,3,4]]
// Source = 0
// Distances: [0, 4, 2, 6]
// Path to 2: 0 -> 1 -> 2 (distance = 4 + (-2) = 2)
//
// Example 2 (Negative cycle):
// Edges: [[0,1,1], [1,2,-1], [2,0,-1]]
// Source = 0
// Cycle: 0 -> 1 -> 2 -> 0 (total weight = 1 + (-1) + (-1) = -1)
// Result: Negative cycle detected!
