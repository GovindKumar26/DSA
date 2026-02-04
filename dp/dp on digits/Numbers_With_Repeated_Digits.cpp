// Numbers With Repeated Digits - LC 1012
// Problem: Count numbers with at least one repeated digit from 1 to n.

#include <bits/stdc++.h>
using namespace std;

int numDupDigitsAtMostN(int n) {
    // Count numbers without repeated digits, then subtract from n
    vector<int> digits;
    int temp = n + 1;
    while (temp > 0) {
        digits.push_back(temp % 10);
        temp /= 10;
    }
    reverse(digits.begin(), digits.end());
    
    int k = digits.size();
    int count = 0;
    
    // Count numbers with fewer digits (all have unique digits)
    for (int i = 1; i < k; i++) {
        int c = 9; // First digit: 1-9
        for (int j = 1; j < i; j++) {
            c *= (10 - j);
        }
        count += c;
    }
    
    // Count k-digit numbers with unique digits
    unordered_set<int> used;
    for (int i = 0; i < k; i++) {
        int cnt = 0;
        for (int d = (i == 0 ? 1 : 0); d < digits[i]; d++) {
            if (used.find(d) == used.end()) {
                cnt++;
            }
        }
        
        // Multiply by permutations of remaining positions
        int mul = 1;
        for (int j = 0; j < k - i - 1; j++) {
            mul *= (10 - used.size() - 1 - j);
        }
        count += cnt * mul;
        
        if (used.find(digits[i]) != used.end()) break;
        used.insert(digits[i]);
    }
    
    return n - count;
}

int main() {
    int n = 20;
    cout << "Numbers with repeated digits: " << numDupDigitsAtMostN(n) << endl;
    return 0;
}

// Time Complexity: O((log n)^2)
// Space Complexity: O(log n)