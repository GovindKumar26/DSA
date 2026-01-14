// Path with Minimum Effort (LeetCode 1631)
// Problem: Given a 2D array of heights, find a path from top-left to bottom-right
// that minimizes the maximum absolute difference in heights between consecutive cells.
// You can move in 4 directions (up, down, left, right).

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        
        // Priority queue: {effort, {x, y}}
        priority_queue<pair<int, pair<int, int>>, 
                      vector<pair<int, pair<int, int>>>, 
                      greater<pair<int, pair<int, int>>>> pq;
        
        // Effort array initialized to infinity
        vector<vector<int>> effort(m, vector<int>(n, INT_MAX));
        effort[0][0] = 0;
        
        pq.push({0, {0, 0}});
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        while(!pq.empty()) {
            auto [currEffort, pos] = pq.top();
            auto [x, y] = pos;
            pq.pop();
            
            // If reached destination
            if(x == m-1 && y == n-1) {
                return currEffort;
            }
            
            // If already found better path
            if(currEffort > effort[x][y]) continue;
            
            // Explore 4 directions
            for(int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if(nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    // Maximum effort is the max of current effort and edge weight
                    int newEffort = max(currEffort, abs(heights[nx][ny] - heights[x][y]));
                    
                    if(newEffort < effort[nx][ny]) {
                        effort[nx][ny] = newEffort;
                        pq.push({newEffort, {nx, ny}});
                    }
                }
            }
        }
        
        return 0;
    }
};

int main() {
    int m, n;
    cin >> m >> n;
    
    vector<vector<int>> heights(m, vector<int>(n));
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cin >> heights[i][j];
        }
    }
    
    Solution obj;
    int result = obj.minimumEffortPath(heights);
    
    cout << "Minimum effort: " << result << endl;
    
    return 0;
}

// Time Complexity: O(m × n × log(m × n))
// - Each cell can be added to priority queue at most once
// - Priority queue operations: O(log(m × n))
// - Overall: O(m × n × log(m × n))
//
// Space Complexity: O(m × n)
// - Effort array: O(m × n)
// - Priority queue: O(m × n) in worst case
// - Overall: O(m × n)
//
// Explanation:
// This is a modified Dijkstra's algorithm where instead of summing weights,
// we track the maximum absolute difference encountered on the path.
//
// Algorithm:
// 1. Use Dijkstra's algorithm with priority queue
// 2. Instead of adding edge weights, take maximum of:
//    - Current path effort
//    - Absolute difference between current and next cell
// 3. Always process cell with minimum effort first
// 4. Return effort when reaching destination
//
// Key Insight:
// - This is a "minimax" problem: minimize the maximum edge weight
// - We use Dijkstra because we want the path with minimum maximum effort
// - Edge weight = |heights[next] - heights[current]|
// - Path effort = max of all edge weights on the path
//
// Example:
// heights = [[1,2,2],
//            [3,8,2],
//            [5,3,5]]
// Path: (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2)
// Efforts: 1, 0, 6, 3
// Maximum effort: 6
// But better path: (0,0) -> (1,0) -> (2,0) -> (2,1) -> (2,2)
// Efforts: 2, 2, 2, 2
// Maximum effort: 2 (answer)
