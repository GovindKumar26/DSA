// Count Numbers with Unique Digits - LC 357
// Problem: Count numbers with unique digits from 0 to 10^n.

#include <bits/stdc++.h>
using namespace std;

int countNumbersWithUniqueDigits(int n) {
    if (n == 0) return 1;
    if (n == 1) return 10;
    
    int result = 10;
    int uniqueDigits = 9;
    int availableNumbers = 9;
    
    for (int i = 2; i <= n && availableNumbers > 0; i++) {
        uniqueDigits *= availableNumbers;
        result += uniqueDigits;
        availableNumbers--;
    }
    
    return result;
}

int main() {
    int n = 2;
    cout << "Count: " << countNumbersWithUniqueDigits(n) << endl;
    return 0;
}

// Time Complexity: O(n)
// Space Complexity: O(1)