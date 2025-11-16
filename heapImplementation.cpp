#include <bits/stdc++.h>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    // Get parent index
    int parent(int i) { return (i - 1) / 2; }

    // Get left child index
    int leftChild(int i) { return 2 * i + 1; }

    // Get right child index
    int rightChild(int i) { return 2 * i + 2; }

    // Move element up to maintain heap property
    void heapifyUp(int idx) {
        while (idx > 0 && heap[parent(idx)] < heap[idx]) {
            swap(heap[parent(idx)], heap[idx]);
            idx = parent(idx);
        }
    }

    // Move element down to maintain heap property
    void heapifyDown(int idx) {
        int size = heap.size();
        int largest = idx;
        int left = leftChild(idx);
        int right = rightChild(idx);

        if (left < size && heap[left] > heap[largest])
            largest = left;

        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != idx) {
            swap(heap[idx], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Constructor
    MaxHeap() {}

    // Insert element into heap
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Delete and return maximum element (root)
    int deleteMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty!");
        }

        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            heapifyDown(0);
        }

        return maxVal;
    }

    // Get maximum element without removing
    int getMax() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty!");
        }
        return heap[0];
    }

    // Check if heap is empty
    bool isEmpty() {
        return heap.empty();
    }

    // Get heap size
    int size() {
        return heap.size();
    }

    // Build heap from array (heapify entire array)
    void buildHeap(vector<int>& arr) {
        heap = arr;
        // Start from last non-leaf node and heapify down
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    // Print heap
    void printHeap() {
        cout << "Heap: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Get heap array (for heap sort)
    vector<int> getHeapArray() {
        return heap;
    }
};

class MinHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int idx) {
        while (idx > 0 && heap[parent(idx)] > heap[idx]) {
            swap(heap[parent(idx)], heap[idx]);
            idx = parent(idx);
        }
    }

    void heapifyDown(int idx) {
        int size = heap.size();
        int smallest = idx;
        int left = leftChild(idx);
        int right = rightChild(idx);

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != idx) {
            swap(heap[idx], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap() {}

    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int deleteMin() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty!");
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
            throw runtime_error("Heap is empty!");
        }
        return heap[0];
    }

    bool isEmpty() {
        return heap.empty();
    }

    int size() {
        return heap.size();
    }

    void buildHeap(vector<int>& arr) {
        heap = arr;
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    void printHeap() {
        cout << "Heap: ";
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }

    vector<int> getHeapArray() {
        return heap;
    }
};

// Heap Sort Functions
class HeapSort {
private:
    // Heapify a subtree rooted at index i (for array-based heapification)
    static void heapifyDown(vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapifyDown(arr, n, largest);
        }
    }

public:
    // Heap sort in ascending order (using max heap)
    static void heapSortAscending(vector<int>& arr) {
        int n = arr.size();

        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapifyDown(arr, n, i);
        }

        // Extract elements one by one from heap
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]); // Move current root to end
            heapifyDown(arr, i, 0); // Heapify reduced heap
        }
    }

    // Heap sort in descending order (extract from max heap differently)
    static void heapSortDescending(vector<int>& arr) {
        MaxHeap maxHeap;
        maxHeap.buildHeap(arr);
        
        arr.clear();
        while (!maxHeap.isEmpty()) {
            arr.push_back(maxHeap.deleteMax());
        }
    }
};

// Demo and test functions
int main() {
    cout << "========== MAX HEAP DEMO ==========" << endl;
    MaxHeap maxHeap;
    
    // Insert elements
    cout << "\n1. Inserting elements: 10, 20, 15, 30, 40" << endl;
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(15);
    maxHeap.insert(30);
    maxHeap.insert(40);
    maxHeap.printHeap();
    
    cout << "Max element: " << maxHeap.getMax() << endl;
    
    // Delete max
    cout << "\n2. Deleting max element: " << maxHeap.deleteMax() << endl;
    maxHeap.printHeap();
    
    // Build heap from array
    cout << "\n3. Building heap from array [5, 3, 8, 1, 9, 2]" << endl;
    vector<int> arr1 = {5, 3, 8, 1, 9, 2};
    maxHeap.buildHeap(arr1);
    maxHeap.printHeap();
    
    cout << "\n========== MIN HEAP DEMO ==========" << endl;
    MinHeap minHeap;
    
    cout << "\n1. Inserting elements: 10, 20, 15, 30, 40" << endl;
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(15);
    minHeap.insert(30);
    minHeap.insert(40);
    minHeap.printHeap();
    
    cout << "Min element: " << minHeap.getMin() << endl;
    
    cout << "\n2. Deleting min element: " << minHeap.deleteMin() << endl;
    minHeap.printHeap();
    
    cout << "\n========== HEAP SORT DEMO ==========" << endl;
    
    // Ascending order
    vector<int> arr2 = {12, 11, 13, 5, 6, 7};
    cout << "\nOriginal array: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;
    
    HeapSort::heapSortAscending(arr2);
    cout << "Sorted (ascending): ";
    for (int x : arr2) cout << x << " ";
    cout << endl;
    
    // Descending order
    vector<int> arr3 = {12, 11, 13, 5, 6, 7};
    HeapSort::heapSortDescending(arr3);
    cout << "Sorted (descending): ";
    for (int x : arr3) cout << x << " ";
    cout << endl;
    
    return 0;
}

/*
Time Complexities:
- insert(): O(log n) - heapifyUp
- deleteMax()/deleteMin(): O(log n) - heapifyDown
- getMax()/getMin(): O(1) - peek at root
- buildHeap(): O(n) - bottom-up heapification
- heapSort(): O(n log n) - build heap + n deletions

Space Complexity:
- O(n) for storing n elements in vector
- O(log n) recursive stack for heapifyDown (can be O(1) with iterative)

Key Operations:
1. Insert: Add to end, bubble up
2. Delete: Replace root with last element, bubble down
3. Heapify: Build heap from unsorted array in O(n)
4. Heap Sort: Build heap then repeatedly extract max/min
*/
