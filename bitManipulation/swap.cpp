class Solution {
public:
    void swap(int &a, int &b) {
        // Your code goes here
        a = a^b;
        b = a^b;
        a = a^b;
    }
};

// Given two integers a and b, swap their values using bitwise XOR operation without using any extra space.
// time complexity: O(1)
// space complexity: O(1)
// Approach: Use the properties of XOR operation to swap the values. The XOR of two identical bits is 0, and the XOR of a bit with 0 is the bit itself. By performing a series of XOR operations, we can effectively swap the values of a and b without needing a temporary variable.