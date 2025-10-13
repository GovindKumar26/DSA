#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long dpSingle[20][2][2]; // pos, tight, leading
    string num;

    long long dfsSingle(int pos, bool tight, bool leading) {
        if (pos == static_cast<int>(num.size())) {
            return leading ? 0 : 1; // exclude all-zero number
        }
        long long &res = dpSingle[pos][tight ? 1 : 0][leading ? 1 : 0];
        if (res != -1) return res;

        int limit = tight ? (num[pos] - '0') : 9;
        long long ans = 0;

        for (int d = 0; d <= limit; ++d) {
            bool nextLeading = leading && d == 0;
            bool nextTight = tight && (d == limit);

            if (nextLeading) {
                ans += dfsSingle(pos + 1, nextTight, true);
            } else if (d != 0) {
                ans += dfsSingle(pos + 1, nextTight, false);
            }
        }
        return res = ans;
    }

    long long countNoZeroNumbers(long long n) {
        if (n <= 0) return 0;
        num = to_string(n);
        memset(dpSingle, -1, sizeof(dpSingle));
        return dfsSingle(0, true, true);
    }

    long long dpPair[20][2][2][2]; // pos, carry, leadingA, leadingB
    vector<int> digitsReversed;

    long long dfsPair(int pos, int carry, bool leadingA, bool leadingB) {
        if (pos == static_cast<int>(digitsReversed.size())) {
            return (carry == 0 && !leadingA && !leadingB) ? 1 : 0;
        }
        long long &res = dpPair[pos][carry][leadingA ? 1 : 0][leadingB ? 1 : 0];
        if (res != -1) return res;

        int target = digitsReversed[pos];
        long long ans = 0;

        for (int da = 0; da <= 9; ++da) {
            bool nextLeadingA = leadingA && da == 0;
            if (!nextLeadingA && da == 0) continue;

            for (int db = 0; db <= 9; ++db) {
                bool nextLeadingB = leadingB && db == 0;
                if (!nextLeadingB && db == 0) continue;

                int sum = da + db + carry;
                if (sum % 10 != target) continue;

                int nextCarry = sum / 10;
                ans += dfsPair(pos + 1, nextCarry, nextLeadingA, nextLeadingB);
            }
        }
        return res = ans;
    }

    long long countNoZeroPairs(long long n) {
        if (n <= 0) return 0;
        digitsReversed.clear();
        while (n > 0) {
            digitsReversed.push_back(static_cast<int>(n % 10));
            n /= 10;
        }
        memset(dpPair, -1, sizeof(dpPair));
        return dfsPair(0, 0, true, true);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    if (!(cin >> n)) return 0;

    Solution solver;
    cout << solver.countNoZeroPairs(n) << '\n';
    return 0;
}
