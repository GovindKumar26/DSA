class Solution {
  public:
    int longestSubarray(vector<int>& arr, int k) {
    
    //  int maxLen = 0;
     
    //  for(int i=0 ; i<arr.size() ; i++){
         
    //      int sum = 0;
         
    //      for(int j=i ; j<arr.size() ; j++) {
    //          sum = sum + arr[j];
             
    //          if(sum==k) {
    //              maxLen = max(maxLen, j-i+1);
    //          }
    //      }
         
    //  }
    //  return maxLen;
    
    int prefixSum = 0;
    map<int, int> mp;
    int maxLen = 0;
    
    for(int i=0 ; i<arr.size() ; i++) {
        prefixSum += arr[i];
        
        if(prefixSum==k) {
            maxLen = i + 1;
        }
         
       else if(mp.find(prefixSum-k)!=mp.end()) {
            maxLen = max(maxLen, i - mp[prefixSum-k] );
        }
        
       if(mp.find(prefixSum)==mp.end()) mp[prefixSum] = i;
    }
    return maxLen;
       
    }
};

// Given an array of integers arr and an integer k, find the length of the longest subarray whose sum equals k. If there is no such subarray, return 0.
// time complexity: O(n)
// space complexity: O(n)