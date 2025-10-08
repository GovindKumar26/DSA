class Solution {
public:

     // Lomuto Partition: pivot is the last element
     // arr[l..r] is partitioned into two halves
     // 0 to i is the window of ele smaller than pivot
     // j to r is the window of ele greater than pivot
    int lomutoPartition(vector<int>& arr, int l, int r) {
        int pivot = arr[r];
        int i = l - 1;

        for (int j = l; j < r; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[r]);
        return i + 1; // pivot index
    }


    // Hoare Partition: pivot is the first element
    int hoarePartition(vector<int>& arr, int l, int r) {
        int pivot = arr[l];
        int i = l - 1;
        int j = r + 1;

        while (true) {
            // Move i right until arr[i] >= pivot
            do { i++; } while (arr[i] < pivot);
            // Move j left until arr[j] <= pivot
            do { j--; } while (arr[j] > pivot);

            if (i >= j) return j; // partition index

            swap(arr[i], arr[j]); // swap out-of-place elements
        }
    }

    void quickSortHoare(vector<int>& arr, int l, int r) {
        if (l < r) {
            int pi = hoarePartition(arr, l, r);
            quickSortHoare(arr, l, pi);       // note: include pi
            quickSortHoare(arr, pi + 1, r);   // start from pi+1
        }
    }
};


// time complexity: O(n log n) avg and best, O(n^2) worst
// space complexity: O(log n) avg and best, O(n) worst (due to recursion stack)
// in-place: yes
// stable: no