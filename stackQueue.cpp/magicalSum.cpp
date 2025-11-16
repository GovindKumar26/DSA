#include <bits/stdc++.h>
using namespace std;

class Solution {
    static constexpr long long MOD = 1'000'000'007LL;

    int n;
    int targetM;
    int targetK;
    vector<int> values;
    vector<vector<long long>> powerTable;
    vector<long long> fact;
    vector<long long> invFact;
    long long answer = 0;

    long long modPow(long long base, long long exp) {
        long long result = 1;
        while (exp > 0) {
            if (exp & 1LL) {
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            exp >>= 1LL;
        }
        return result;
    }

    long long comb(int total, int choose) {
        if (choose < 0 || choose > total) return 0;
        return (((fact[total] * invFact[choose]) % MOD) * invFact[total - choose]) % MOD;
    }

    void dfs(int idx, int remaining, long long carry, int bitCount,
             long long ways, long long product) {
        if (bitCount > targetK) return; // prune impossible branches

        if (idx == n) {
            if (remaining != 0) return;
            int totalBits = bitCount + __builtin_popcountll(carry);
            if (totalBits == targetK) {
                answer = (answer + (ways * product) % MOD) % MOD;
            }
            return;
        }

        for (int cnt = 0; cnt <= remaining; ++cnt) {
            long long total = carry + cnt;
            int bitHere = static_cast<int>(total & 1LL);
            long long nextCarry = total >> 1LL;
            long long nextWays = (ways * comb(remaining, cnt)) % MOD;
            long long nextProduct = (product * powerTable[idx][cnt]) % MOD;
            dfs(idx + 1, remaining - cnt, nextCarry, bitCount + bitHere, nextWays, nextProduct);
        }
    }

public:
    int magicalSum(int m, int k, vector<int>& nums) {
        targetM = m;
        targetK = k;
        values = nums;
        n = static_cast<int>(values.size());
        answer = 0;

        if (targetM == 0) {
            return (k == 0) ? 1 : 0;
        }

        fact.assign(targetM + 1, 1);
        for (int i = 1; i <= targetM; ++i) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }

        invFact.assign(targetM + 1, 1);
        invFact[targetM] = modPow(fact[targetM], MOD - 2);
        for (int i = targetM; i > 0; --i) {
            invFact[i - 1] = (invFact[i] * i) % MOD;
        }

        powerTable.assign(n, vector<long long>(targetM + 1, 1));
        for (int i = 0; i < n; ++i) {
            long long base = (static_cast<long long>(values[i]) % MOD + MOD) % MOD;
            for (int c = 1; c <= targetM; ++c) {
                powerTable[i][c] = (powerTable[i][c - 1] * base) % MOD;
            }
        }

        dfs(0, targetM, 0LL, 0, 1LL, 1LL);
        return static_cast<int>(answer % MOD);
    }
};
