class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if(n==0) return 0;
        // sort(nums.begin(), nums.end());
        // int lastSmaller = INT_MIN;
        // int cnt = 0;
         int longest = 1;

        // for(int i=0 ;i<n ; i++){
        //     if(nums[i]-1==lastSmaller){
        //         cnt++;
        //         lastSmaller = nums[i];
        //     }
        //     else if(nums[i]!=lastSmaller){
        //         cnt = 1;
        //         lastSmaller = nums[i];
        //     }
        //     longest = max(longest, cnt);
        // }
        // return longest;

        unordered_set<int>st;
        for(auto i : nums){
            st.insert(i);
        }

        for(auto ele : st){
             if(st.find(ele-1)==st.end()){
               int cnt = 1;
                int x = ele;
                while(st.find(x+1)!=st.end()){
                    x = x+1;
                    cnt = cnt+1;
                }
                longest = max(longest, cnt);
             }
        }
        return longest;
    }
};


// time complexity: O(n)
// space complexity: O(n)
// Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence