/*
================================================================================
                            HEAP SORT ALGORITHM
================================================================================

WHAT IS HEAP SORT?
-----------------
A comparison-based sorting algorithm that uses a binary heap data structure.
Works by building a max heap and repeatedly extracting the maximum element.

ALGORITHM:
---------
Step 1: Build a max heap from input array - O(n)
Step 2: Repeatedly:
   - Swap root (max) with last element
   - Reduce heap size by 1
   - Heapify root to restore max heap property
Step 3: Continue until heap size is 1

TIME COMPLEXITY:
---------------
- Best Case: O(n log n)
- Average Case: O(n log n)
- Worst Case: O(n log n)
- Building heap: O(n)
- n-1 deletions with heapify: O(n log n)

SPACE COMPLEXITY: O(1) - In-place sorting (except recursion stack O(log n))

CHARACTERISTICS:
---------------
✓ In-place sorting (constant space)
✓ Not stable (relative order may change)
✓ O(n log n) guaranteed (no worst case like QuickSort)
✓ No extra space needed (unlike Merge Sort)
✗ Not adaptive (doesn't take advantage of sorted data)
✗ Poor cache performance (non-sequential access)

COMPARISON WITH OTHER SORTS:
---------------------------
1. Merge Sort: Stable, needs O(n) space, better cache
2. Quick Sort: O(n²) worst case, but faster average, better cache
3. Heap Sort: Guaranteed O(n log n), in-place, but not stable

WHEN TO USE:
-----------
- When O(n log n) worst case is required
- When space is limited (in-place needed)
- When stability is not required
- For partial sorting (k largest/smallest elements)

APPLICATIONS:
------------
1. Priority Queue implementation
2. Finding k largest/smallest elements
3. External sorting
4. Systems with limited memory

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// =============================================================================
//                          HEAP SORT IMPLEMENTATION
// =============================================================================

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;         // Initialize largest as root
    int left = 2 * i + 1;    // Left child
    int right = 2 * i + 2;   // Right child
    
    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        
        // Recursively heapify the affected subtree
        heapify(arr, n, largest);
    }
}

// Main heap sort function
void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Step 1: Build max heap (rearrange array)
    // Start from last non-leaf node and heapify all nodes
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Step 2: Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (max) to end
        swap(arr[0], arr[i]);
        
        // Call heapify on reduced heap
        heapify(arr, i, 0);
    }
}

// =============================================================================
//                      ITERATIVE HEAPIFY VERSION
// =============================================================================

void heapifyIterative(vector<int>& arr, int n, int i) {
    while (true) {
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
        i = largest;
    }
}

void heapSortIterative(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyIterative(arr, n, i);
    }
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyIterative(arr, i, 0);
    }
}

// =============================================================================
//                      FIND K LARGEST ELEMENTS
// =============================================================================

// Find k largest elements using heap sort approach
vector<int> findKLargest(vector<int> arr, int k) {
    // Build max heap
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    vector<int> result;
    
    // Extract k largest elements
    for (int i = n - 1; i >= n - k && i >= 0; i--) {
        result.push_back(arr[0]);
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
    
    return result;
}

// Find k smallest elements
vector<int> findKSmallest(vector<int> arr, int k) {
    heapSort(arr); // Sort in ascending order
    
    vector<int> result;
    for (int i = 0; i < k && i < arr.size(); i++) {
        result.push_back(arr[i]);
    }
    
    return result;
}

// =============================================================================
//                      DESCENDING ORDER HEAP SORT
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

void heapSortDescending(vector<int>& arr) {
    int n = arr.size();
    
    // Build min heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
    }
}

// =============================================================================
//                          UTILITY FUNCTIONS
// =============================================================================

void printArray(const vector<int>& arr, const string& label = "") {
    if (!label.empty()) {
        cout << label << ": ";
    }
    cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool isSorted(const vector<int>& arr, bool ascending = true) {
    for (int i = 1; i < arr.size(); i++) {
        if (ascending) {
            if (arr[i] < arr[i-1]) return false;
        } else {
            if (arr[i] > arr[i-1]) return false;
        }
    }
    return true;
}

// =============================================================================
//                      STEP-BY-STEP VISUALIZATION
// =============================================================================

void visualizeHeapSort(vector<int> arr) {
    int n = arr.size();
    
    cout << "\n=== STEP-BY-STEP HEAP SORT ===" << endl;
    printArray(arr, "Initial array");
    
    // Build max heap
    cout << "\n--- Building Max Heap ---" << endl;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
        cout << "After heapifying index " << i << ": ";
        printArray(arr);
    }
    
    cout << "\n--- Extracting Elements ---" << endl;
    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        cout << "\nSwap root (" << arr[0] << ") with last (" << arr[i] << "):" << endl;
        swap(arr[0], arr[i]);
        printArray(arr, "After swap");
        
        heapify(arr, i, 0);
        printArray(arr, "After heapify");
    }
    
    printArray(arr, "\nFinal sorted array");
}

// =============================================================================
//                          DEMONSTRATION
// =============================================================================

void demonstrateHeapSort() {
    cout << "=== BASIC HEAP SORT ===" << endl;
    
    vector<int> arr1 = {12, 11, 13, 5, 6, 7};
    printArray(arr1, "Original");
    heapSort(arr1);
    printArray(arr1, "Sorted");
    cout << "Is sorted: " << (isSorted(arr1) ? "YES" : "NO") << endl;
    
    cout << "\n=== HEAP SORT WITH DUPLICATES ===" << endl;
    vector<int> arr2 = {4, 10, 3, 5, 1, 5, 3, 10, 2};
    printArray(arr2, "Original");
    heapSort(arr2);
    printArray(arr2, "Sorted");
    cout << "Is sorted: " << (isSorted(arr2) ? "YES" : "NO") << endl;
    
    cout << "\n=== DESCENDING ORDER ===" << endl;
    vector<int> arr3 = {12, 11, 13, 5, 6, 7};
    printArray(arr3, "Original");
    heapSortDescending(arr3);
    printArray(arr3, "Sorted (descending)");
    cout << "Is sorted descending: " << (isSorted(arr3, false) ? "YES" : "NO") << endl;
}

void demonstrateKElements() {
    cout << "\n=== FINDING K LARGEST ELEMENTS ===" << endl;
    
    vector<int> arr = {7, 10, 4, 3, 20, 15, 8, 2};
    int k = 3;
    
    printArray(arr, "Array");
    cout << "Finding " << k << " largest elements..." << endl;
    
    vector<int> largest = findKLargest(arr, k);
    printArray(largest, "K largest");
    
    cout << "\n=== FINDING K SMALLEST ELEMENTS ===" << endl;
    vector<int> smallest = findKSmallest(arr, k);
    printArray(smallest, "K smallest");
}

void demonstrateEdgeCases() {
    cout << "\n=== EDGE CASES ===" << endl;
    
    // Single element
    vector<int> single = {42};
    printArray(single, "\n1. Single element");
    heapSort(single);
    printArray(single, "After sort");
    
    // Two elements
    vector<int> two = {5, 2};
    printArray(two, "\n2. Two elements");
    heapSort(two);
    printArray(two, "After sort");
    
    // Already sorted
    vector<int> sorted = {1, 2, 3, 4, 5};
    printArray(sorted, "\n3. Already sorted");
    heapSort(sorted);
    printArray(sorted, "After sort");
    
    // Reverse sorted
    vector<int> reverse = {5, 4, 3, 2, 1};
    printArray(reverse, "\n4. Reverse sorted");
    heapSort(reverse);
    printArray(reverse, "After sort");
    
    // All same
    vector<int> same = {3, 3, 3, 3, 3};
    printArray(same, "\n5. All same");
    heapSort(same);
    printArray(same, "After sort");
}

void comparePerformance() {
    cout << "\n=== PERFORMANCE COMPARISON ===" << endl;
    cout << "\nTime Complexities:" << endl;
    cout << "Algorithm    | Best      | Average   | Worst     | Space" << endl;
    cout << "-------------|-----------|-----------|-----------|-------" << endl;
    cout << "Heap Sort    | O(nlogn)  | O(nlogn)  | O(nlogn)  | O(1)" << endl;
    cout << "Quick Sort   | O(nlogn)  | O(nlogn)  | O(n²)     | O(logn)" << endl;
    cout << "Merge Sort   | O(nlogn)  | O(nlogn)  | O(nlogn)  | O(n)" << endl;
    cout << "Bubble Sort  | O(n)      | O(n²)     | O(n²)     | O(1)" << endl;
    
    cout << "\nHeap Sort Advantages:" << endl;
    cout << "✓ Guaranteed O(n log n) performance" << endl;
    cout << "✓ In-place sorting (O(1) space)" << endl;
    cout << "✓ No worst case like QuickSort" << endl;
    
    cout << "\nHeap Sort Disadvantages:" << endl;
    cout << "✗ Not stable" << endl;
    cout << "✗ Poor cache locality" << endl;
    cout << "✗ Slower than QuickSort on average" << endl;
}

int main() {
    demonstrateHeapSort();
    demonstrateKElements();
    visualizeHeapSort({4, 10, 3, 5, 1});
    demonstrateEdgeCases();
    comparePerformance();
    
    return 0;
}

/*
KEY INSIGHTS:
------------
1. Heap sort is O(n log n) in all cases - guaranteed!
2. Build heap: O(n), Extract all: O(n log n)
3. In-place sorting, but not stable
4. Better than QuickSort for worst-case guarantees
5. Better space complexity than Merge Sort
6. Perfect for finding top-k elements efficiently

INTERVIEW QUESTIONS:
-------------------
Q: Why is heap sort not stable?
A: When we swap max with last element, equal elements may change order

Q: When would you use heap sort over quick sort?
A: When you need guaranteed O(n log n) or when space is limited

Q: How to sort in descending order?
A: Use min heap instead of max heap

Q: How to find k largest elements efficiently?
A: Build max heap and extract k times - O(n + k log n)

PRACTICE PROBLEMS:
-----------------
1. Implement heap sort for strings
2. Sort array with k-sorted elements
3. Find k largest elements in stream
4. Merge k sorted arrays using heap
*/
