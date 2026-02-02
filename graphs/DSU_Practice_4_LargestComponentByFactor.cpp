// LeetCode 952: Largest Component Size by Common Factor - HARD
// Problem: Given an array of unique positive integers, find the size of the 
// largest connected component where two integers are connected if they share 
// a common factor greater than 1.

#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, size;
    
public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int node) {
        if(node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }
    
    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU == rootV) return;
        
        if(size[rootU] < size[rootV]) {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        } else {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }
    
    int getSize(int node) {
        return size[find(node)];
    }
};

class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        DSU dsu(n);
        
        // Map: prime factor -> first index having this factor
        unordered_map<int, int> factorToIndex;
        
        for(int i = 0; i < n; i++) {
            int num = nums[i];
            
            // Find all prime factors of nums[i]
            for(int factor = 2; factor * factor <= num; factor++) {
                if(num % factor == 0) {
                    // Found a factor
                    if(factorToIndex.count(factor)) {
                        // Connect with first occurrence of this factor
                        dsu.unite(i, factorToIndex[factor]);
                    } else {
                        factorToIndex[factor] = i;
                    }
                    
                    // Divide out all occurrences of this factor
                    while(num % factor == 0) {
                        num /= factor;
                    }
                }
            }
            
            // If num > 1, then it's a prime factor itself
            if(num > 1) {
                if(factorToIndex.count(num)) {
                    dsu.unite(i, factorToIndex[num]);
                } else {
                    factorToIndex[num] = i;
                }
            }
        }
        
        // Find maximum component size
        int maxSize = 0;
        for(int i = 0; i < n; i++) {
            maxSize = max(maxSize, dsu.getSize(i));
        }
        
        return maxSize;
    }
};

/*
═══════════════════════════════════════════════════════════════════
INTUITION:
═══════════════════════════════════════════════════════════════════
Two numbers are connected if they share a common factor > 1.
This means they share at least one prime factor.

Strategy: Use prime factors as bridges
- If two numbers share a prime factor p, they're in same component
- Map each prime factor to the first index that has it
- When we find a number with factor p, union it with the first number
  that had factor p

EXAMPLE:
nums = [4, 6, 15, 35]
- 4 = 2²: factor 2 -> maps to index 0
- 6 = 2·3: factor 2 (union with 0), factor 3 -> maps to index 1
- 15 = 3·5: factor 3 (union with 1), factor 5 -> maps to index 2
- 35 = 5·7: factor 5 (union with 2), factor 7 -> maps to index 3

Components: {0,1,2,3} all connected via transitive factors
Answer: 4

WHY PRIME FACTORIZATION?
- If a and b share any common factor f > 1, they share at least one prime
- Using primes avoids redundant connections
- More efficient than checking all pairs

ALGORITHM:
1. For each number, find all its prime factors
2. For each prime factor:
   - If seen before, union current index with first index having this prime
   - Otherwise, record this as first occurrence
3. Find maximum component size

COMPLEXITY:
Time: O(n·√m) where m = max(nums)
  - For each number: O(√m) to factorize
Space: O(n + p) where p = number of unique primes

OPTIMIZATION:
Instead of trial division up to √num, could use sieve for better performance.
═══════════════════════════════════════════════════════════════════
*/

int main() {
    Solution sol;
    
    vector<int> nums1 = {4, 6, 15, 35};
    cout << "Test 1: " << sol.largestComponentSize(nums1) << endl;
    // Expected: 4 (all connected: 4-6 via 2, 6-15 via 3, 15-35 via 5)
    
    vector<int> nums2 = {20, 50, 9, 63};
    cout << "Test 2: " << sol.largestComponentSize(nums2) << endl;
    // Expected: 2 (9-63 via 3, or 20-50 via 2/5)
    
    vector<int> nums3 = {2, 3, 6, 7, 4, 12, 21, 39};
    cout << "Test 3: " << sol.largestComponentSize(nums3) << endl;
    // Expected: 8 (all connected transitively)
    
    return 0;
}
