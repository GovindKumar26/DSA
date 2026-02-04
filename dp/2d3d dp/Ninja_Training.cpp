// Ninja Training (DP-7)
// Problem: Maximum points in n days. Each day choose from 3 activities, but can't repeat same activity.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Recursion with Memoization
// TC: O(n*4*3), SC: O(n*4) + O(n) stack space
int solve(int day, int last, vector<vector<int>>& points, vector<vector<int>>& dp) {
    if (day == 0) {
        int maxi = 0;
        for (int task = 0; task < 3; task++) {
            if (task != last) {
                maxi = max(maxi, points[0][task]);
            }
        }
        return maxi;
    }
    
    if (dp[day][last] != -1) return dp[day][last];
    
    int maxi = 0;
    for (int task = 0; task < 3; task++) {
        if (task != last) {
            int point = points[day][task] + solve(day-1, task, points, dp);
            maxi = max(maxi, point);
        }
    }
    
    return dp[day][last] = maxi;
}

int ninjaTrainingMemo(int n, vector<vector<int>>& points) {
    vector<vector<int>> dp(n, vector<int>(4, -1));
    return solve(n-1, 3, points, dp); // 3 means no activity done yet
}

// Approach 2: Tabulation
// TC: O(n*4*3), SC: O(n*4)
int ninjaTrainingTabulation(int n, vector<vector<int>>& points) {
    vector<vector<int>> dp(n, vector<int>(4, 0));
    
    // Base case: day 0
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max({points[0][0], points[0][1], points[0][2]});
    
    for (int day = 1; day < n; day++) {
        for (int last = 0; last < 4; last++) {
            dp[day][last] = 0;
            for (int task = 0; task < 3; task++) {
                if (task != last) {
                    int point = points[day][task] + dp[day-1][task];
                    dp[day][last] = max(dp[day][last], point);
                }
            }
        }
    }
    
    return dp[n-1][3];
}

// Approach 3: Space Optimized
// TC: O(n*4*3), SC: O(4)
int ninjaTrainingOptimized(int n, vector<vector<int>>& points) {
    vector<int> prev(4, 0);
    
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max({points[0][0], points[0][1], points[0][2]});
    
    for (int day = 1; day < n; day++) {
        vector<int> curr(4, 0);
        for (int last = 0; last < 4; last++) {
            for (int task = 0; task < 3; task++) {
                if (task != last) {
                    curr[last] = max(curr[last], points[day][task] + prev[task]);
                }
            }
        }
        prev = curr;
    }
    
    return prev[3];
}

int main() {
    vector<vector<int>> points = {{10, 40, 70}, {20, 50, 80}, {30, 60, 90}};
    int n = points.size();
    cout << "Maximum points: " << ninjaTrainingOptimized(n, points) << endl;
    return 0;
}

// Time Complexity: O(n*12) ≈ O(n)
// Space Complexity: O(4) ≈ O(1) for optimized