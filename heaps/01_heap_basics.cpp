/*
================================================================================
                        HEAP DATA STRUCTURE - BASICS
================================================================================

WHAT IS A HEAP?
--------------
A heap is a specialized tree-based data structure that satisfies the heap property:
- In a MAX HEAP: Parent node >= all its children
- In a MIN HEAP: Parent node <= all its children

WHY USE HEAPS?
-------------
1. Efficient priority queue operations (O(log n) insert/delete)
2. Quick access to min/max element (O(1))
3. Efficient sorting (Heap Sort)
4. Used in algorithms: Dijkstra's, Prim's, Huffman coding

BINARY HEAP PROPERTIES:
-----------------------
1. Complete Binary Tree: All levels filled except possibly the last, which fills left to right
2. Height = O(log n) where n is number of nodes
3. Can be efficiently represented using an array

ARRAY REPRESENTATION (0-indexed):
---------------------------------
For node at index i:
- Parent: (i-1)/2
- Left child: 2*i + 1
- Right child: 2*i + 2

For 1-indexed arrays:
- Parent: i/2
- Left child: 2*i
- Right child: 2*i + 1

Example Max Heap:
       100
      /   \
    80     90
   / \    / \
  70 60  85 75

Array: [100, 80, 90, 70, 60, 85, 75]
Index:   0   1   2   3   4   5   6

TIME COMPLEXITIES:
-----------------
- Insert: O(log n)
- Delete (extract max/min): O(log n)
- Get max/min: O(1)
- Build heap: O(n)
- Heapify: O(log n)

SPACE COMPLEXITY: O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;
    
    // Get index of parent node
    int parent(int i) {
        return (i - 1) / 2;
    }
    
    // Get index of left child
    int leftChild(int i) {
        return 2 * i + 1;
    }
    
    // Get index of right child
    int rightChild(int i) {
        return 2 * i + 2;
    }
    
    // Move element up to maintain heap property
    void heapifyUp(int index) {
        // If not root and parent is smaller than current
        while (index > 0 && heap[parent(index)] < heap[index]) {
            // Swap with parent
            swap(heap[index], heap[parent(index)]);
            // Move up
            index = parent(index);
        }
    }
    
    // Move element down to maintain heap property
    void heapifyDown(int index) {
        int size = heap.size();
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);
        
        // Check if left child is larger
        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }
        
        // Check if right child is larger
        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }
        
        // If largest is not current node
        if (largest != index) {
            swap(heap[index], heap[largest]);
            // Recursively heapify down
            heapifyDown(largest);
        }
    }
    
public:
    // Constructor
    MaxHeap() {}
    
    // Insert element into heap
    void insert(int val) {
        // Add element at the end
        heap.push_back(val);
        // Heapify up to maintain heap property
        heapifyUp(heap.size() - 1);
    }
    
    // Extract maximum element
    int extractMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        
        // Store max value (root)
        int maxVal = heap[0];
        
        // Move last element to root
        heap[0] = heap.back();
        heap.pop_back();
        
        // Heapify down from root
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return maxVal;
    }
    
    // Get maximum element without removing
    int getMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }
    
    // Check if heap is empty
    bool isEmpty() {
        return heap.empty();
    }
    
    // Get size of heap
    int size() {
        return heap.size();
    }
    
    // Print heap
    void printHeap() {
        cout << "Heap: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // Get heap array (for testing)
    vector<int> getHeap() {
        return heap;
    }
};

class MinHeap {
private:
    vector<int> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int index) {
        // For min heap, parent should be smaller
        while (index > 0 && heap[parent(index)] > heap[index]) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.size();
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);
        
        // Find smallest among node, left child, and right child
        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    
public:
    MinHeap() {}
    
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMin() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return minVal;
    }
    
    int getMin() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }
    
    bool isEmpty() {
        return heap.empty();
    }
    
    int size() {
        return heap.size();
    }
    
    void printHeap() {
        cout << "Heap: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    vector<int> getHeap() {
        return heap;
    }
};

// Test function
void demonstrateHeapBasics() {
    cout << "=== MAX HEAP DEMONSTRATION ===" << endl;
    MaxHeap maxHeap;
    
    vector<int> values = {10, 20, 15, 30, 40};
    cout << "Inserting: ";
    for (int val : values) {
        cout << val << " ";
        maxHeap.insert(val);
    }
    cout << endl;
    
    maxHeap.printHeap();
    cout << "Max element: " << maxHeap.getMax() << endl;
    
    cout << "\nExtracting max elements:" << endl;
    while (!maxHeap.isEmpty()) {
        cout << maxHeap.extractMax() << " ";
    }
    cout << endl;
    
    cout << "\n=== MIN HEAP DEMONSTRATION ===" << endl;
    MinHeap minHeap;
    
    cout << "Inserting: ";
    for (int val : values) {
        cout << val << " ";
        minHeap.insert(val);
    }
    cout << endl;
    
    minHeap.printHeap();
    cout << "Min element: " << minHeap.getMin() << endl;
    
    cout << "\nExtracting min elements:" << endl;
    while (!minHeap.isEmpty()) {
        cout << minHeap.extractMin() << " ";
    }
    cout << endl;
}

int main() {
    demonstrateHeapBasics();
    return 0;
}
