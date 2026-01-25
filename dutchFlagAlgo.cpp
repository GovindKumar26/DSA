class Solution {
public:
    void sortColors(vector<int>& nums) {
        double cntW=0,cntR=0,cntB = 0;

        for(int i =0;i<nums.size();i++){
            if(nums[i]==0) cntR++;
            else if(nums[i]==1) cntW++;
            else cntB++;
        }

        for(int i=0;i<nums.size();i++){
            if(i<cntR) nums[i] = 0;
            else if(i<cntR+cntW) nums[i] = 1;
            else if(i<cntR+cntW+cntB) nums[i] = 2;
        }


        // Dutch National Flag Algorithm - O(n) time, O(1) space, single pass
        // int n = nums.size();
        // int low = 0, mid = 0, high = n - 1;
        // 
        // // Invariant: [0..low-1] = 0s, [low..mid-1] = 1s, [high+1..n-1] = 2s
        // while (mid <= high) {
        //     if (nums[mid] == 0) {
        //         swap(nums[mid], nums[low]);
        //         low++;
        //         mid++;
        //     }
        //     else if (nums[mid] == 1) {
        //         mid++;
        //     }
        //     else { // nums[mid] == 2
        //         swap(nums[mid], nums[high]);
        //         high--;
        //         // Don't increment mid! Need to check swapped element
        //     }
        // }
        
    }
};

// Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
// We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
// time complexity: O(n)
// space complexity: O(1)