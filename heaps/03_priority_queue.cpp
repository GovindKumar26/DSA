/*
================================================================================
                        PRIORITY QUEUE IMPLEMENTATION
================================================================================

WHAT IS A PRIORITY QUEUE?
-------------------------
A priority queue is an abstract data type where each element has a "priority".
Elements with higher priority are served before elements with lower priority.

DIFFERENCE FROM REGULAR QUEUE:
------------------------------
- Regular Queue: FIFO (First In First Out)
- Priority Queue: Highest/Lowest priority served first

IMPLEMENTATION OPTIONS:
----------------------
1. Array (unsorted): Insert O(1), Extract O(n)
2. Array (sorted): Insert O(n), Extract O(1)
3. Linked List: Similar to array
4. Binary Heap: Insert O(log n), Extract O(log n) ← BEST CHOICE
5. Fibonacci Heap: Insert O(1) amortized, Extract O(log n)

WHY HEAP FOR PRIORITY QUEUE?
-----------------------------
- Balanced operations: Both insert and extract are O(log n)
- Easy to implement
- Cache-friendly (array-based)
- Used in C++ STL std::priority_queue

C++ STL PRIORITY QUEUE:
-----------------------
#include <queue>

// Max heap by default
priority_queue<int> maxPQ;

// Min heap (using greater comparator)
priority_queue<int, vector<int>, greater<int>> minPQ;

// Custom comparator
auto cmp = [](int a, int b) { return a > b; };
priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

APPLICATIONS:
------------
1. Dijkstra's shortest path algorithm
2. Prim's minimum spanning tree
3. Huffman coding
4. Task scheduling (OS)
5. Event-driven simulation
6. A* pathfinding algorithm
7. Merge K sorted lists
8. Median maintenance

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// =============================================================================
//                    PRIORITY QUEUE WITH MAX HEAP
// =============================================================================

template <typename T>
class PriorityQueueMax {
private:
    vector<T> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] < heap[index]) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.size();
        
        while (true) {
            int largest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            
            if (left < size && heap[left] > heap[largest]) {
                largest = left;
            }
            
            if (right < size && heap[right] > heap[largest]) {
                largest = right;
            }
            
            if (largest == index) break;
            
            swap(heap[index], heap[largest]);
            index = largest;
        }
    }
    
public:
    // Insert element with priority
    void push(T value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }
    
    // Remove and return highest priority element
    T pop() {
        if (empty()) {
            throw runtime_error("Priority queue is empty");
        }
        
        T maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!empty()) {
            heapifyDown(0);
        }
        
        return maxVal;
    }
    
    // Get highest priority element without removing
    T top() {
        if (empty()) {
            throw runtime_error("Priority queue is empty");
        }
        return heap[0];
    }
    
    // Check if empty
    bool empty() {
        return heap.empty();
    }
    
    // Get size
    int size() {
        return heap.size();
    }
    
    // Print all elements
    void print() {
        cout << "[";
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i];
            if (i < heap.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

// =============================================================================
//                    PRIORITY QUEUE WITH MIN HEAP
// =============================================================================

template <typename T>
class PriorityQueueMin {
private:
    vector<T> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] > heap[index]) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.size();
        
        while (true) {
            int smallest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            
            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }
            
            if (smallest == index) break;
            
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }
    
public:
    void push(T value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }
    
    T pop() {
        if (empty()) {
            throw runtime_error("Priority queue is empty");
        }
        
        T minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!empty()) {
            heapifyDown(0);
        }
        
        return minVal;
    }
    
    T top() {
        if (empty()) {
            throw runtime_error("Priority queue is empty");
        }
        return heap[0];
    }
    
    bool empty() {
        return heap.empty();
    }
    
    int size() {
        return heap.size();
    }
    
    void print() {
        cout << "[";
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i];
            if (i < heap.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

// =============================================================================
//                    PRIORITY QUEUE WITH CUSTOM OBJECTS
// =============================================================================

struct Task {
    string name;
    int priority;
    
    Task(string n, int p) : name(n), priority(p) {}
    
    // For max heap: higher priority value = higher priority
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
    
    // For min heap: lower priority value = higher priority
    bool operator>(const Task& other) const {
        return priority > other.priority;
    }
};

// =============================================================================
//                          DEMONSTRATION
// =============================================================================

void demonstrateMaxPriorityQueue() {
    cout << "=== MAX PRIORITY QUEUE ===" << endl;
    PriorityQueueMax<int> pq;
    
    vector<int> values = {5, 1, 8, 3, 9, 2, 7};
    cout << "Inserting: ";
    for (int val : values) {
        cout << val << " ";
        pq.push(val);
    }
    cout << endl;
    
    cout << "Current heap: ";
    pq.print();
    
    cout << "\nExtracting elements (highest priority first):" << endl;
    while (!pq.empty()) {
        cout << pq.pop() << " ";
    }
    cout << endl;
}

void demonstrateMinPriorityQueue() {
    cout << "\n=== MIN PRIORITY QUEUE ===" << endl;
    PriorityQueueMin<int> pq;
    
    vector<int> values = {5, 1, 8, 3, 9, 2, 7};
    cout << "Inserting: ";
    for (int val : values) {
        cout << val << " ";
        pq.push(val);
    }
    cout << endl;
    
    cout << "Current heap: ";
    pq.print();
    
    cout << "\nExtracting elements (lowest priority first):" << endl;
    while (!pq.empty()) {
        cout << pq.pop() << " ";
    }
    cout << endl;
}

void demonstrateSTLPriorityQueue() {
    cout << "\n=== C++ STL PRIORITY QUEUE ===" << endl;
    
    // Max heap (default)
    cout << "\n1. Max Heap (default):" << endl;
    priority_queue<int> maxPQ;
    vector<int> values = {5, 1, 8, 3, 9, 2, 7};
    
    for (int val : values) {
        maxPQ.push(val);
    }
    
    cout << "Elements (highest first): ";
    while (!maxPQ.empty()) {
        cout << maxPQ.top() << " ";
        maxPQ.pop();
    }
    cout << endl;
    
    // Min heap
    cout << "\n2. Min Heap (using greater):" << endl;
    priority_queue<int, vector<int>, greater<int>> minPQ;
    
    for (int val : values) {
        minPQ.push(val);
    }
    
    cout << "Elements (lowest first): ";
    while (!minPQ.empty()) {
        cout << minPQ.top() << " ";
        minPQ.pop();
    }
    cout << endl;
}

void demonstrateCustomObjects() {
    cout << "\n=== PRIORITY QUEUE WITH CUSTOM OBJECTS ===" << endl;
    
    // Max heap: highest priority number first
    priority_queue<Task> taskQueue;
    
    taskQueue.push(Task("Low priority task", 1));
    taskQueue.push(Task("High priority task", 10));
    taskQueue.push(Task("Medium priority task", 5));
    taskQueue.push(Task("Urgent task", 15));
    
    cout << "Tasks (by priority):" << endl;
    while (!taskQueue.empty()) {
        Task t = taskQueue.top();
        taskQueue.pop();
        cout << "  Priority " << t.priority << ": " << t.name << endl;
    }
}

void demonstrateApplications() {
    cout << "\n=== REAL-WORLD APPLICATION: TOP K ELEMENTS ===" << endl;
    
    vector<int> arr = {3, 1, 5, 12, 2, 11, 8, 6, 9};
    int k = 3;
    
    // Find top K largest elements using min heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int num : arr) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop(); // Remove smallest
        }
    }
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\nTop " << k << " largest elements: ";
    
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    
    reverse(result.begin(), result.end());
    for (int x : result) cout << x << " ";
    cout << endl;
}

int main() {
    demonstrateMaxPriorityQueue();
    demonstrateMinPriorityQueue();
    demonstrateSTLPriorityQueue();
    demonstrateCustomObjects();
    demonstrateApplications();
    
    return 0;
}

/*
KEY CONCEPTS:
------------
1. Priority Queue is an ADT, Heap is the implementation
2. Max heap = highest priority first
3. Min heap = lowest priority first
4. Both operations are O(log n) - balanced performance
5. Use STL priority_queue for production code
6. Custom comparators allow flexible priority definitions
7. Perfect for algorithms requiring "best" element repeatedly
*/
