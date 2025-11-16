#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Approach 1: Using Min Heap (Priority Queue)
    // Time: O(N*k*log(k)) where N is total elements, k is number of arrays
    // Space: O(k) for heap
    vector<int> mergeKArrays(vector<vector<int>>& arr, int k) {
        vector<int> result;
        
        // Min heap: {value, {array_index, element_index}}
        priority_queue<pair<int, pair<int, int>>, 
                       vector<pair<int, pair<int, int>>>, 
                       greater<pair<int, pair<int, int>>>> minHeap;
        
        // Insert first element of each array into heap
        for (int i = 0; i < k; i++) {
            if (!arr[i].empty()) {
                minHeap.push({arr[i][0], {i, 0}});
            }
        }
        
        // Extract min and insert next element from same array
        while (!minHeap.empty()) {
            auto curr = minHeap.top();
            minHeap.pop();
            
            int value = curr.first;
            int arrayIdx = curr.second.first;
            int elemIdx = curr.second.second; 
            
            result.push_back(value);
            
            // If there's a next element in the same array, add it to heap
            if (elemIdx + 1 < arr[arrayIdx].size()) {
                minHeap.push({arr[arrayIdx][elemIdx + 1], {arrayIdx, elemIdx + 1}});
            }
        }
        
        return result;
    }
    
    // Approach 2: Divide and Conquer (Merge pairs recursively)
    // Time: O(N*k*log(k)) where N is avg array size
    // Space: O(N*k) for temporary arrays
    vector<int> mergeKArraysDivideConquer(vector<vector<int>>& arr, int k) {
        if (k == 0) return {};
        if (k == 1) return arr[0];
        
        return mergeKHelper(arr, 0, k - 1);
    }
    
private:
    vector<int> mergeKHelper(vector<vector<int>>& arr, int left, int right) {
        if (left == right) {
            return arr[left];
        }
        
        if (left + 1 == right) {
            return mergeTwoArrays(arr[left], arr[right]);
        }
        
        int mid = left + (right - left) / 2;
        vector<int> leftMerged = mergeKHelper(arr, left, mid);
        vector<int> rightMerged = mergeKHelper(arr, mid + 1, right);
        
        return mergeTwoArrays(leftMerged, rightMerged);
    }
    
    vector<int> mergeTwoArrays(vector<int>& a, vector<int>& b) {
        vector<int> result;
        int i = 0, j = 0;
        
        while (i < a.size() && j < b.size()) {
            if (a[i] <= b[j]) {
                result.push_back(a[i++]);
            } else {
                result.push_back(b[j++]);
            }
        }
        
        while (i < a.size()) result.push_back(a[i++]);
        while (j < b.size()) result.push_back(b[j++]);
        
        return result;
    }
    
public:
    // Approach 3: Using custom comparator with indices
    // Most concise version
    vector<int> mergeKArraysClean(vector<vector<int>>& arr, int k) {
        vector<int> result;
        
        // {value, arrayIdx, elemIdx}
        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            return a[0] > b[0]; // min heap
        };
        
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        
        // Push first element of each array
        for (int i = 0; i < k; i++) {
            if (!arr[i].empty()) {
                pq.push({arr[i][0], i, 0});
            }
        }
        
        while (!pq.empty()) {
            vector<int> curr = pq.top();
            pq.pop();
            
            result.push_back(curr[0]);
            
            int arrayIdx = curr[1];
            int elemIdx = curr[2];
            
            if (elemIdx + 1 < arr[arrayIdx].size()) {
                pq.push({arr[arrayIdx][elemIdx + 1], arrayIdx, elemIdx + 1});
            }
        }
        
        return result;
    }
};

/*
Problem: Merge K Sorted Arrays
Given K sorted arrays arranged in the form of a matrix of size K*N. 
The task is to merge them into one sorted array.

Example 1:
Input: K = 3, N = 4
arr[][] = {{1,2,3,4},
           {2,2,3,4},
           {5,5,6,6}}
Output: 1 2 2 2 3 3 4 4 5 5 6 6

Example 2:
Input: K = 3, N = 4
arr[][] = {{1,3,5,7},
           {2,4,6,8},
           {0,9,10,11}}
Output: 0 1 2 3 4 5 6 7 8 9 10 11

Constraints:
1 <= K <= 100
1 <= N <= 100

-----------------------------------------------------------
APPROACH COMPARISON:
-----------------------------------------------------------

1. Min Heap Approach (RECOMMENDED):
   - Use priority queue with k elements at most
   - Keep track of which array and which index
   - Time: O(N*k * log(k))
   - Space: O(k)
   - Best for: Memory efficiency

2. Divide and Conquer:
   - Merge arrays in pairs recursively
   - Like merge sort on arrays
   - Time: O(N*k * log(k))
   - Space: O(N*k) for temporary arrays
   - Best for: When heap operations are expensive

3. Brute Force (Not implemented):
   - Concatenate all + sort
   - Time: O(N*k * log(N*k))
   - Space: O(N*k)
   - Simplest but inefficient

-----------------------------------------------------------
KEY INSIGHTS:
-----------------------------------------------------------
- At any point, next smallest element must be at front of one of the k arrays
- Min heap maintains k candidates (one from each array)
- Extract min, replace with next element from same array
- Process continues until all elements consumed

-----------------------------------------------------------
*/
