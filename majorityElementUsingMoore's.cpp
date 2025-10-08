class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // map<int, int>mp;
        // int n  = nums.size();
        // for(int i=0;i<n;i++){
        //     mp[nums[i]]++;
        // }
        // for(auto it : mp){
        //     if(it.second>n/2) return it.first;
        // }
        // return -1;

        //   int n = nums.size();
        // sort(nums.begin(),nums.end());
        // return nums[n/2];

        // Moore's voting algorithm
        int cnt=0;
        int ele;
        for(int i=0 ; i<nums.size(); i++){
            if(cnt==0){
                ele = nums[i];
                cnt=1;
            } else if(nums[i]==ele){
                cnt++;
            } else{
                cnt--;
            }
        }
               
       int cnt1 =0;
        for(int i=0 ; i<nums.size() ; i++){
            if(nums[i]==ele) cnt1++;
        }

        if(cnt1>nums.size()/2){
            return ele;
        }
        return -1;
    }
};