// Prim's Algorithm - Minimum Spanning Tree (MST)
// Problem: Given a weighted, undirected, and connected graph with V vertices and E edges,
// find the Minimum Spanning Tree (MST) - a subset of edges that connects all vertices
// with minimum total edge weight and no cycles.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // Priority queue: {weight, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        vector<int> visited(V, 0);
        
        // Start from node 0
        pq.push({0, 0});
        int mstWeight = 0; 
        
        while(!pq.empty()) {
            auto [weight, node] = pq.top();
            pq.pop();
            
            // If already visited, skip
            if(visited[node]) continue;
            
            // Mark as visited and add weight to MST
            visited[node] = 1;
            mstWeight += weight;
            
            // Explore all neighbors
            for(auto& edge : adj[node]) {
                int neighbor = edge[0];
                int edgeWeight = edge[1];
                
                if(!visited[neighbor]) {
                    pq.push({edgeWeight, neighbor});
                }
            }
        }
        
        return mstWeight;
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
        adj[v].push_back({u, wt});
    }
    
    Solution obj;
    int result = obj.spanningTree(V, adj);
    
    cout << "Minimum Spanning Tree weight: " << result << endl;
    
    return 0;
}

// Time Complexity: O((V + E) log V)
// - Each vertex is added to priority queue at most once: O(V log V)
// - Each edge is considered at most once: O(E log V)
// - Overall: O((V + E) log V)
//
// Space Complexity: O(V + E)
// - Adjacency list: O(V + E)
// - Visited array: O(V)
// - Priority queue: O(V) in worst case
// - Overall: O(V + E)
//
// Explanation:
// Prim's algorithm builds the MST by greedily selecting the minimum weight edge
// that connects a visited vertex to an unvisited vertex.
//
// Algorithm:
// 1. Start with any vertex (usually vertex 0)
// 2. Use a priority queue to always pick the minimum weight edge
// 3. For each vertex:
//    - Pop the minimum weight edge from priority queue
//    - If vertex is already visited, skip it
//    - Mark vertex as visited and add edge weight to MST total
//    - Add all edges from this vertex to unvisited neighbors to priority queue
// 4. Continue until all vertices are visited
// 5. Return total MST weight
//
// Key Insight:
// - Greedy approach: always pick the cheapest edge to expand the MST
// - Priority queue ensures we always process minimum weight edge first
// - We only add vertices to MST when we visit them (not when we add to queue)
// - This ensures we get the minimum total weight
//
// Why it works:
// - At each step, we add the minimum weight edge connecting MST to a new vertex
// - This greedy choice is always safe (proven by cut property)
// - The algorithm maintains a "cut" between visited and unvisited vertices
// - The minimum weight edge crossing this cut is always in some MST
//
// Difference from Dijkstra:
// - Dijkstra: tracks distance from source
// - Prim's: tracks edge weight to add vertex to MST
// - Both use priority queue, but optimize different things
//
// Example:
// Graph with 5 vertices:
// Edges: (0,1,2), (0,3,6), (1,2,3), (1,3,8), (1,4,5), (2,4,7), (3,4,9)
//
// Step-by-step:
// 1. Start at 0, MST = {0}, weight = 0
// 2. Add edge (0,1,2), MST = {0,1}, weight = 2
// 3. Add edge (1,2,3), MST = {0,1,2}, weight = 5
// 4. Add edge (1,4,5), MST = {0,1,2,4}, weight = 10
// 5. Add edge (0,3,6), MST = {0,1,2,3,4}, weight = 16
//
// MST edges: (0,1), (1,2), (1,4), (0,3)
// Total weight: 16
