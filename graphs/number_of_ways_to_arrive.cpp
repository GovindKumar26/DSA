// Number of Ways to Arrive at Destination (LeetCode 1976)
// Problem: You are in a city with n intersections numbered from 0 to n-1 with bi-directional roads.
// You are given roads array where roads[i] = [ui, vi, timei] means there is a road between ui and vi
// that takes timei minutes to travel. Find the number of ways to arrive at destination (n-1) from
// source (0) in the shortest time. Return answer modulo 10^9 + 7.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        const int MOD = 1e9 + 7;
        
        // Build adjacency list
        vector<pair<int, long long>> adj[n];
        for(auto& road : roads) {
            adj[road[0]].push_back({road[1], road[2]});
            adj[road[1]].push_back({road[0], road[2]});
        }
        
        // Priority queue: {time, node}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        
        vector<long long> dist(n, LLONG_MAX);
        vector<long long> ways(n, 0);
        
        dist[0] = 0;
        ways[0] = 1;
        
        pq.push({0, 0});
        
        while(!pq.empty()) {
            auto [time, node] = pq.top();
            pq.pop();
            
            // If already processed with better time
            if(time > dist[node]) continue;
            
            // Explore neighbors
            for(auto& [neighbor, travelTime] : adj[node]) {
                long long newTime = dist[node] + travelTime;
                
                // Found shorter path
                if(newTime < dist[neighbor]) {
                    dist[neighbor] = newTime;
                    ways[neighbor] = ways[node];
                    pq.push({newTime, neighbor});
                }
                // Found another path with same shortest time
                else if(newTime == dist[neighbor]) {
                    ways[neighbor] = (ways[neighbor] + ways[node]) % MOD;
                }
            }
        }
        
        return ways[n - 1];
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> roads;
    
    for(int i = 0; i < m; i++) {
        int u, v, time;
        cin >> u >> v >> time;
        roads.push_back({u, v, time});
    }
    
    Solution obj;
    int result = obj.countPaths(n, roads);
    
    cout << "Number of shortest paths: " << result << endl;
    
    return 0;
}

// Time Complexity: O((V + E) log V)
// - Dijkstra's algorithm: O((V + E) log V)
// - Overall: O((V + E) log V)
//
// Space Complexity: O(V + E)
// - Adjacency list: O(V + E)
// - Distance and ways arrays: O(V)
// - Priority queue: O(V)
// - Overall: O(V + E)
//
// Explanation:
// This is a modified Dijkstra's algorithm that counts the number of shortest paths
// in addition to finding the shortest distance.
//
// Algorithm:
// 1. Use Dijkstra's algorithm with an additional 'ways' array
// 2. ways[i] = number of shortest paths from source to node i
// 3. When we find a shorter path:
//    - Update distance
//    - Set ways[neighbor] = ways[node] (inherit count from current node)
// 4. When we find an equal-length path:
//    - Keep distance same
//    - Add ways[node] to ways[neighbor] (another way to reach neighbor)
// 5. Return ways[n-1]
//
// Key Insight:
// - If we reach a node via a shorter path, all previous paths are invalid
//   So we reset the count to the current node's count
// - If we reach a node via an equal-length path, it's another valid shortest path
//   So we add the current node's count to the neighbor's count
// - Use modulo to prevent overflow
//
// Why it works:
// - ways[node] represents total ways to reach 'node' in shortest time
// - When extending to neighbor:
//   * If shorter: this is the only shortest way, so ways[neighbor] = ways[node]
//   * If equal: this is an additional shortest way, so ways[neighbor] += ways[node]
//
// Example:
// n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
// Shortest time from 0 to 6 = 7
// Paths: 0->6 (direct), 0->4->6
// Answer: 2
