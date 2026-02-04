// Digit DP Template
// Generic template for digit DP problems.

#include <bits/stdc++.h>
using namespace std;

/*
 * Standard Digit DP Template
 * 
 * Parameters:
 * - pos: current position in the number
 * - tight: whether current position is bounded by the limit
 * - state: problem-specific state (sum, count, etc.)
 * 
 * Returns: count of valid numbers satisfying the condition
 */

string num;
vector<vector<vector<int>>> dp;

int solve(int pos, bool tight, int state) {
    // Base case: processed all digits
    if (pos == num.size()) {
        // Check if state satisfies the condition
        return 1; // or check state
    }
    
    // Memoization
    if (dp[pos][tight][state] != -1) {
        return dp[pos][tight][state];
    }
    
    // Determine the upper limit for current digit
    int limit = tight ? (num[pos] - '0') : 9;
    int result = 0;
    
    // Try all possible digits
    for (int digit = 0; digit <= limit; digit++) {
        // Update state based on current digit
        int newState = state; // Update according to problem
        
        // Recurse
        result += solve(pos + 1, tight && (digit == limit), newState);
    }
    
    return dp[pos][tight][state] = result;
}

int countNumbers(int n) {
    num = to_string(n);
    int maxState = 100; // Adjust based on problem
    dp.assign(num.size(), vector<vector<int>>(2, vector<int>(maxState, -1)));
    
    return solve(0, true, 0);
}

int main() {
    int n = 100;
    cout << "Result: " << countNumbers(n) << endl;
    return 0;
}

/*
 * Common Digit DP Problems:
 * 1. Count numbers with digit sum in range
 * 2. Count numbers with no consecutive same digits
 * 3. Count numbers divisible by k with digit sum divisible by m
 * 4. Count numbers with at most k non-zero digits
 * 5. Count numbers without digit d
 * 
 * Key Points:
 * - tight constraint ensures we don't exceed the limit
 * - State tracks problem-specific information
 * - Memoization optimizes overlapping subproblems
 */