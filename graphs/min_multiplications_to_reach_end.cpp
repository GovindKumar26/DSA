// Minimum Steps to Reach End by Performing Multiplication and Mod Operations
// Problem: Given a start number, an end number, and an array of multipliers,
// find the minimum number of steps to reach end from start.
// In each step, you can multiply current number with any element from array and take mod 100000.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        const int MOD = 100000;
        
        if(start == end) return 0;
        
        // Queue: {number, steps}
        queue<pair<int, int>> q;
        q.push({start, 0});
        
        // Distance array to track minimum steps to reach each number
        vector<int> dist(MOD, INT_MAX);
        dist[start] = 0;
        
        while(!q.empty()) {
            auto [num, steps] = q.front();
            q.pop();
            
            // Try all multipliers
            for(int multiplier : arr) {
                int newNum = (num * multiplier) % MOD;
                
                // If reached end
                if(newNum == end) {
                    return steps + 1;
                }
                
                // If found a shorter path to newNum
                if(steps + 1 < dist[newNum]) {
                    dist[newNum] = steps + 1;
                    q.push({newNum, steps + 1});
                }
            }
        }
        
        return -1; // Cannot reach end
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int start, end;
    cin >> start >> end;
    
    Solution obj;
    int result = obj.minimumMultiplications(arr, start, end);
    
    if(result == -1) {
        cout << "Cannot reach end from start" << endl;
    } else {
        cout << "Minimum steps: " << result << endl;
    }
    
    return 0;
}

// Time Complexity: O(MOD × n)
// where MOD = 100000, n = size of multipliers array
// - Each number from 0 to MOD-1 can be visited at most once
// - For each number, we try all n multipliers
// - Overall: O(100000 × n)
//
// Space Complexity: O(MOD)
// - Distance array: O(100000)
// - Queue: O(100000) in worst case
// - Overall: O(100000)
//
// Explanation:
// This is a shortest path problem in an implicit graph where:
// - Nodes are numbers from 0 to 99999
// - Edges exist from num to (num × multiplier) % 100000 for each multiplier
// - We want shortest path from start to end
//
// Algorithm:
// 1. Use BFS to find shortest path (all edges have weight 1)
// 2. Start from 'start' number with 0 steps
// 3. For each number, try multiplying with all multipliers
// 4. Take modulo 100000 to get new number
// 5. If new number is end, return steps + 1
// 6. If we found shorter path to new number, add to queue
// 7. If BFS completes without reaching end, return -1
//
// Key Insight:
// - This is BFS on an implicit graph (graph not explicitly given)
// - Each multiplication is an edge with weight 1
// - BFS guarantees shortest path in unweighted graphs
// - We track visited numbers to avoid cycles
// - Modulo operation keeps numbers in range [0, 99999]
//
// Why BFS?
// - All edges have same weight (1 step per multiplication)
// - BFS finds shortest path in unweighted graphs
// - First time we reach 'end' is guaranteed to be via shortest path
//
// Example:
// arr = [2, 5, 7], start = 3, end = 30
// Step 0: 3
// Step 1: 3×2=6, 3×5=15, 3×7=21
// Step 2: From 15: 15×2=30 ✓
// Answer: 2
