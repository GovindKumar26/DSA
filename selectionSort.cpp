class Solution {
  public:
    void selectionSort(vector<int> &arr) {
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            
            if (minIdx != i) {
                swap(arr[i], arr[minIdx]);
            }
        }
    }
};


// time complexity: O(n^2) all
// space complexity: O(1)
// stable: no
// in-place: yes
// adaptive: no
