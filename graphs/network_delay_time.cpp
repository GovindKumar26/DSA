// Network Delay Time (LeetCode 743)
// Problem: You are given a network of n nodes labeled from 1 to n.
// You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi),
// where ui is the source node, vi is the target node, and wi is the time for a signal to travel.
// Send a signal from node k. Return the minimum time for all nodes to receive the signal.
// If impossible, return -1.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Build adjacency list
        vector<pair<int, int>> adj[n + 1];
        for(auto& time : times) {
            adj[time[0]].push_back({time[1], time[2]});
        }
        
        // Priority queue: {time, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Distance array
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        
        pq.push({0, k});
        
        while(!pq.empty()) {
            auto [time, node] = pq.top();
            pq.pop();
            
            // If already found better path
            if(time > dist[node]) continue;
            
            // Explore neighbors
            for(auto& [neighbor, travelTime] : adj[node]) {
                if(dist[node] + travelTime < dist[neighbor]) {
                    dist[neighbor] = dist[node] + travelTime;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        }
        
        // Find maximum time among all nodes
        int maxTime = 0;
        for(int i = 1; i <= n; i++) {
            if(dist[i] == INT_MAX) {
                return -1; // Some node is unreachable
            }
            maxTime = max(maxTime, dist[i]);
        }
        
        return maxTime;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> times;
    
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        times.push_back({u, v, w});
    }
    
    int k;
    cin >> k;
    
    Solution obj;
    int result = obj.networkDelayTime(times, n, k);
    
    if(result == -1) {
        cout << "Not all nodes can receive the signal" << endl;
    } else {
        cout << "Network delay time: " << result << endl;
    }
    
    return 0;
}

// Time Complexity: O((V + E) log V)
// where V = number of nodes, E = number of edges
// - Dijkstra's algorithm: O((V + E) log V)
// - Finding maximum: O(V)
// - Overall: O((V + E) log V)
//
// Space Complexity: O(V + E)
// - Adjacency list: O(V + E)
// - Distance array: O(V)
// - Priority queue: O(V)
// - Overall: O(V + E)
//
// Explanation:
// This is a single-source shortest path problem where we need to find
// the time for the signal to reach the farthest node.
//
// Algorithm:
// 1. Use Dijkstra's algorithm from source node k
// 2. Find shortest time to reach each node
// 3. The answer is the maximum time among all nodes
// 4. If any node is unreachable, return -1
//
// Key Insight:
// - Signal propagates simultaneously to all neighbors
// - Time for all nodes to receive = time for farthest node to receive
// - This is the maximum of all shortest path distances
// - Use Dijkstra because all weights are non-negative
//
// Why maximum time?
// - Signal is sent simultaneously from source
// - Each node receives signal as soon as shortest path is traversed
// - All nodes have received signal when the farthest node receives it
// - Hence, answer = max(shortest path to all nodes)
//
// Example:
// n = 4, times = [[2,1,1],[2,3,1],[3,4,1]], k = 2
// Shortest paths from 2:
// - 2 -> 1: time = 1
// - 2 -> 2: time = 0
// - 2 -> 3: time = 1
// - 2 -> 4: time = 2
// Maximum = 2 (answer)
