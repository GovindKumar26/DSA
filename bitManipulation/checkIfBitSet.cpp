class Solution {
public:
    bool checkIthBit(int n, int i) {
        // Your code goes here
        int check = 1<<i;
        return n&check;
    }
};

// Given two integers n and i, check if the ith bit in the binary representation of n is set (1) or not (0).
// time complexity: O(1) 
// space complexity: O(1)