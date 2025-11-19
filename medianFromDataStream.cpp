#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
private:
    // Max-heap to store the smaller half of the numbers
    priority_queue<int> maxHeap;
    
    // Min-heap to store the larger half of the numbers
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    // Adds a number into the data structure.
    // Time Complexity: O(log n)
    void addNum(int num) {
        // Add to maxHeap first (smaller half)
        maxHeap.push(num);
        
        // Balance: Move largest of smaller half to larger half
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        
        // Maintain size property: maxHeap size >= minHeap size
        // If minHeap has more elements, move smallest of larger half back to maxHeap
        if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    // Returns the median of current data stream
    // Time Complexity: O(1)
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

/*
Problem: Find Median from Data Stream (LeetCode 295)

The median is the middle value in an ordered integer list. If the size of the list is even, 
there is no middle value and the median is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.

Implement the MedianFinder class:
- MedianFinder() initializes the MedianFinder object.
- void addNum(int num) adds the integer num from the data stream to the data structure.
- double findMedian() returns the median of all elements so far.

-----------------------------------------------------------
APPROACH: TWO HEAPS
-----------------------------------------------------------

Intuition:
To find the median, we need to access the middle element(s). 
If we split the data into two halves:
1. A "smaller half" containing elements <= median
2. A "larger half" containing elements >= median

We can efficiently access the largest of the smaller half and the smallest of the larger half.

Data Structures:
1. Max Heap (left side): Stores the smaller half of numbers. The top is the largest of the small numbers.
2. Min Heap (right side): Stores the larger half of numbers. The top is the smallest of the large numbers.

Invariants:
1. All elements in Max Heap <= All elements in Min Heap.
2. Size difference between heaps is at most 1.
   - If total elements N is odd, Max Heap has (N+1)/2 and Min Heap has (N-1)/2.
   - If total elements N is even, both have N/2.
   (We choose to keep the extra element in Max Heap if N is odd).

Algorithm:
addNum(num):
1. Add num to Max Heap.
2. Move the largest element from Max Heap to Min Heap (to ensure invariant 1).
3. If Min Heap has more elements than Max Heap, move the smallest from Min Heap back to Max Heap (to ensure invariant 2).

findMedian():
1. If Max Heap size > Min Heap size (odd total), median is Max Heap top.
2. If sizes are equal (even total), median is average of Max Heap top and Min Heap top.

Complexity:
- Time: 
  - addNum: O(log n) for heap insertions/deletions.
  - findMedian: O(1) to access heap tops.
- Space: O(n) to store all elements.

Example Trace:
addNum(1):
- maxHeap: [1]
- move 1 to minHeap -> minHeap: [1], maxHeap: []
- balance: minHeap > maxHeap -> move 1 to maxHeap
- State: maxHeap: [1], minHeap: []

addNum(2):
- maxHeap: [2, 1] (top is 2)
- move 2 to minHeap -> minHeap: [2], maxHeap: [1]
- balance: sizes equal (1, 1) -> OK
- State: maxHeap: [1], minHeap: [2]
- findMedian -> (1 + 2) / 2.0 = 1.5

addNum(3):
- maxHeap: [3, 1] (top is 3)
- move 3 to minHeap -> minHeap: [2, 3] (top is 2), maxHeap: [1]
- balance: minHeap (2) > maxHeap (1) -> move 2 to maxHeap
- State: maxHeap: [2, 1], minHeap: [3]
- findMedian -> maxHeap.top() = 2
*/
