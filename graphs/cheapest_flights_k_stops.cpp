// Cheapest Flights Within K Stops (LeetCode 787)
// Problem: There are n cities connected by flights. You are given flights array where
// flights[i] = [from, to, price], and also given src, dst, and k.
// Find the cheapest price from src to dst with at most k stops.
// Return -1 if no such route exists.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Build adjacency list
        vector<pair<int, int>> adj[n];
        for(auto& flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }
        
        // Queue: {stops, {node, cost}}
        queue<pair<int, pair<int, int>>> q;
        q.push({0, {src, 0}});
        
        // Distance array to track minimum cost to reach each node
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        
        while(!q.empty()) {
            auto [stops, nodeInfo] = q.front();
            auto [node, cost] = nodeInfo;
            q.pop();
            
            // If exceeded k stops, skip
            if(stops > k) continue;
            
            // Explore neighbors
            for(auto& [neighbor, price] : adj[node]) {
                int newCost = cost + price;
                
                // Only update if we found a cheaper path
                if(newCost < dist[neighbor]) {
                    dist[neighbor] = newCost;
                    q.push({stops + 1, {neighbor, newCost}});
                }
            }
        }
        
        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> flights;
    
    for(int i = 0; i < m; i++) {
        int from, to, price;
        cin >> from >> to >> price;
        flights.push_back({from, to, price});
    }
    
    int src, dst, k;
    cin >> src >> dst >> k;
    
    Solution obj;
    int result = obj.findCheapestPrice(n, flights, src, dst, k);
    
    if(result == -1) {
        cout << "No route exists within " << k << " stops" << endl;
    } else {
        cout << "Cheapest price: " << result << endl;
    }
    
    return 0;
}

// Time Complexity: O(n + E × k)
// where n = number of cities, E = number of flights
// - In worst case, each edge is relaxed k times
// - BFS with constraint on stops
// - Overall: O(E × k)
//
// Space Complexity: O(n + E)
// - Adjacency list: O(n + E)
// - Distance array: O(n)
// - Queue: O(n) in worst case
// - Overall: O(n + E)
//
// Explanation:
// This is a constrained shortest path problem where we limit the number of stops.
// We use BFS with a twist - we track the number of stops taken.
//
// Algorithm:
// 1. Build adjacency list from flights
// 2. Use BFS starting from source
// 3. Track: current node, cost so far, number of stops
// 4. For each neighbor:
//    - Calculate new cost
//    - If cheaper than previous cost to neighbor, update and add to queue
//    - Only process if stops <= k
// 5. Return cost to destination (or -1 if unreachable)
//
// Key Insight:
// - We can't use standard Dijkstra because we have a constraint on stops
// - BFS works here because we process nodes level by level (stops)
// - We might visit same node multiple times with different stop counts
// - We update distance only if we found a cheaper path
//
// Why not Dijkstra?
// - Dijkstra would give shortest path without considering stop constraint
// - We need to explore paths with more stops if they're cheaper
// - BFS with stop tracking handles this constraint naturally
//
// Example:
// n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]]
// src = 0, dst = 3, k = 1
// Path 1: 0 -> 1 -> 3 (cost = 700, stops = 1) ✓
// Path 2: 0 -> 1 -> 2 -> 3 (cost = 400, stops = 2) ✗ (exceeds k)
// Answer: 700
