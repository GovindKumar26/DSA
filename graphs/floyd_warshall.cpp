// Floyd-Warshall Algorithm - All Pairs Shortest Path
// Problem: Given a weighted graph with V vertices, find the shortest path between
// every pair of vertices. Can handle negative edge weights but not negative cycles.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void floydWarshall(vector<vector<int>>& matrix) {
        int V = matrix.size();
        
        // Apply Floyd-Warshall algorithm
        for(int k = 0; k < V; k++) {
            for(int i = 0; i < V; i++) {
                for(int j = 0; j < V; j++) {
                    // If both paths exist, try to improve
                    if(matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX) {
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
                }
            }
        }
        
        // Check for negative cycle
        for(int i = 0; i < V; i++) {
            if(matrix[i][i] < 0) {
                cout << "Negative cycle detected!" << endl;
                return;
            }
        }
    }
};

int main() {
    int V;
    cin >> V;
    
    // Initialize matrix with infinity
    vector<vector<int>> matrix(V, vector<int>(V, INT_MAX));
    
    // Distance from a vertex to itself is 0
    for(int i = 0; i < V; i++) {
        matrix[i][i] = 0;
    }
    
    int E;
    cin >> E;
    
    for(int i = 0; i < E; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        matrix[u][v] = wt;
        // For undirected graph, uncomment the next line:
        // matrix[v][u] = wt;
    }
    
    Solution obj;
    obj.floydWarshall(matrix);
    
    cout << "Shortest distances between all pairs of vertices:" << endl;
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            if(matrix[i][j] == INT_MAX) {
                cout << "INF\t";
            } else {
                cout << matrix[i][j] << "\t";
            }
        }
        cout << endl;
    }
    
    return 0;
}

// Time Complexity: O(V³)
// - Three nested loops, each running V times
// - Overall: O(V³)
//
// Space Complexity: O(V²)
// - Distance matrix: O(V²)
// - Overall: O(V²)
//
// Explanation:
// Floyd-Warshall finds shortest paths between ALL pairs of vertices.
// It uses dynamic programming to consider all possible intermediate vertices.
//
// Algorithm:
// 1. Initialize matrix with edge weights (infinity if no edge)
// 2. Set diagonal to 0 (distance from vertex to itself)
// 3. For each vertex k (potential intermediate vertex):
//    - For each pair of vertices (i, j):
//      * Check if path i -> k -> j is shorter than current i -> j
//      * If yes, update matrix[i][j] = matrix[i][k] + matrix[k][j]
// 4. Check for negative cycles (if matrix[i][i] < 0 for any i)
//
// Key Insight:
// - DP approach: build solution by considering intermediate vertices one by one
// - matrix[i][j] after k iterations = shortest path from i to j using vertices {0,1,...,k}
// - After considering all V vertices, we have shortest paths for all pairs
//
// Why it works:
// - Any path from i to j either:
//   a) Doesn't use vertex k as intermediate → matrix[i][j] unchanged
//   b) Uses vertex k as intermediate → matrix[i][k] + matrix[k][j]
// - We take the minimum of these two options
// - By considering all vertices as intermediate, we find optimal paths
//
// Negative Cycle Detection:
// - After algorithm completes, check diagonal elements
// - If matrix[i][i] < 0, there's a negative cycle involving vertex i
// - In a valid graph, distance from a vertex to itself should be 0
//
// Comparison with other algorithms:
// - Dijkstra (from single source): O((V+E) log V) per source, O(V²(V+E) log V) for all pairs
// - Bellman-Ford (from single source): O(V×E) per source, O(V²×E) for all pairs
// - Floyd-Warshall (all pairs): O(V³)
// - For dense graphs (E ≈ V²), Floyd-Warshall is often more efficient for all pairs
//
// When to use Floyd-Warshall:
// ✅ Need shortest paths between ALL pairs of vertices
// ✅ Graph is dense (many edges)
// ✅ Graph is small (V ≤ 400-500)
// ✅ May have negative weights (but no negative cycles)
// ❌ Don't use for large graphs (V > 1000) - too slow
// ❌ Don't use if only need single source shortest paths
//
// Example:
// Graph with 4 vertices:
// Edges: [[0,1,3], [0,3,7], [1,0,8], [1,2,2], [2,0,5], [2,3,1], [3,0,2]]
// 
// Initial matrix:
//   0   3  INF  7
//   8   0   2  INF
//   5  INF  0   1
//   2  INF INF  0
//
// After Floyd-Warshall:
//   0   3   5   6
//   5   0   2   3
//   3   6   0   1
//   2   5   7   0
//
// Shortest path from 1 to 3: 1 -> 2 -> 3 (distance = 2 + 1 = 3)
