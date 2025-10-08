class Solution {
  public:
  
    void merge(vector<int>&arr, int l, int mid, int r){
        int i = l, j = mid+1;
        
        vector<int>temp(r-l+1, 0);
        int k=0;
        
        while(i<=mid && j<=r){
            if(arr[i]<arr[j])
            temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        }
        
        while(i<=mid){
            temp[k++] = arr[i++];
        }
        
        while(j<=r){
            temp[k++] = arr[j++];
        }
        
        for(int k=0 ; k<temp.size() ; k++){
            arr[l+k] = temp[k];
        }
    }
  
    void mergeSort(vector<int>& arr, int l, int r) {
        
        if(l==r){
            return;
        }
        // code here
        int mid = (l+r)/2;
        
        mergeSort(arr, l, mid);
        mergeSort(arr, mid+1, r);
        merge(arr, l, mid, r);
    }
};

// time complexity: O(n log n) all
// space complexity: O(n)
// stable: yes
// adaptive: no
// in-place: no
// divide and conquer: yes
// recursive: yes