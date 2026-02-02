/*
================================================================================
                    CHECK IF ARRAY IS A VALID HEAP
================================================================================

PROBLEM: Given an array, determine if it represents a valid binary heap.

APPROACHES:
----------
1. Check Max Heap Property
2. Check Min Heap Property
3. Check Complete Binary Tree Property
4. Check if array can be converted to valid heap

HEAP PROPERTIES TO VERIFY:
--------------------------
For MAX HEAP:
- Every parent node >= its children
- For node at index i:
  * arr[i] >= arr[2*i + 1] (left child)
  * arr[i] >= arr[2*i + 2] (right child)

For MIN HEAP:
- Every parent node <= its children
- For node at index i:
  * arr[i] <= arr[2*i + 1] (left child)
  * arr[i] <= arr[2*i + 2] (right child)

COMPLETE BINARY TREE:
--------------------
- All levels are completely filled except possibly the last
- Last level is filled from left to right
- In array: no gaps before size n

TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(1) for iterative, O(log n) for recursive

IMPORTANT NOTES:
---------------
1. Array of size 0 or 1 is always a valid heap
2. Need to check all non-leaf nodes
3. Leaf nodes don't need checking (they have no children)
4. Non-leaf nodes: indices 0 to (n/2 - 1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// =============================================================================
//                    CHECK IF ARRAY IS MAX HEAP
// =============================================================================

// Method 1: Iterative approach
bool isMaxHeap(vector<int>& arr) {
    int n = arr.size();
    
    // Empty or single element is always a valid heap
    if (n <= 1) return true;
    
    // Check all non-leaf nodes
    // Last non-leaf node is at index (n/2 - 1)
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        
        // Check left child exists and parent is greater
        if (leftChild < n && arr[i] < arr[leftChild]) {
            return false;
        }
        
        // Check right child exists and parent is greater
        if (rightChild < n && arr[i] < arr[rightChild]) {
            return false;
        }
    }
    
    return true;
}

// Method 2: Recursive approach
bool isMaxHeapRecursive(vector<int>& arr, int i = 0) {
    int n = arr.size();
    
    // If we're at or beyond a leaf node, it's valid
    if (i >= (n - 2) / 2) {
        return true;
    }
    
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    
    // Check if current node satisfies max heap property
    bool isValid = true;
    
    if (leftChild < n) {
        isValid = isValid && (arr[i] >= arr[leftChild]);
    }
    
    if (rightChild < n) {
        isValid = isValid && (arr[i] >= arr[rightChild]);
    }
    
    // Recursively check left and right subtrees
    return isValid && 
           isMaxHeapRecursive(arr, leftChild) && 
           isMaxHeapRecursive(arr, rightChild);
}

// =============================================================================
//                    CHECK IF ARRAY IS MIN HEAP
// =============================================================================

bool isMinHeap(vector<int>& arr) {
    int n = arr.size();
    
    if (n <= 1) return true;
    
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        
        // For min heap, parent should be smaller than children
        if (leftChild < n && arr[i] > arr[leftChild]) {
            return false;
        }
        
        if (rightChild < n && arr[i] > arr[rightChild]) {
            return false;
        }
    }
    
    return true;
}

bool isMinHeapRecursive(vector<int>& arr, int i = 0) {
    int n = arr.size();
    
    if (i >= (n - 2) / 2) {
        return true;
    }
    
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    
    bool isValid = true;
    
    if (leftChild < n) {
        isValid = isValid && (arr[i] <= arr[leftChild]);
    }
    
    if (rightChild < n) {
        isValid = isValid && (arr[i] <= arr[rightChild]);
    }
    
    return isValid && 
           isMinHeapRecursive(arr, leftChild) && 
           isMinHeapRecursive(arr, rightChild);
}

// =============================================================================
//                    CHECK IF COMPLETE BINARY TREE
// =============================================================================

// Check if array represents a complete binary tree
bool isCompleteBinaryTree(vector<int>& arr) {
    // An array representation is always a complete binary tree
    // if it has no gaps and fills from left to right
    // Since we use contiguous array indices, it's automatically complete
    return true;
}

// For a tree with explicit structure (not array), we'd need BFS
// to check if we encounter a gap

// =============================================================================
//                    UTILITY FUNCTIONS
// =============================================================================

void printArray(vector<int>& arr, string label = "") {
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

string boolToString(bool val) {
    return val ? "YES" : "NO";
}

// Visualize why array is/isn't a heap
void explainHeapProperty(vector<int>& arr, bool isMax) {
    int n = arr.size();
    cout << "\nDetailed Check:" << endl;
    
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        
        cout << "Node[" << i << "] = " << arr[i];
        
        if (leftChild < n) {
            cout << ", Left[" << leftChild << "] = " << arr[leftChild];
            
            bool leftOk = isMax ? (arr[i] >= arr[leftChild]) : (arr[i] <= arr[leftChild]);
            cout << " -> " << (leftOk ? "✓" : "✗");
        }
        
        if (rightChild < n) {
            cout << ", Right[" << rightChild << "] = " << arr[rightChild];
            
            bool rightOk = isMax ? (arr[i] >= arr[rightChild]) : (arr[i] <= arr[rightChild]);
            cout << " -> " << (rightOk ? "✓" : "✗");
        }
        
        cout << endl;
    }
}

// =============================================================================
//                          DEMONSTRATION
// =============================================================================

void testMaxHeap() {
    cout << "=== TESTING MAX HEAP ===" << endl;
    
    vector<vector<int>> testCases = {
        {90, 80, 70, 60, 50, 40, 30},      // Valid max heap
        {90, 15, 10, 7, 12, 2},             // Valid max heap
        {10, 20, 30, 40, 50},               // Not a max heap
        {100},                               // Single element
        {},                                  // Empty
        {50, 40, 45, 35, 30, 42, 43},      // Not a max heap
        {100, 90, 95, 80, 85, 88, 92}      // Valid max heap
    };
    
    for (int i = 0; i < testCases.size(); i++) {
        cout << "\nTest Case " << (i + 1) << ":" << endl;
        printArray(testCases[i], "Array");
        
        bool result = isMaxHeap(testCases[i]);
        cout << "Is Max Heap (Iterative): " << boolToString(result) << endl;
        
        bool resultRec = isMaxHeapRecursive(testCases[i]);
        cout << "Is Max Heap (Recursive): " << boolToString(resultRec) << endl;
        
        if (!result && testCases[i].size() > 1) {
            explainHeapProperty(testCases[i], true);
        }
    }
}

void testMinHeap() {
    cout << "\n=== TESTING MIN HEAP ===" << endl;
    
    vector<vector<int>> testCases = {
        {10, 20, 30, 40, 50, 60, 70},      // Valid min heap
        {5, 10, 15, 20, 25, 30},           // Valid min heap
        {50, 40, 30, 20, 10},               // Not a min heap
        {1},                                // Single element
        {},                                 // Empty
        {10, 15, 12, 20, 18, 25, 16},      // Valid min heap
        {5, 20, 10, 25, 30, 15, 12}        // Not a min heap
    };
    
    for (int i = 0; i < testCases.size(); i++) {
        cout << "\nTest Case " << (i + 1) << ":" << endl;
        printArray(testCases[i], "Array");
        
        bool result = isMinHeap(testCases[i]);
        cout << "Is Min Heap (Iterative): " << boolToString(result) << endl;
        
        bool resultRec = isMinHeapRecursive(testCases[i]);
        cout << "Is Min Heap (Recursive): " << boolToString(resultRec) << endl;
        
        if (!result && testCases[i].size() > 1) {
            explainHeapProperty(testCases[i], false);
        }
    }
}

void demonstrateEdgeCases() {
    cout << "\n=== EDGE CASES ===" << endl;
    
    // All same elements
    vector<int> allSame = {5, 5, 5, 5, 5};
    printArray(allSame, "\n1. All same elements");
    cout << "Is Max Heap: " << boolToString(isMaxHeap(allSame)) << endl;
    cout << "Is Min Heap: " << boolToString(isMinHeap(allSame)) << endl;
    
    // Two elements
    vector<int> twoAsc = {10, 20};
    printArray(twoAsc, "\n2. Two elements (ascending)");
    cout << "Is Max Heap: " << boolToString(isMaxHeap(twoAsc)) << endl;
    cout << "Is Min Heap: " << boolToString(isMinHeap(twoAsc)) << endl;
    
    vector<int> twoDesc = {20, 10};
    printArray(twoDesc, "\n3. Two elements (descending)");
    cout << "Is Max Heap: " << boolToString(isMaxHeap(twoDesc)) << endl;
    cout << "Is Min Heap: " << boolToString(isMinHeap(twoDesc)) << endl;
    
    // Three elements - perfect binary tree
    vector<int> perfectMax = {30, 20, 10};
    printArray(perfectMax, "\n4. Perfect max heap");
    cout << "Is Max Heap: " << boolToString(isMaxHeap(perfectMax)) << endl;
    
    vector<int> perfectMin = {10, 20, 30};
    printArray(perfectMin, "\n5. Perfect min heap");
    cout << "Is Min Heap: " << boolToString(isMinHeap(perfectMin)) << endl;
}

int main() {
    testMaxHeap();
    testMinHeap();
    demonstrateEdgeCases();
    
    return 0;
}

/*
KEY INSIGHTS:
------------
1. Only check non-leaf nodes: indices 0 to (n/2 - 1)
2. Leaf nodes are at indices (n/2) to (n - 1)
3. Empty array or single element is always a valid heap
4. Both max and min heaps are valid heaps
5. Array with all same elements is both max and min heap
6. Time: O(n) - check each node once
7. Space: O(1) iterative, O(log n) recursive (call stack)

COMMON MISTAKES:
---------------
1. Forgetting to check if child index is within bounds
2. Checking leaf nodes unnecessarily
3. Wrong calculation of last non-leaf node
4. Confusing parent/child index formulas
*/
