class Solution {
  public:
    // Function to merge the arrays.
    void merge(int n, int m, long long arr1[], long long arr2[]) {
       int left = n-1, right = 0;
       
       
       while(left>=0 && right<m){
           if(arr1[left]>arr2[right]){
               swap(arr1[left], arr2[right]);
               left--, right++;
           } else break;
       }
       sort(arr1, arr1+n);
       sort(arr2, arr2+m);
    }
};

// time complexity: O(min(n+m) + nlog + mlogm)
// space complexity: O(1)
// Given two sorted arrays arr1 and arr2 of sizes n and m in non-decreasing order, merge them in sorted order without using any extra space. The first n elements should be stored in arr1 and the last m elements in arr2.