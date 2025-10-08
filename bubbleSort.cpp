class Solution {
  public:
    void bubbleSort(vector<int>& arr) {
        // code here
        int n = arr.size();
        
        for(int i=0 ; i<n ; i++){
            bool flag = 1;
            for(int j=0 ; j<n-1-i ; j++){
                if(arr[j]>arr[j+1]){
                    swap(arr[j], arr[j+1]);
                    flag = 0;
                }
            }
            if(flag) break;
        }
    }
};

// time complexity: O(n) best, O(n^2) avg and worst
// space complexity: O(1)
// stable: yes
// in-place: yes
// adaptive: yes