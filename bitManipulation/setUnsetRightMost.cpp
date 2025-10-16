n = n | (n + 1);

// Set the rightmost unset bit of n to 1.
// time complexity: O(1)
// space complexity: O(1)

n = n & (n - 1);
// Unset the rightmost set bit of n to 0.
// time complexity: O(1)
// space complexity: O(1)


n = n | (n - 1);
// Set all bits to the right of the rightmost unset bit (including itself) to
// 1.
// time complexity: O(1)
// space complexity: O(1)

n = n & ~(n - 1);
// Isolate the rightmost set bit of n.
// time complexity: O(1)
// space complexity: O(1)

n = n & ~(n + 1);
// Isolate the rightmost unset bit of n.
// time complexity: O(1)
// space complexity: O(1)



int mask = ~(n) & (n + 1);
n = n ^ mask;
// Toggle the rightmost unset bit of n.
// time complexity: O(1)
// space complexity: O(1)

int mask = n & ~(n + 1);
n = n ^ mask;
// Toggle the rightmost set bit of n.
// time complexity: O(1)
// space complexity: O(1)