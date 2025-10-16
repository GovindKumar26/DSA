int countSetBits(int n) {
    int cnt = 0;
    while(n) {
        n = n & (n - 1); // remove the rightmost set bit
        cnt++;
    }
    return cnt;
}


// Given an integer n, count the number of set bits (1s) in its binary representation.
// time complexity: O(k) where k is the number of set bits in n.
// space complexity: O(1)
// Approach: Use Brian Kernighan’s Algorithm which repeatedly flips the least significant set bit of n to 0 and increments the count until n becomes 0.
// The expression n & (n - 1) removes the rightmost set bit from n


int cnt = 0;
while(n){
    cnt += n & 1;   // check the least significant bit
    n >>= 1;        // shift right by 1 to check next bit
}


// Alternative approach: Iterate through all bits of n, checking each bit and counting the number of 1s.
// time complexity: O(log n) where n is the input number.