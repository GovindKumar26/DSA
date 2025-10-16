// User function Template for C++

class Solution {
  public:
    long long divide(long long dividend, long long divisor) {
        // Handle overflow case
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;

        // Take absolute values
        long long n = abs((long long)dividend);
        long long d = abs((long long)divisor);
        long long ans = 0;

        while (n >= d) {
            int cnt = 0;

            // Find the largest d * (2^cnt) <= n
            while (n >= (d << (cnt + 1))) {  
                cnt++;
            }

            ans += (1LL << cnt);   // add 2^cnt to quotient
            n -= (d << cnt);       // subtract chunk
        }

        // Adjust sign
        if ((dividend < 0) ^ (divisor < 0)) ans = -ans;

        return (int)ans;
    }
};

// Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator. Return the quotient after dividing dividend by divisor.
// The integer division should truncate toward zero.
// time complexity: O(log^2(n)) where n is the absolute value of the dividend. This is because for each subtraction, we are effectively doubling the divisor (using bit shifts) until it exceeds the dividend, which takes O(log(n)) time, and this process can repeat up to O(log(n)) times in the worst case.
// space complexity: O(1) since we are using a constant amount of extra space.
// Approach: Use bit manipulation to perform the division. We repeatedly double the divisor (using left shifts) until it exceeds the dividend, keeping track of how many times we can double it. This allows us to subtract large chunks from the dividend at once, effectively performing the division without using multiplication or division operators.
// We also handle edge cases such as overflow when the dividend is INT_MIN and the divisor is
// -1, as well as adjusting the sign of the result based on the signs of the dividend and divisor. 