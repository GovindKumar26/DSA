#include <iostream>
#include <vector>

// Function to perform insertion sort
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int ele = arr[i];
        int j = i - 1;
        // Move elements greater than ele to one position ahead
        while (j >= 0 && arr[j] > ele) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = ele;
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6};
    insertionSort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}

// time complexity: O(n) best, O(n^2) avg and worst
// space complexity: O(1)
// stable: yes
// adaptive: yes
// in-place: yes