class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
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
        int candidate = 0, count = 0;

        for (int x : nums) {
            if (count == 0) {
                candidate = x;
            }

            if (x == candidate) {
                count++;
            } else {
                count--;
            }
        }

     
        // verify 
        int cnt = 0;
        for (int x : nums)
            if (x == candidate)
                cnt++;

        if (cnt > nums.size() / 2)
            return candidate;
        return -1;
    }
};