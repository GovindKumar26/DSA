#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Time: O(N log N + K log K), Space: O(N + K)
    vector<int> maxCombinations(int N, int K, vector<int>& A, vector<int>& B) {
        // Sort both arrays in descending order
        sort(A.begin(), A.end(), greater<int>());
        sort(B.begin(), B.end(), greater<int>());
        
        // Max heap: {sum, {i, j}}
        priority_queue<pair<int, pair<int, int>>> maxHeap;
        set<pair<int, int>> visited;
        
        // Start with the largest possible sum
        maxHeap.push({A[0] + B[0], {0, 0}});
        visited.insert({0, 0});
        
        vector<int> result;
        while (K-- && !maxHeap.empty()) {
            auto curr = maxHeap.top();
            maxHeap.pop();
            int sum = curr.first;
            int i = curr.second.first;
            int j = curr.second.second;
            result.push_back(sum);
            
            // Next pair (i+1, j)
            if (i + 1 < N && visited.find({i + 1, j}) == visited.end()) {
                maxHeap.push({A[i + 1] + B[j], {i + 1, j}});
                visited.insert({i + 1, j});
            }
            // Next pair (i, j+1)
            if (j + 1 < N && visited.find({i, j + 1}) == visited.end()) {
                maxHeap.push({A[i] + B[j + 1], {i, j + 1}});
                visited.insert({i, j + 1});
            }
        }
        return result;
    }
};

/*
Problem: Maximum Sum Combination
Given two integer arrays A and B of size N each, and an integer K, return the top K maximum sum combinations from all the possible sum combinations.

Example:
Input: N = 2, K = 2, A = [3,2], B = [1,4]
Output: [7, 6]
Explanation: The possible combinations are (3+4=7), (3+1=4), (2+4=6), (2+1=3). The top 2 are 7 and 6.

Constraints:
- 1 <= N <= 10^5
- 1 <= K <= N
- -10^6 <= A[i], B[i] <= 10^6

Approach:
- Sort both arrays in descending order
- Use a max heap to always pick the next largest sum
- Use a set to avoid duplicate index pairs
- At each step, push the next two possible pairs (i+1, j) and (i, j+1)
- Repeat K times
*/
