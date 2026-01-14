// Floyd-Warshall Algorithm with Path Reconstruction
// Problem: Given a weighted graph with V vertices, find the shortest path between
// every pair of vertices AND reconstruct the actual path.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void floydWarshall(vector<vector<int>>& dist, vector<vector<int>>& next) {
        int V = dist.size();
        
        // Apply Floyd-Warshall algorithm
        for(int k = 0; k < V; k++) {
            for(int i = 0; i < V; i++) {
                for(int j = 0; j < V; j++) {
                    // If both paths exist and going through k is better
                    if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        if(dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next[i][j] = next[i][k]; // Update next hop
                        }
                    }
                }
            }
        }
        
        // Check for negative cycle
        for(int i = 0; i < V; i++) {
            if(dist[i][i] < 0) {
                cout << "Negative cycle detected!" << endl;
                return;
            }
        }
    }
    
    vector<int> reconstructPath(int u, int v, vector<vector<int>>& next) {
        // If no path exists
        if(next[u][v] == -1) {
            return {};
        }
        
        vector<int> path;
        path.push_back(u);
        
        while(u != v) {
            u = next[u][v];
            path.push_back(u);
        }
        
        return path;
    }
};

int main() {
    int V;
    cin >> V;
    
    // Initialize distance matrix with infinity
    vector<vector<int>> dist(V, vector<int>(V, INT_MAX));
    
    // Initialize next matrix for path reconstruction
    // next[i][j] = next vertex to visit on shortest path from i to j
    vector<vector<int>> next(V, vector<int>(V, -1));
    
    // Distance from a vertex to itself is 0
    for(int i = 0; i < V; i++) {
        dist[i][i] = 0;
        next[i][i] = i;
    }
    
    int E;
    cin >> E;
    
    for(int i = 0; i < E; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        dist[u][v] = wt;
        next[u][v] = v; // Direct edge, so next hop is v itself
        // For undirected graph, uncomment:
        // dist[v][u] = wt;
        // next[v][u] = u;
    }
    
    Solution obj;
    obj.floydWarshall(dist, next);
    
    cout << "\nShortest distances between all pairs:" << endl;
    cout << "     ";
    for(int i = 0; i < V; i++) {
        cout << i << "\t";
    }
    cout << endl;
    
    for(int i = 0; i < V; i++) {
        cout << i << " -> ";
        for(int j = 0; j < V; j++) {
            if(dist[i][j] == INT_MAX) {
                cout << "INF\t";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
    
    // Example: Print paths from vertex 0 to all others
    cout << "\nPaths from vertex 0:" << endl;
    for(int i = 0; i < V; i++) {
        if(i == 0) continue;
        
        vector<int> path = obj.reconstructPath(0, i, next);
        
        if(path.empty()) {
            cout << "0 -> " << i << ": No path exists" << endl;
        } else {
            cout << "0 -> " << i << " (distance = " << dist[0][i] << "): ";
            for(int j = 0; j < path.size(); j++) {
                cout << path[j];
                if(j < path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
    
    // Interactive path query
    cout << "\nEnter source and destination to see path (-1 -1 to exit):" << endl;
    while(true) {
        int src, dest;
        cin >> src >> dest;
        
        if(src == -1 || dest == -1) break;
        
        if(src < 0 || src >= V || dest < 0 || dest >= V) {
            cout << "Invalid vertices!" << endl;
            continue;
        }
        
        vector<int> path = obj.reconstructPath(src, dest, next);
        
        if(path.empty()) {
            cout << "No path exists from " << src << " to " << dest << endl;
        } else {
            cout << "Path from " << src << " to " << dest << " (distance = " << dist[src][dest] << "): ";
            for(int j = 0; j < path.size(); j++) {
                cout << path[j];
                if(j < path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
    
    return 0;
}

// Time Complexity: O(V³)
// - Floyd-Warshall: O(V³)
// - Path reconstruction: O(V) per query
// - Overall: O(V³)
//
// Space Complexity: O(V²)
// - Distance matrix: O(V²)
// - Next matrix: O(V²)
// - Overall: O(V²)
//
// Explanation of Path Reconstruction:
//
// The 'next' matrix stores the next vertex to visit on the shortest path.
// - next[i][j] = the next vertex after i on the shortest path from i to j
//
// How it works:
// 1. Initially, for direct edge i -> j, next[i][j] = j
// 2. When we find a better path i -> k -> j:
//    - We update dist[i][j] = dist[i][k] + dist[k][j]
//    - We update next[i][j] = next[i][k]
//    - This means: to go from i to j, first go to next[i][k]
//
// To reconstruct path from u to v:
// 1. Start at u
// 2. Repeatedly follow next[current][v] until we reach v
// 3. Each step gives us the next vertex on the shortest path
//
// Example:
// If shortest path from 0 to 3 is: 0 -> 1 -> 2 -> 3
// Then:
// - next[0][3] = 1 (from 0, go to 1 to reach 3)
// - next[1][3] = 2 (from 1, go to 2 to reach 3)
// - next[2][3] = 3 (from 2, go to 3 to reach 3)
//
// Reconstruction:
// Start: u = 0, v = 3
// Step 1: path = [0], u = next[0][3] = 1, path = [0, 1]
// Step 2: u = next[1][3] = 2, path = [0, 1, 2]
// Step 3: u = next[2][3] = 3, path = [0, 1, 2, 3]
// Done: u == v
//
// Why update next[i][j] = next[i][k]?
// - When we find path i -> k -> j is better than direct i -> j
// - The first step from i is the same as going from i to k
// - So next hop from i (to reach j) = next hop from i (to reach k)
