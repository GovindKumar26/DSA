/*
================================================================================
                    COMMON HEAP PROBLEMS AND PATTERNS
================================================================================

This file contains solutions to common heap-based problems and patterns
that frequently appear in coding interviews and competitive programming.

COMMON PATTERNS:
---------------
1. Top K Elements (K largest/smallest)
2. K-way merge
3. Two heaps (median finding)
4. Scheduling problems
5. Frequency-based problems
6. Sliding window with heap

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// =============================================================================
//                  PROBLEM 1: KTH LARGEST ELEMENT
// =============================================================================

/*
Find the kth largest element in an unsorted array.

Approach 1: Sort - O(n log n)
Approach 2: Min Heap of size k - O(n log k) ✓
Approach 3: Max Heap - O(n + k log n)
Approach 4: QuickSelect - O(n) average

Using min heap of size k:
- Keep k largest elements in min heap
- Root is the kth largest
*/

int kthLargest(vector<int>& nums, int k) {
    // Min heap of size k
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int num : nums) {
        minHeap.push(num);
        
        // Maintain heap size = k
        if (minHeap.size() > k) {
            minHeap.pop(); // Remove smallest
        }
    }
    
    return minHeap.top(); // kth largest
}

// =============================================================================
//                  PROBLEM 2: KTH SMALLEST ELEMENT
// =============================================================================

int kthSmallest(vector<int>& nums, int k) {
    // Max heap of size k
    priority_queue<int> maxHeap;
    
    for (int num : nums) {
        maxHeap.push(num);
        
        if (maxHeap.size() > k) {
            maxHeap.pop(); // Remove largest
        }
    }
    
    return maxHeap.top(); // kth smallest
}

// =============================================================================
//                  PROBLEM 3: TOP K FREQUENT ELEMENTS
// =============================================================================

/*
Given an array, find k most frequent elements.

Approach:
1. Count frequencies using hash map
2. Use min heap of size k with (frequency, element) pairs
3. Maintain k most frequent elements
*/

vector<int> topKFrequent(vector<int>& nums, int k) {
    // Count frequencies
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }
    
    // Min heap: {frequency, number}
    auto cmp = [](pair<int,int>& a, pair<int,int>& b) {
        return a.first > b.first; // Min heap by frequency
    };
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> minHeap(cmp);
    
    for (auto& [num, count] : freq) {
        minHeap.push({count, num});
        
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    // Extract result
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    
    return result;
}

// =============================================================================
//                  PROBLEM 4: MERGE K SORTED ARRAYS
// =============================================================================

/*
Merge k sorted arrays into one sorted array.

Approach: Use min heap
- Store {value, array_index, element_index}
- Extract min and add next element from same array
Time: O(n log k) where n = total elements
*/

vector<int> mergeKSortedArrays(vector<vector<int>>& arrays) {
    // Min heap: {value, {array_idx, element_idx}}
    auto cmp = [](const pair<int, pair<int,int>>& a, 
                  const pair<int, pair<int,int>>& b) {
        return a.first > b.first;
    };
    priority_queue<pair<int, pair<int,int>>, 
                   vector<pair<int, pair<int,int>>>, 
                   decltype(cmp)> minHeap(cmp);
    
    // Initialize heap with first element of each array
    for (int i = 0; i < arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], {i, 0}});
        }
    }
    
    vector<int> result;
    
    while (!minHeap.empty()) {
        auto [val, indices] = minHeap.top();
        minHeap.pop();
        
        int arrIdx = indices.first;
        int elemIdx = indices.second;
        
        result.push_back(val);
        
        // Add next element from same array
        if (elemIdx + 1 < arrays[arrIdx].size()) {
            minHeap.push({arrays[arrIdx][elemIdx + 1], {arrIdx, elemIdx + 1}});
        }
    }
    
    return result;
}

// =============================================================================
//                  PROBLEM 5: FIND MEDIAN FROM DATA STREAM
// =============================================================================

/*
Design a data structure that supports:
1. addNum(num) - add number to stream
2. findMedian() - return median of all numbers so far

Approach: Two Heaps
- Max heap for smaller half
- Min heap for larger half
- Keep sizes balanced (differ by at most 1)
*/

class MedianFinder {
private:
    priority_queue<int> maxHeap; // Smaller half
    priority_queue<int, vector<int>, greater<int>> minHeap; // Larger half
    
public:
    MedianFinder() {}
    
    void addNum(int num) {
        // Add to max heap first
        maxHeap.push(num);
        
        // Balance: move largest from max to min
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        
        // Keep max heap size >= min heap size
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};

// =============================================================================
//            PROBLEM 6: SORT CHARACTERS BY FREQUENCY
// =============================================================================

string frequencySort(string s) {
    // Count frequencies
    unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    
    // Max heap by frequency
    auto cmp = [](pair<char, int>& a, pair<char, int>& b) {
        return a.second < b.second;
    };
    priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> maxHeap(cmp);
    
    for (auto& p : freq) {
        maxHeap.push(p);
    }
    
    // Build result
    string result = "";
    while (!maxHeap.empty()) {
        auto [ch, count] = maxHeap.top();
        maxHeap.pop();
        result += string(count, ch);
    }
    
    return result;
}

// =============================================================================
//            PROBLEM 7: REORGANIZE STRING (NO ADJACENT DUPLICATES)
// =============================================================================

/*
Rearrange string so no two adjacent characters are same.
Return "" if impossible.

Approach:
- Use max heap by frequency
- Always pick most frequent character available
- Use previous character to avoid adjacent duplicates
*/

string reorganizeString(string s) {
    // Count frequencies
    unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
        // If any character appears more than (n+1)/2 times, impossible
        if (freq[c] > (s.length() + 1) / 2) {
            return "";
        }
    }
    
    // Max heap by frequency
    priority_queue<pair<int, char>> maxHeap;
    for (auto& [ch, count] : freq) {
        maxHeap.push({count, ch});
    }
    
    string result = "";
    pair<int, char> prev = {-1, '#'}; // Previous character
    
    while (!maxHeap.empty()) {
        auto [count, ch] = maxHeap.top();
        maxHeap.pop();
        
        result += ch;
        
        // Add previous back to heap if it has remaining count
        if (prev.first > 0) {
            maxHeap.push(prev);
        }
        
        // Update previous
        count--;
        prev = {count, ch};
    }
    
    return result.length() == s.length() ? result : "";
}

// =============================================================================
//            PROBLEM 8: K CLOSEST POINTS TO ORIGIN
// =============================================================================

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    // Max heap by distance
    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first; // Max heap
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> maxHeap(cmp);
    
    for (int i = 0; i < points.size(); i++) {
        int dist = points[i][0] * points[i][0] + points[i][1] * points[i][1];
        maxHeap.push({dist, i});
        
        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
    }
    
    vector<vector<int>> result;
    while (!maxHeap.empty()) {
        int idx = maxHeap.top().second;
        maxHeap.pop();
        result.push_back(points[idx]);
    }
    
    return result;
}

// =============================================================================
//                          DEMONSTRATION
// =============================================================================

void demonstrateKthLargest() {
    cout << "=== KTH LARGEST ELEMENT ===" << endl;
    vector<int> arr = {3, 2, 1, 5, 6, 4};
    int k = 2;
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nk = " << k << endl;
    cout << "Kth largest: " << kthLargest(arr, k) << endl;
    cout << "Kth smallest: " << kthSmallest(arr, k) << endl;
}

void demonstrateTopKFrequent() {
    cout << "\n=== TOP K FREQUENT ELEMENTS ===" << endl;
    vector<int> arr = {1, 1, 1, 2, 2, 3};
    int k = 2;
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nk = " << k << endl;
    
    vector<int> result = topKFrequent(arr, k);
    cout << "Top " << k << " frequent: ";
    for (int x : result) cout << x << " ";
    cout << endl;
}

void demonstrateMergeKArrays() {
    cout << "\n=== MERGE K SORTED ARRAYS ===" << endl;
    vector<vector<int>> arrays = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    
    cout << "Arrays:" << endl;
    for (auto& arr : arrays) {
        cout << "  ";
        for (int x : arr) cout << x << " ";
        cout << endl;
    }
    
    vector<int> merged = mergeKSortedArrays(arrays);
    cout << "Merged: ";
    for (int x : merged) cout << x << " ";
    cout << endl;
}

void demonstrateMedianFinder() {
    cout << "\n=== MEDIAN FROM DATA STREAM ===" << endl;
    MedianFinder mf;
    
    vector<int> stream = {5, 15, 1, 3, 8};
    cout << "Stream: ";
    for (int num : stream) {
        cout << num << " ";
        mf.addNum(num);
        cout << "[median=" << mf.findMedian() << "] ";
    }
    cout << endl;
}

void demonstrateFrequencySort() {
    cout << "\n=== SORT BY FREQUENCY ===" << endl;
    string s = "tree";
    cout << "Input: " << s << endl;
    cout << "Output: " << frequencySort(s) << endl;
}

void demonstrateReorganizeString() {
    cout << "\n=== REORGANIZE STRING ===" << endl;
    vector<string> tests = {"aab", "aaab", "vvvlo"};
    
    for (string s : tests) {
        cout << "Input: " << s << endl;
        string result = reorganizeString(s);
        cout << "Output: " << (result.empty() ? "impossible" : result) << endl;
    }
}

int main() {
    demonstrateKthLargest();
    demonstrateTopKFrequent();
    demonstrateMergeKArrays();
    demonstrateMedianFinder();
    demonstrateFrequencySort();
    demonstrateReorganizeString();
    
    return 0;
}

/*
COMMON HEAP PATTERNS SUMMARY:
-----------------------------

1. TOP K ELEMENTS:
   - Use min heap of size k for k largest
   - Use max heap of size k for k smallest
   
2. K-WAY MERGE:
   - Use min heap with {value, source, index}
   - Extract min and add next from same source
   
3. TWO HEAPS (Median):
   - Max heap for smaller half
   - Min heap for larger half
   - Balance sizes
   
4. FREQUENCY BASED:
   - Count frequencies first
   - Use heap with custom comparator
   
5. CLOSEST/FARTHEST:
   - Calculate distance/metric
   - Use opposite heap (max for closest)
   
6. REORGANIZE/SCHEDULE:
   - Use frequency/deadline in heap
   - Greedy selection with constraints

TIME COMPLEXITIES:
- Insert: O(log n)
- Extract: O(log n)
- Top: O(1)
- Build heap: O(n)
*/
