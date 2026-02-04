// Evaluate Boolean Expression to True (DP-52)
// Problem: Count ways to parenthesize expression to evaluate to true.

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1003;

// Memoization
long long solve(int i, int j, int isTrue, string& exp, vector<vector<vector<long long>>>& dp) {
    if (i > j) return 0;
    if (i == j) {
        if (isTrue) return exp[i] == 'T';
        else return exp[i] == 'F';
    }
    
    if (dp[i][j][isTrue] != -1) return dp[i][j][isTrue];
    
    long long ways = 0;
    for (int k = i+1; k <= j-1; k += 2) {
        long long lT = solve(i, k-1, 1, exp, dp);
        long long lF = solve(i, k-1, 0, exp, dp);
        long long rT = solve(k+1, j, 1, exp, dp);
        long long rF = solve(k+1, j, 0, exp, dp);
        
        if (exp[k] == '&') {
            if (isTrue) ways = (ways + (lT * rT) % MOD) % MOD;
            else ways = (ways + (lF * rT) % MOD + (lT * rF) % MOD + (lF * rF) % MOD) % MOD;
        } else if (exp[k] == '|') {
            if (isTrue) ways = (ways + (lT * rT) % MOD + (lF * rT) % MOD + (lT * rF) % MOD) % MOD;
            else ways = (ways + (lF * rF) % MOD) % MOD;
        } else { // XOR
            if (isTrue) ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD) % MOD;
            else ways = (ways + (lT * rT) % MOD + (lF * rF) % MOD) % MOD;
        }
    }
    
    return dp[i][j][isTrue] = ways;
}

int evaluateExp(string& exp) {
    int n = exp.size();
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, -1)));
    return solve(0, n-1, 1, exp, dp);
}

int main() {
    string exp = "T|T&F^T";
    cout << "Ways to evaluate to true: " << evaluateExp(exp) << endl;
    return 0;
}

// Time Complexity: O(n^3)
// Space Complexity: O(n^2)