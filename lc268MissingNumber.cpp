class Solution {
public:
    int missingNumber(vector<int>& nums) {
    //  hashing approach
    //   int n = nums.size();
    //     vector<int>hash(n+1, 0);

    //     for(int i=0 ; i<n ; i++){
    //         hash[nums[i]] = 1;
    //     }

    //     for(int i=1 ; i<=n ; i++){
    //         if(hash[i]==0) return i;
    //     }
    // return 0;

    // sum method
//     int sum = 0;
  
//     int n = nums.size();
//    int sumTot = n*(n+1)/2;

//     for(auto i : nums){
//         sum = i+sum;
//     }
//     return sumTot-sum;
//     }

      // XOR method
      
      int n = nums.size();
       int xor1= 0, xor2 =0;
      for(int i=0 ; i<n ; i++){
        xor1 = xor1^nums[i];
        xor2 = xor2^(i+1);
      }

      return xor1^xor2;
    }

};



// Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

 

// Example 1:

// Input: nums = [3,0,1]

// Output: 2

// Explanation:

// n = 3 since there are 3 numbers, so all numbers ar