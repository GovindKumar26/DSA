// Count of Integers - LC 2719
// Problem: Count integers in range with digit sum in given range.

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int solve(string& num, int minSum, int maxSum, int pos, int sum, bool tight, vector<vector<vector<int>>>& dp) {
    if (sum > maxSum) return 0;
    if (pos == num.size()) {
        return sum >= minSum ? 1 : 0;
    }
    
    if (dp[pos][sum][tight] != -1) return dp[pos][sum][tight];
    
    int limit = tight ? (num[pos] - '0') : 9;
    int result = 0;
    
    for (int digit = 0; digit <= limit; digit++) {
        result = (result + solve(num, minSum, maxSum, pos + 1, sum + digit, 
                               tight && (digit == limit), dp)) % MOD;
    }
    
    return dp[pos][sum][tight] = result;
}

int count(string num1, string num2, int min_sum, int max_sum) {
    vector<vector<vector<int>>> dp(23, vector<vector<int>>(401, vector<int>(2, -1)));
    int ans2 = solve(num2, min_sum, max_sum, 0, 0, true, dp);
    
    // Subtract 1 from num1
    int i = num1.size() - 1;
    while (i >= 0 && num1[i] == '0') {
        num1[i] = '9';
        i--;
    }
    if (i >= 0) num1[i]--;
    
    dp.assign(23, vector<vector<int>>(401, vector<int>(2, -1)));
    int ans1 = solve(num1, min_sum, max_sum, 0, 0, true, dp);
    
    return (ans2 - ans1 + MOD) % MOD;
}

int main() {
    cout << "Count: " << count("1", "12", 1, 8) << endl;
    return 0;
}

// Time Complexity: O(n * maxSum * 2)
// Space Complexity: O(n * maxSum * 2)