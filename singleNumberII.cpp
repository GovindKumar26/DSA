#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Approach 1: Bit Manipulation (Count bits at each position)
    // Time: O(32*n) = O(n), Space: O(1)
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        
        // For each bit position (0 to 31)
        for (int i = 0; i < 32; i++) {
            int count = 0;
            
            // Count how many numbers have this bit set
            for (int num : nums) {
                if ((num >> i) & 1) {
                    count++;
                }
            }
            
            // If count % 3 != 0, the single number has this bit set
            if (count % 3 != 0) {
                ans |= (1 << i);
            }
        }
        
        return ans;
    }
    
    // Approach 2: Using ones and twos (State Machine)
    // Time: O(n), Space: O(1)
    int singleNumberOptimized(vector<int>& nums) {
        int ones = 0, twos = 0;
        
        for (int num : nums) {
            // ones holds bits that appeared 1 time (mod 3)
            // twos holds bits that appeared 2 times (mod 3)
            
            ones = (ones ^ num) & (~twos);
            twos = (twos ^ num) & (~ones);
        }
        
        return ones;
    }
};

int main() {
    Solution sol;
    
    vector<int> nums1 = {2, 2, 3, 2};
    cout << "Input: [2, 2, 3, 2]" << endl;
    cout << "Single Number: " << sol.singleNumber(nums1) << endl;
    
    vector<int> nums2 = {0, 1, 0, 1, 0, 1, 99};
    cout << "\nInput: [0, 1, 0, 1, 0, 1, 99]" << endl;
    cout << "Single Number: " << sol.singleNumber(nums2) << endl;
    
    vector<int> nums3 = {-2, -2, 1, 1, 1, -2, 4};
    cout << "\nInput: [-2, -2, 1, 1, 1, -2, 4]" << endl;
    cout << "Single Number (Optimized): " << sol.singleNumberOptimized(nums3) << endl;
    
    return 0;
}

/*
LeetCode 137 - Single Number II

Problem: Given an integer array where every element appears three times 
except for one element which appears exactly once. Find that single element.

Example 1:
Input: nums = [2,2,3,2]
Output: 3

Example 2:
Input: nums = [0,1,0,1,0,1,99]
Output: 99

Approach 1 - Bit Counting:
- For each bit position (0-31), count how many numbers have that bit set
- If count % 3 != 0, the single number has that bit set
- Build the answer bit by bit

Approach 2 - State Machine (ones, twos):
- Track bits appearing once in 'ones', twice in 'twos'
- When a bit appears 3 times, it's removed from both
- After processing, 'ones' contains the single number

State transitions for each bit:
(ones, twos) -> after seeing the bit
(0, 0) -> (1, 0)  // first occurrence
(1, 0) -> (0, 1)  // second occurrence  
(0, 1) -> (0, 0)  // third occurrence (reset)

Time Complexity: O(n)
Space Complexity: O(1)
*/
