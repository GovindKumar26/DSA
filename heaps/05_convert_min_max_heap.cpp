/*
================================================================================
                    CONVERT MIN HEAP TO MAX HEAP AND VICE VERSA
================================================================================

PROBLEM 1: Convert Min Heap to Max Heap
PROBLEM 2: Convert Max Heap to Min Heap

KEY INSIGHT:
-----------
Cannot simply reverse or negate values! We need to rearrange elements
to satisfy the opposite heap property.

APPROACH:
--------
1. The array already represents a complete binary tree
2. We just need to reorganize it to satisfy new heap property
3. Use heapify operation from bottom-up

ALGORITHM:
---------
Step 1: Start from last non-leaf node: (n/2 - 1)
Step 2: Apply appropriate heapify (maxHeapify or minHeapify)
Step 3: Move up to root, heapifying each node

TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(log n) for recursive calls

WHY START FROM BOTTOM?
---------------------
- Leaves are already valid heaps (no children)
- Build larger heaps from smaller ones
- Ensures subtrees are valid heaps before processing parent

ALTERNATIVE APPROACHES:
----------------------
1. Build new heap: O(n log n) - less efficient
2. Sort and rebuild: O(n log n) - less efficient
3. Heapify in place: O(n) - OPTIMAL ✓

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// =============================================================================
//                    HEAPIFY OPERATIONS
// =============================================================================

void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

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

// =============================================================================
//                    CONVERSION FUNCTIONS
// =============================================================================

// Convert Min Heap to Max Heap
void convertMinHeapToMaxHeap(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap from bottom-up
    // Start from last non-leaf node
    for (int i = (n - 2) / 2; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

// Convert Max Heap to Min Heap
void convertMaxHeapToMinHeap(vector<int>& arr) {
    int n = arr.size();
    
    // Build min heap from bottom-up
    // Start from last non-leaf node
    for (int i = (n - 2) / 2; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
}

// =============================================================================
//                    VERIFICATION FUNCTIONS
// =============================================================================

bool isMaxHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[i] < arr[left]) return false;
        if (right < n && arr[i] < arr[right]) return false;
    }
    return true;
}

bool isMinHeap(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[i] > arr[left]) return false;
        if (right < n && arr[i] > arr[right]) return false;
    }
    return true;
}

// =============================================================================
//                    UTILITY FUNCTIONS
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

void visualizeHeap(const vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return;
    
    int height = log2(n) + 1;
    int index = 0;
    
    for (int level = 0; level < height && index < n; level++) {
        int nodes = min((int)pow(2, level), n - index);
        
        // Print spacing
        for (int i = 0; i < height - level; i++) cout << "  ";
        
        for (int i = 0; i < nodes; i++) {
            cout << arr[index++];
            if (i < nodes - 1) cout << "  ";
        }
        cout << endl;
    }
}

void demonstrateConversion(vector<int> arr, const string& type) {
    cout << "\n========================================" << endl;
    cout << "Converting " << type << endl;
    cout << "========================================" << endl;
    
    printArray(arr, "Original");
    cout << "\nOriginal Structure:" << endl;
    visualizeHeap(arr);
    
    if (type == "Min Heap to Max Heap") {
        cout << "\nVerification - Is Min Heap: " << (isMinHeap(arr) ? "YES" : "NO") << endl;
        
        convertMinHeapToMaxHeap(arr);
        
        printArray(arr, "\nAfter Conversion");
        cout << "\nConverted Structure:" << endl;
        visualizeHeap(arr);
        
        cout << "\nVerification - Is Max Heap: " << (isMaxHeap(arr) ? "YES" : "NO") << endl;
    } else {
        cout << "\nVerification - Is Max Heap: " << (isMaxHeap(arr) ? "YES" : "NO") << endl;
        
        convertMaxHeapToMinHeap(arr);
        
        printArray(arr, "\nAfter Conversion");
        cout << "\nConverted Structure:" << endl;
        visualizeHeap(arr);
        
        cout << "\nVerification - Is Min Heap: " << (isMinHeap(arr) ? "YES" : "NO") << endl;
    }
}

// =============================================================================
//                          STEP-BY-STEP TRACE
// =============================================================================

void traceConversion() {
    cout << "\n========================================" << endl;
    cout << "STEP-BY-STEP CONVERSION TRACE" << endl;
    cout << "========================================" << endl;
    
    vector<int> arr = {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
    
    cout << "\nConverting Min Heap to Max Heap" << endl;
    printArray(arr, "Initial Min Heap");
    
    int n = arr.size();
    
    cout << "\nProcessing from index " << (n-2)/2 << " down to 0:" << endl;
    
    for (int i = (n - 2) / 2; i >= 0; i--) {
        cout << "\n--- Heapifying at index " << i << " (value = " << arr[i] << ") ---" << endl;
        
        vector<int> before = arr;
        maxHeapify(arr, n, i);
        
        if (before != arr) {
            printArray(arr, "After heapify");
            visualizeHeap(arr);
        } else {
            cout << "No change needed (already satisfies max heap property)" << endl;
        }
    }
    
    cout << "\n--- Final Result ---" << endl;
    printArray(arr, "Max Heap");
    visualizeHeap(arr);
}

// =============================================================================
//                          DEMONSTRATION
// =============================================================================

void demonstrateConversions() {
    cout << "=== MIN HEAP TO MAX HEAP CONVERSIONS ===" << endl;
    
    // Test Case 1: Simple min heap
    vector<int> minHeap1 = {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
    demonstrateConversion(minHeap1, "Min Heap to Max Heap");
    
    // Test Case 2: Another min heap
    vector<int> minHeap2 = {1, 3, 6, 5, 9, 8};
    demonstrateConversion(minHeap2, "Min Heap to Max Heap");
    
    cout << "\n\n=== MAX HEAP TO MIN HEAP CONVERSIONS ===" << endl;
    
    // Test Case 3: Simple max heap
    vector<int> maxHeap1 = {20, 18, 10, 12, 9, 9, 3, 5, 6, 8};
    demonstrateConversion(maxHeap1, "Max Heap to Min Heap");
    
    // Test Case 4: Another max heap
    vector<int> maxHeap2 = {90, 80, 70, 60, 50, 40, 30};
    demonstrateConversion(maxHeap2, "Max Heap to Min Heap");
}

void demonstrateEdgeCases() {
    cout << "\n\n=== EDGE CASES ===" << endl;
    
    // Single element
    vector<int> single = {42};
    printArray(single, "\n1. Single element");
    convertMinHeapToMaxHeap(single);
    printArray(single, "After conversion");
    cout << "Is Max Heap: " << (isMaxHeap(single) ? "YES" : "NO") << endl;
    
    // Two elements
    vector<int> two = {5, 10};
    printArray(two, "\n2. Two elements (min heap)");
    convertMinHeapToMaxHeap(two);
    printArray(two, "After conversion to max heap");
    cout << "Is Max Heap: " << (isMaxHeap(two) ? "YES" : "NO") << endl;
    
    // All same elements
    vector<int> same = {7, 7, 7, 7, 7};
    printArray(same, "\n3. All same elements");
    convertMinHeapToMaxHeap(same);
    printArray(same, "After conversion");
    cout << "Is Max Heap: " << (isMaxHeap(same) ? "YES" : "NO") << endl;
    cout << "Is Min Heap: " << (isMinHeap(same) ? "YES" : "NO") << endl;
}

int main() {
    demonstrateConversions();
    traceConversion();
    demonstrateEdgeCases();
    
    return 0;
}

/*
KEY TAKEAWAYS:
-------------
1. Cannot simply reverse array to convert heap types
2. Must use heapify operations to rearrange elements
3. Start from last non-leaf node and work upward
4. Time complexity is O(n) - same as building a heap
5. Conversion is done in-place - no extra space needed
6. Both conversions use the same approach, just different heapify

INTERVIEW TIPS:
--------------
1. Explain why we start from (n/2 - 1) index
2. Mention that leaves don't need processing
3. Emphasize O(n) time complexity (not O(n log n))
4. Can verify result using isMaxHeap/isMinHeap
5. Works for any complete binary tree represented as array

COMMON APPLICATIONS:
-------------------
1. Switching between min and max priority queues
2. Algorithm optimization (sometimes need opposite heap)
3. Data structure transformation
4. Heap-based sorting variations
*/
