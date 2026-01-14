// Find the City With the Smallest Number of Neighbors at a Threshold Distance (LeetCode 1334)
// Problem: There are n cities numbered from 0 to n-1. Given the array edges where
// edges[i] = [from, to, weight] represents a bidirectional edge.
// Find the city with the smallest number of cities that are reachable through some path
// and whose distance is at most distanceThreshold. If there are multiple such cities,
// return the city with the greatest number.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Initialize distance matrix
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        
        // Distance from city to itself is 0
        for(int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
        
        // Fill edges
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            dist[u][v] = wt;
            dist[v][u] = wt;
        }
        
        // Floyd-Warshall algorithm
        for(int k = 0; k < n; k++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        
        // Find city with smallest number of reachable cities
        int minReachable = n;
        int resultCity = 0;
        
        for(int i = 0; i < n; i++) {
            int reachableCount = 0;
            
            for(int j = 0; j < n; j++) {
                if(i != j && dist[i][j] <= distanceThreshold) {
                    reachableCount++;
                }
            }
            
            // Update if fewer reachable cities, or same count but greater city number
            if(reachableCount < minReachable || 
               (reachableCount == minReachable && i > resultCity)) {
                minReachable = reachableCount;
                resultCity = i;
            }
        }
        
        return resultCity;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> edges;
    
    for(int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back({u, v, wt});
    }
    
    int distanceThreshold;
    cin >> distanceThreshold;
    
    Solution obj;
    int result = obj.findTheCity(n, edges, distanceThreshold);
    
    cout << "City with smallest number of neighbors: " << result << endl;
    
    return 0;
}

// Time Complexity: O(n³)
// - Floyd-Warshall algorithm: O(n³)
// - Counting reachable cities for each city: O(n²)
// - Overall: O(n³)
//
// Space Complexity: O(n²)
// - Distance matrix: O(n²)
// - Overall: O(n²)
//
// Explanation:
// We need to find shortest distances between all pairs of cities, then count
// how many cities are reachable within threshold for each city.
//
// Algorithm:
// 1. Use Floyd-Warshall to find all-pairs shortest paths
// 2. For each city i, count how many cities j have dist[i][j] <= threshold
// 3. Find city with minimum reachable count
// 4. If tie, choose city with greater number
//
// Key Insight:
// - Need all-pairs shortest paths → Floyd-Warshall is perfect
// - Could also run Dijkstra from each city, but Floyd-Warshall is simpler
// - After getting all distances, counting is straightforward
//
// Why Floyd-Warshall?
// - Need distances from all cities to all other cities
// - Graph is small (n ≤ 100 typically)
// - Simple implementation
// - Alternative: Run Dijkstra n times → O(n² log n) for dense graphs
//
// Tie-breaking:
// - If multiple cities have same minimum reachable count
// - Choose the one with greatest city number
// - This is why we use i > resultCity in the condition
//
// Example:
// n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
// All-pairs distances:
//   0  1  2  3
// 0[0, 3, 4, 4]
// 1[3, 0, 1, 2]
// 2[4, 1, 0, 1]
// 3[4, 2, 1, 0]
//
// Reachable within threshold 4:
// City 0: cities 1,2,3 → count = 3
// City 1: cities 0,2,3 → count = 3
// City 2: cities 1,3 → count = 2
// City 3: cities 1,2 → count = 2
//
// Cities 2 and 3 have minimum count (2)
// Choose city 3 (greater number)
// Answer: 3
