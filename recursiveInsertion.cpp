class Solution {
public:
    void recursiveInsertionSort(vector<int>& arr, int n) {
        // Base case: array of size 1 is already sorted
        if (n <= 1) return;

        // Recursively sort first n-1 elements
        recursiveInsertionSort(arr, n - 1);

        // Insert the nth element into the sorted array[0..n-2]
        int last = arr[n - 1];
        int j = n - 2;

        // Shift elements of arr[0..n-2] that are greater than last
        while (j >= 0 && arr[j] > last) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Place last in its correct position
        arr[j + 1] = last;
    }
};

// time complexity: O(n) best, O(n^2) avg and worst
// space complexity: O(n) recursive stack space
// in place: yes
// stable: yes