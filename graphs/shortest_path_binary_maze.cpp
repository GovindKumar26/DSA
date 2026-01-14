// Shortest Path in a Binary Maze (LeetCode 1091 - Shortest Path in Binary Matrix)
// Problem: Given an n x n binary matrix grid, return the length of the shortest clear path.
// A clear path is a path from top-left (0,0) to bottom-right (n-1,n-1) such that:
// - All visited cells are 0
// - All adjacent cells are 8-directionally connected
// Return -1 if no such path exists.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // If start or end is blocked
        if(grid[0][0] == 1 || grid[n-1][n-1] == 1) {
            return -1;
        }
        
        // 8 directions: up, down, left, right, and 4 diagonals
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        
        queue<pair<int, int>> q;
        q.push({0, 0});
        grid[0][0] = 1; // Mark as visited (distance = 1)
        
        while(!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            int dist = grid[x][y];
            
            // If reached destination
            if(x == n-1 && y == n-1) {
                return dist;
            }
            
            // Explore all 8 directions
            for(int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                // Check bounds and if cell is clear
                if(nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                    grid[nx][ny] = dist + 1;
                    q.push({nx, ny});
                }
            }
        }
        
        return -1;
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<vector<int>> grid(n, vector<int>(n));
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    Solution obj;
    int result = obj.shortestPathBinaryMatrix(grid);
    
    if(result == -1) {
        cout << "No path exists" << endl;
    } else {
        cout << "Shortest path length: " << result << endl;
    }
    
    return 0;
}

// Time Complexity: O(n²)
// - Each cell is visited at most once: O(n²)
// - BFS traversal: O(n²)
// - Overall: O(n²)
//
// Space Complexity: O(n²)
// - Queue can contain at most O(n²) cells
// - Grid is modified in-place
// - Overall: O(n²)
//
// Explanation:
// This is a shortest path problem in a grid with 8-directional movement.
// We use BFS because all edges have unit weight (each move = 1 step).
//
// Algorithm:
// 1. Check if start or end is blocked (return -1)
// 2. Use BFS starting from (0, 0)
// 3. Mark visited cells with their distance from start
// 4. Explore all 8 directions from current cell
// 5. If we reach (n-1, n-1), return the distance
// 6. If BFS completes without reaching end, return -1
//
// Key Insight:
// - BFS guarantees shortest path in unweighted graphs
// - We can modify grid in-place to store distances (saves space)
// - 8-directional movement means we check all adjacent cells including diagonals
//
// Example:
// grid = [[0,0,0],
//         [1,1,0],
//         [1,1,0]]
// Path: (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2)
// Length: 5
