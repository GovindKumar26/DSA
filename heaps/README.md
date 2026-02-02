# Heaps - Complete Learning Guide

## Overview
This folder contains comprehensive implementations and explanations of heap data structures, their operations, and common problems.

## Files Structure

### 1. **01_heap_basics.cpp**
- **What you'll learn:**
  - What is a heap and why use it
  - Binary heap properties
  - Array representation of heaps
  - Max heap and min heap implementations
  - Basic operations: insert, extract, getTop
  - Time and space complexities

- **Key Concepts:**
  - Parent/child index relationships
  - Heapify up (bubble up) for insertions
  - Heapify down (bubble down) for deletions
  - Complete binary tree property

### 2. **02_heapify_operations.cpp**
- **What you'll learn:**
  - Heapify up vs heapify down
  - Build heap from array in O(n)
  - Why build heap is O(n), not O(n log n)
  - Recursive and iterative heapify
  - Step-by-step visualization

- **Key Concepts:**
  - Bottom-up heapification
  - Last non-leaf node: (n/2 - 1)
  - Height-based complexity analysis

### 3. **03_priority_queue.cpp**
- **What you'll learn:**
  - Priority queue abstract data type
  - Implementation using heaps
  - C++ STL priority_queue usage
  - Custom comparators
  - Priority queue with custom objects

- **Applications:**
  - Task scheduling
  - Dijkstra's algorithm
  - Event-driven simulation
  - A* pathfinding

### 4. **04_check_if_array_is_heap.cpp**
- **What you'll learn:**
  - Verify max heap property
  - Verify min heap property
  - Check complete binary tree
  - Iterative vs recursive approaches
  - Detailed explanation of why array is/isn't a heap

- **Key Concepts:**
  - Only check non-leaf nodes
  - Heap verification in O(n) time
  - Edge cases handling

### 5. **05_convert_min_max_heap.cpp**
- **What you'll learn:**
  - Convert min heap to max heap
  - Convert max heap to min heap
  - In-place conversion in O(n)
  - Step-by-step conversion trace
  - Why we can't just reverse the array

- **Key Concepts:**
  - Reheapification technique
  - Bottom-up approach
  - Maintaining complete binary tree structure

### 6. **06_heap_sort.cpp**
- **What you'll learn:**
  - Heap sort algorithm
  - Building max/min heap for sorting
  - In-place sorting
  - Ascending and descending order
  - Finding k largest/smallest elements

- **Characteristics:**
  - Time: O(n log n) guaranteed
  - Space: O(1) - in-place
  - Not stable
  - Comparison with other sorting algorithms

### 7. **07_common_heap_problems.cpp**
- **Problems covered:**
  1. Kth largest/smallest element
  2. Top K frequent elements
  3. Merge K sorted arrays
  4. Find median from data stream
  5. Sort characters by frequency
  6. Reorganize string (no adjacent duplicates)
  7. K closest points to origin

- **Patterns:**
  - Top K elements pattern
  - K-way merge pattern
  - Two heaps pattern
  - Frequency-based problems

## Key Concepts Summary

### Heap Properties
```
MAX HEAP: Parent >= Children
MIN HEAP: Parent <= Children
COMPLETE BINARY TREE: All levels filled except last (left to right)
```

### Array Representation (0-indexed)
```
Parent of i:     (i-1)/2
Left child of i:  2*i + 1
Right child of i: 2*i + 2
```

### Time Complexities
| Operation | Time Complexity |
|-----------|----------------|
| Insert | O(log n) |
| Extract Min/Max | O(log n) |
| Get Min/Max | O(1) |
| Build Heap | O(n) |
| Heapify | O(log n) |
| Heap Sort | O(n log n) |

### Space Complexity
- Array-based heap: O(n)
- Heap operations: O(1) extra space
- Recursive heapify: O(log n) call stack

## Common Patterns

### 1. Top K Elements
```cpp
// Use min heap for K largest
priority_queue<int, vector<int>, greater<int>> minHeap;
for (int num : nums) {
    minHeap.push(num);
    if (minHeap.size() > k) minHeap.pop();
}
```

### 2. K-Way Merge
```cpp
// Merge K sorted lists/arrays
priority_queue<Node, vector<Node>, Compare> pq;
// Add first element from each list
// Extract min, add next from same list
```

### 3. Two Heaps (Median)
```cpp
// Max heap for smaller half, min heap for larger half
priority_queue<int> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;
// Keep sizes balanced
```

### 4. Frequency Based
```cpp
// Count frequencies, use heap with custom comparator
unordered_map<T, int> freq;
priority_queue<pair<int, T>> pq; // {frequency, element}
```

## When to Use Heaps

### Use Heaps When:
- Need to repeatedly find min/max element
- Implementing priority queue
- Finding top K elements
- Merging K sorted sequences
- Maintaining running median
- Task scheduling based on priority

### Don't Use Heaps When:
- Need to search for arbitrary elements (use hash table)
- Need sorted order of all elements (use sorting)
- Need to access middle elements (use balanced BST)
- Simple min/max of static array (use linear scan)

## C++ STL Priority Queue

### Basic Usage
```cpp
// Max heap (default)
priority_queue<int> maxHeap;

// Min heap
priority_queue<int, vector<int>, greater<int>> minHeap;

// Custom comparator
auto cmp = [](const T& a, const T& b) { return a.priority < b.priority; };
priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);
```

### Common Operations
```cpp
pq.push(element);      // Insert - O(log n)
pq.pop();             // Remove top - O(log n)
pq.top();             // Access top - O(1)
pq.size();            // Get size - O(1)
pq.empty();           // Check if empty - O(1)
```

## Interview Tips

### Common Questions
1. **Explain heap property** - Parent-child relationship
2. **Why use heap over array?** - O(log n) vs O(n) operations
3. **Build heap complexity** - O(n), not O(n log n)
4. **Heap vs BST** - Heap: faster insert/delete, BST: faster search
5. **Stable heap sort?** - No, heap sort is not stable

### Common Mistakes
- Forgetting to check child index bounds
- Wrong parent/child index calculation
- Not starting from last non-leaf node in build heap
- Using max heap when min heap is needed (or vice versa)
- Forgetting to maintain heap size in top-K problems

## Practice Problems

### Easy
- Kth largest element in array
- Last stone weight
- Relative ranks

### Medium
- Top K frequent elements
- K closest points to origin
- Task scheduler
- Merge K sorted lists
- Find median from data stream
- Reorganize string

### Hard
- Sliding window median
- Find median in data stream with duplicates
- Merge K sorted arrays
- IPO (maximum capital)

## Compilation and Running

```bash
# Compile any file
g++ -std=c++17 filename.cpp -o output

# Run
./output
```

## Additional Resources

### Related Topics
- Binary Trees
- Sorting Algorithms
- Priority Queues
- Graph Algorithms (Dijkstra, Prim's)
- Greedy Algorithms

### Further Reading
- Introduction to Algorithms (CLRS) - Chapter 6
- Algorithm Design Manual - Heap section
- LeetCode Heap tag problems
- GeeksforGeeks Heap articles

---

**Note:** Each file contains detailed comments, multiple examples, edge cases, and step-by-step explanations. Start with `01_heap_basics.cpp` and progress sequentially for best understanding.

Happy Learning! 🚀

