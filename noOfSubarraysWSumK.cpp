class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
       unordered_map<int, int>mp;
       mp[0] = 1;
       int preSum = 0, cnt = 0;
       for(int i = 0 ; i<nums.size() ; i++){
           preSum  = preSum + nums[i];
           int remove = preSum - k;
           cnt = cnt + mp[remove];
           mp[preSum]++;
       }
       return cnt;
    }
};

// Given an array of integers nums and an integer k, return the total number of continuous subarrays whose sum equals to k.
// time complexity: O(n)
// space complexity: O(n)