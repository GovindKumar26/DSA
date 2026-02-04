// Non-Negative Integers without Consecutive Ones - LC 600
// Problem: Count integers from 0 to n with no consecutive 1s in binary.

#include <bits/stdc++.h>
using namespace std;

int findIntegers(int n) {
    string s = "";
    while (n > 0) {
        s = (char)('0' + n % 2) + s;
        n /= 2;
    }
    
    int k = s.size();
    vector<int> f(k);
    f[0] = 1;
    if (k > 1) f[1] = 2;
    for (int i = 2; i < k; i++) {
        f[i] = f[i-1] + f[i-2];
    }
    
    int result = 0;
    for (int i = 0; i < k; i++) {
        if (s[i] == '1') {
            result += f[k-1-i];
            if (i > 0 && s[i-1] == '1') return result;
        }
    }
    
    return result + 1;
}

int main() {
    int n = 5;
    cout << "Count: " << findIntegers(n) << endl;
    return 0;
}

// Time Complexity: O(log n)
// Space Complexity: O(log n)