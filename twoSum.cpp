class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int>mp;
        int n = nums.size();
        for(int i=0 ; i<n ; i++){
            int num = nums[i];
            int moreNeeded = target-num;
            if(mp.find(moreNeeded)!=mp.end()){
                return {i, mp[moreNeeded]};
            }
            mp[num] = i;
        }
        return {-1, -1};
    }
};

// time complexity: O(n)
// space complexity: O(n)