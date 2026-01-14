// Dijkstra's Algorithm - Shortest Path in Weighted Graph
// Problem: Given a weighted graph with V vertices and E edges, find the shortest path
// from a source vertex to all other vertices. All edge weights must be non-negative.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int src) {
        // Priority queue: {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Distance array initialized to infinity
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
        
        pq.push({0, src});
        
        while(!pq.empty()) {
            int dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            
            // If we already found a better path, skip
            if(dis > dist[node]) continue;
            
            // Explore all neighbors
            for(auto& edge : adj[node]) {
                int neighbor = edge[0];
                int weight = edge[1];
                
                // Relaxation step
                if(dist[node] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[node] + weight;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        } 
        
        return dist;
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    
    vector<vector<int>> adj[V];
    
    for(int i = 0; i < E; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt}); // For undirected graph
    }
    
    int src;
    cin >> src;
    
    Solution obj;
    vector<int> result = obj.dijkstra(V, adj, src);
    
    cout << "Shortest distances from source " << src << ":" << endl;
    for(int i = 0; i < V; i++) {
        if(result[i] == INT_MAX) {
            cout << "Vertex " << i << ": INF (unreachable)" << endl;
        } else {
            cout << "Vertex " << i << ": " << result[i] << endl;
        }
    }
    
    return 0;
}

// Time Complexity: O((V + E) log V)
// - Each vertex is inserted into priority queue at most once: O(V log V)
// - Each edge is relaxed at most once: O(E log V)
// - Overall: O((V + E) log V)
//
// Space Complexity: O(V)
// - Distance array: O(V)
// - Priority queue: O(V) in worst case
// - Overall: O(V)
//
// Explanation:
// Dijkstra's algorithm finds the shortest path from a source to all vertices
// in a weighted graph with non-negative edge weights.
//
// Algorithm:
// 1. Initialize distance array with infinity, source distance = 0
// 2. Use a min-heap (priority queue) to always process the closest unvisited node
// 3. For each node:
//    - Pop the node with minimum distance from priority queue
//    - If we already found a better path to this node, skip it
//    - For each neighbor, try to relax the edge:
//      * If distance[node] + weight < distance[neighbor]:
//        - Update distance[neighbor]
//        - Add neighbor to priority queue with new distance
// 4. Return the distance array
//
// Key Insight:
// - Greedy approach: always process the closest unvisited node
// - Once a node is processed with minimum distance, that distance is final
// - Priority queue ensures we always pick the node with smallest tentative distance
// - Works only with non-negative weights (for negative weights, use Bellman-Ford)
//
// Why priority queue?
// - We need to efficiently find the node with minimum distance
// - Priority queue gives us O(log V) insertion and extraction
// - Without it, finding minimum would take O(V) each time
//
// Relaxation:
// - "Relaxing" an edge means checking if we can improve the shortest path
//   to a neighbor by going through the current node
// - If dist[u] + weight(u,v) < dist[v], we found a better path to v
//
// Example: Graph with edges [[0,1,4], [0,7,8], [1,2,8], [1,7,11], [2,3,7], 
//          [2,8,2], [2,5,4], [3,4,9], [3,5,14], [4,5,10], [5,6,2], [6,7,1], [6,8,6], [7,8,7]]
// Source = 0
// Distances: [0, 4, 12, 19, 21, 11, 9, 8, 14]
// Path to 4: 0 -> 7 -> 6 -> 5 -> 4 (distance = 8 + 1 + 2 + 10 = 21)
