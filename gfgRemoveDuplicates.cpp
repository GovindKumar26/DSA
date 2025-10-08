class Solution {
  public:
    // Function to remove duplicates from the given array.
    vector<int> removeDuplicates(vector<int> &arr) {
        // code here
        int i=0 ;
        vector<int>ans;
        ans.push_back(arr[0]);
        for(int j=1 ; j<arr.size() ; j++){
            if(arr[i]!=arr[j]){
             //   ans.push_back(arr[i]);
                i = j;
                ans.push_back(arr[j]);
            }
        }
        return ans;
    }
};


// You are given a sorted array arr[] containing positive integers. Your task is to remove all duplicate elements from this array such that each element appears only once. Return an array containing these distinct elements in the same order as they appeared.
// Examples :

// Input: arr[] = [2, 2, 2, 2, 2]
// Output: [2]
// Explanation: After removing all the duplicates only one instance of 2 will remain i.e. [2] so modified array will contains 2 at first position and you should return array containing [2] after modifying the array.
// Input: arr[] = [1, 2, 4]
// Output: [1, 2, 4]
// Explation:  As the array does not contain any duplicates so you should return [1, 2, 4].