class Solution {
public:
    bool isPowerOfTwo(int n) {
        // Your code goes here
        return n>0 && !(n&(n-1));
    }
};

// Given an integer n, check if it is a power of 2.
// time complexity: O(1)
// space complexity: O(1)