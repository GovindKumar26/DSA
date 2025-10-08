class Solution {
public:
    // Function to perform recursive bubble sort
    void recursiveBubbleSort(vector<int>& arr, int n) {
        // Base case
        if (n == 1) return;

        // One pass to bubble the largest element to the end
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
            }
        }

        // Recur for remaining array
        recursiveBubbleSort(arr, n - 1);
    }
};
// time complexity: O(n) best, O(n^2) avg and worst
// space complexity: O(n) recursive stack space
// stable: yes
// in-place: yes
// adaptive: yes
// recursive: yes