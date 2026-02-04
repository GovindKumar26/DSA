// Numbers At Most N Given Digit Set - LC 902
// Problem: Count numbers <= n using given digit set.

#include <bits/stdc++.h>
using namespace std;

int atMostNGivenDigitSet(vector<string>& digits, int n) {
    string S = to_string(n);
    int K = S.size();
    int D = digits.size();
    
    // Count numbers with fewer digits
    int result = 0;
    for (int i = 1; i < K; i++) {
        result += pow(D, i);
    }
    
    // Count numbers with K digits
    for (int i = 0; i < K; i++) {
        bool hasSameNum = false;
        for (string& d : digits) {
            if (d[0] < S[i]) {
                result += pow(D, K - i - 1);
            } else if (d[0] == S[i]) {
                hasSameNum = true;
            }
        }
        if (!hasSameNum) return result;
    }
    
    return result + 1; // +1 for n itself
}

int main() {
    vector<string> digits = {"1", "3", "5", "7"};
    int n = 100;
    cout << "Count: " << atMostNGivenDigitSet(digits, n) << endl;
    return 0;
}

// Time Complexity: O(log n * D)
// Space Complexity: O(1)