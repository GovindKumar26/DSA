/*
================================================================================
                        HEAPIFY OPERATIONS
================================================================================

WHAT IS HEAPIFY?
---------------
Heapify is the process of converting an array/tree into a heap data structure.

TWO TYPES OF HEAPIFY:
--------------------
1. HEAPIFY UP (Sift Up / Bubble Up):
   - Used when inserting a new element
   - Starts from a node and moves upward
   - Compares with parent and swaps if needed
   - Time: O(log n)

2. HEAPIFY DOWN (Sift Down / Bubble Down):
   - Used when deleting root or building heap
   - Starts from a node and moves downward
   - Compares with children and swaps with appropriate child
   - Time: O(log n)

BUILD HEAP:
----------
- Convert an arbitrary array into a heap
- Two approaches:
  a) Insert each element one by one: O(n log n)
  b) Heapify from bottom-up: O(n) - MORE EFFICIENT!

WHY BUILD HEAP IS O(n)?
----------------------
- We only need to heapify non-leaf nodes
- Number of non-leaf nodes = n/2
- Leaves are already heaps (no children)
- Starting from last non-leaf node: (n/2 - 1) index
- Most nodes are near leaves, need less operations

Height analysis:
- n/2 nodes at height 0 (leaves, no work)
- n/4 nodes at height 1 (1 comparison)
- n/8 nodes at height 2 (2 comparisons)
- ...
- Sum = n * (1/4 + 2/8 + 3/16 + ...) = O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// =============================================================================
//                          MAX HEAP HEAPIFY
// =============================================================================

// Heapify a subtree rooted at index i
// n is the size of heap
void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;           // Initialize largest as root
    int left = 2 * i + 1;      // Left child
    int right = 2 * i + 2;     // Right child
    
    // If left child exists and is greater than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    // If right child exists and is greater than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        // Recursively heapify the affected subtree
        maxHeapify(arr, n, largest);
    }
}

// Iterative version of max heapify
void maxHeapifyIterative(vector<int>& arr, int n, int i) {
    while (i < n) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        
        if (largest == i) {
            break; // Heap property satisfied
        }
        
        swap(arr[i], arr[largest]);
        i = largest; // Move down to the swapped position
    }
}

// Build max heap from an array - O(n)
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    
    // Start from last non-leaf node and heapify all nodes
    // Last non-leaf node is at index (n/2 - 1)
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

// =============================================================================
//                          MIN HEAP HEAPIFY
// =============================================================================

void minHeapify(vector<int>& arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }
    
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }
    
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
}

// =============================================================================
//                          HEAPIFY UP OPERATIONS
// =============================================================================

// Heapify up for max heap (used during insertion)
void heapifyUpMax(vector<int>& arr, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        
        // If parent is already greater, heap property satisfied
        if (arr[parent] >= arr[index]) {
            break;
        }
        
        // Swap with parent
        swap(arr[index], arr[parent]);
        index = parent;
    }
}

// Heapify up for min heap (used during insertion)
void heapifyUpMin(vector<int>& arr, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        
        // If parent is already smaller, heap property satisfied
        if (arr[parent] <= arr[index]) {
            break;
        }
        
        swap(arr[index], arr[parent]);
        index = parent;
    }
}

// =============================================================================
//                          UTILITY FUNCTIONS
// =============================================================================

void printArray(const vector<int>& arr, const string& message = "") {
    if (!message.empty()) {
        cout << message << ": ";
    }
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

// Visualize heap structure
void visualizeHeap(const vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return;
    
    int height = log2(n) + 1;
    int index = 0;
    
    for (int level = 0; level < height && index < n; level++) {
        int nodes = min((int)pow(2, level), n - index);
        
        // Print indentation
        for (int i = 0; i < height - level - 1; i++) {
            cout << "  ";
        }
        
        // Print nodes at this level
        for (int i = 0; i < nodes; i++) {
            cout << arr[index++] << " ";
            if (i < nodes - 1) cout << "  ";
        }
        cout << endl;
    }
}

// =============================================================================
//                          DEMONSTRATION
// =============================================================================

void demonstrateHeapify() {
    cout << "=== HEAPIFY OPERATIONS DEMONSTRATION ===" << endl;
    
    // Example 1: Build Max Heap
    cout << "\n1. Building Max Heap from array:" << endl;
    vector<int> arr1 = {4, 10, 3, 5, 1, 6, 8, 2, 7, 9};
    printArray(arr1, "Original array");
    
    buildMaxHeap(arr1);
    printArray(arr1, "After buildMaxHeap");
    visualizeHeap(arr1);
    
    // Example 2: Build Min Heap
    cout << "\n2. Building Min Heap from same array:" << endl;
    vector<int> arr2 = {4, 10, 3, 5, 1, 6, 8, 2, 7, 9};
    printArray(arr2, "Original array");
    
    buildMinHeap(arr2);
    printArray(arr2, "After buildMinHeap");
    visualizeHeap(arr2);
    
    // Example 3: Heapify Down demonstration
    cout << "\n3. Max Heapify Down from root:" << endl;
    vector<int> arr3 = {1, 10, 8, 5, 3, 6, 4}; // 1 is at root, violates max heap
    printArray(arr3, "Before heapify");
    
    maxHeapify(arr3, arr3.size(), 0);
    printArray(arr3, "After heapify from root");
    visualizeHeap(arr3);
    
    // Example 4: Heapify Up demonstration
    cout << "\n4. Heapify Up during insertion:" << endl;
    vector<int> arr4 = {10, 8, 6, 5, 3, 4, 1};
    printArray(arr4, "Max heap before insertion");
    
    arr4.push_back(15); // Insert 15
    cout << "Inserted 15 at end" << endl;
    printArray(arr4, "Before heapify up");
    
    heapifyUpMax(arr4, arr4.size() - 1);
    printArray(arr4, "After heapify up");
    visualizeHeap(arr4);
    
    // Time complexity demonstration
    cout << "\n5. Time Complexity Comparison:" << endl;
    cout << "Building heap using repeated insertion: O(n log n)" << endl;
    cout << "Building heap using heapify: O(n)" << endl;
    cout << "For n = 1,000,000 elements:" << endl;
    cout << "  - Insertion method: ~20,000,000 operations" << endl;
    cout << "  - Heapify method: ~1,000,000 operations" << endl;
}

int main() {
    demonstrateHeapify();
    return 0;
}

/*
KEY TAKEAWAYS:
-------------
1. Heapify Down: Used for delete operations and building heap
2. Heapify Up: Used for insert operations
3. Build heap using heapify is O(n), not O(n log n)
4. Start heapify from last non-leaf node: (n/2 - 1)
5. Recursive and iterative versions both work
6. Max heap: parent >= children
7. Min heap: parent <= children
*/
