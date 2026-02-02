#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

class Solution {
public:
    // Approach 1: Brute Force - Using Hash Map
    // Time: O(n), Space: O(n)
    vector<int> findMissingRepeatingHashMap(vector<int> nums) {
        int n = nums.size();
        unordered_map<int, int> freq;
        
        // Count frequencies
        for (int num : nums) {
            freq[num]++;
        }
        
        int repeating = -1, missing = -1;
        
        // Find repeating and missing
        for (int i = 1; i <= n; i++) {
            if (freq[i] == 2) {
                repeating = i;
            } else if (freq[i] == 0) {
                missing = i;
            }
        }
        
        return {repeating, missing};
    }
    
    // Approach 2: Math - Using Sum and Sum of Squares
    // Time: O(n), Space: O(1)
    vector<int> findMissingRepeatingMath(vector<int> nums) {
        int n = nums.size();
        long long actualSum = 0;
        long long actualSumSq = 0;
        
        for (int num : nums) {
            actualSum += num;
            actualSumSq += (long long)num * num;
        }
        
        // Expected sum: 1+2+...+n = n*(n+1)/2
        long long expectedSum = (long long)n * (n + 1) / 2;
        
        // Expected sum of squares: 1^2+2^2+...+n^2 = n*(n+1)*(2n+1)/6
        long long expectedSumSq = (long long)n * (n + 1) * (2 * n + 1) / 6;
        
        // Let A = repeating, B = missing
        // actualSum = expectedSum - B + A
        // actualSumSq = expectedSumSq - B^2 + A^2
        
        // A - B = actualSum - expectedSum ... (1)
        long long diff = actualSum - expectedSum;
        
        // A^2 - B^2 = actualSumSq - expectedSumSq
        // (A-B)(A+B) = actualSumSq - expectedSumSq
        // A + B = (actualSumSq - expectedSumSq) / (A - B) ... (2)
        long long sumSqDiff = actualSumSq - expectedSumSq;
        long long sum = sumSqDiff / diff;
        
        // Solving (1) and (2):
        // A - B = diff
        // A + B = sum
        // 2A = diff + sum
        long long A = (diff + sum) / 2;
        long long B = sum - A;
        
        return {(int)A, (int)B};
    }
    
    // Approach 3: XOR - Using XOR Properties
    // Time: O(n), Space: O(1)
    vector<int> findMissingRepeatingXOR(vector<int> nums) {
        int n = nums.size();
        int xorAll = 0;
        
        // XOR all array elements
        for (int num : nums) {
            xorAll ^= num;
        }
        
        // XOR with [1, n]
        for (int i = 1; i <= n; i++) {
            xorAll ^= i;
        }
        
        // Now xorAll = A ^ B (repeating ^ missing)
        
        // Find rightmost set bit in xorAll
        int rightmostSetBit = xorAll & -xorAll;
        
        // Divide elements into two groups based on this bit
        int bucket0 = 0, bucket1 = 0;
        
        // Divide array elements
        for (int num : nums) {
            if (num & rightmostSetBit) {
                bucket1 ^= num;
            } else {
                bucket0 ^= num;
            }
        }
        
        // Divide [1, n]
        for (int i = 1; i <= n; i++) {
            if (i & rightmostSetBit) {
                bucket1 ^= i;
            } else {
                bucket0 ^= i;
            }
        }
        
        // One bucket has repeating, other has missing
        // Check which is which
        int count = 0;
        for (int num : nums) {
            if (num == bucket0) count++;
        }
        
        if (count == 2) {
            return {bucket0, bucket1}; // bucket0 is repeating
        } else {
            return {bucket1, bucket0}; // bucket1 is repeating
        }
    }
    
    // Approach 4: OPTIMAL - Math with cleaner formulation
    // Time: O(n), Space: O(1)
    vector<int> findMissingRepeatingNumbers(vector<int> nums) {
        int n = nums.size();
        
        // S = sum of array, Sn = sum of 1 to n
        // S - Sn = A - B ... (equation 1)
        long long S = 0;
        long long S2 = 0;
        
        for (int num : nums) {
            S += num;
            S2 += (long long)num * num;
        }
        
        long long Sn = (long long)n * (n + 1) / 2;
        long long S2n = (long long)n * (n + 1) * (2 * n + 1) / 6;
        
        // val1 = S - Sn = A - B
        long long val1 = S - Sn;
        
        // val2 = S2 - S2n = A^2 - B^2 = (A-B)(A+B)
        long long val2 = S2 - S2n;
        
        // A + B = val2 / val1
        long long val2_divided = val2 / val1;
        
        // A - B = val1
        // A + B = val2_divided
        // 2A = val1 + val2_divided
        long long A = (val1 + val2_divided) / 2;
        long long B = A - val1;
        
        return {(int)A, (int)B};
    }
};

int main() {
    Solution sol;
    
    cout << "===== Approach 1: Hash Map =====" << endl;
    vector<int> nums1 = {3, 1, 2, 5, 3};
    vector<int> result1 = sol.findMissingRepeatingHashMap(nums1);
    cout << "Input: [3, 1, 2, 5, 3]" << endl;
    cout << "Output: [" << result1[0] << ", " << result1[1] << "]" << endl;
    cout << "Expected: [3, 4] (3 repeats, 4 is missing)" << endl << endl;
    
    cout << "===== Approach 2: Math (Sum and Sum of Squares) =====" << endl;
    vector<int> nums2 = {3, 1, 2, 5, 3};
    vector<int> result2 = sol.findMissingRepeatingMath(nums2);
    cout << "Input: [3, 1, 2, 5, 3]" << endl;
    cout << "Output: [" << result2[0] << ", " << result2[1] << "]" << endl;
    cout << "Expected: [3, 4]" << endl << endl;
    
    cout << "===== Approach 3: XOR =====" << endl;
    vector<int> nums3 = {3, 1, 2, 5, 3};
    vector<int> result3 = sol.findMissingRepeatingXOR(nums3);
    cout << "Input: [3, 1, 2, 5, 3]" << endl;
    cout << "Output: [" << result3[0] << ", " << result3[1] << "]" << endl;
    cout << "Expected: [3, 4]" << endl << endl;
    
    cout << "===== Approach 4: OPTIMAL (Math Clean) =====" << endl;
    vector<int> nums4 = {3, 1, 2, 5, 3};
    vector<int> result4 = sol.findMissingRepeatingNumbers(nums4);
    cout << "Input: [3, 1, 2, 5, 3]" << endl;
    cout << "Output: [" << result4[0] << ", " << result4[1] << "]" << endl;
    cout << "Expected: [3, 4]" << endl << endl;
    
    // Test case 2
    cout << "===== Test Case 2 (OPTIMAL) =====" << endl;
    vector<int> nums5 = {2, 2};
    vector<int> result5 = sol.findMissingRepeatingNumbers(nums5);
    cout << "Input: [2, 2]" << endl;
    cout << "Output: [" << result5[0] << ", " << result5[1] << "]" << endl;
    cout << "Expected: [2, 1]" << endl << endl;
    
    // Test case 3
    cout << "===== Test Case 3 (OPTIMAL) =====" << endl;
    vector<int> nums6 = {1, 3, 3};
    vector<int> result6 = sol.findMissingRepeatingNumbers(nums6);
    cout << "Input: [1, 3, 3]" << endl;
    cout << "Output: [" << result6[0] << ", " << result6[1] << "]" << endl;
    cout << "Expected: [3, 2]" << endl;
    
    return 0;
}

/*
===============================================
PROBLEM EXPLANATION
===============================================
Given: Array of size n containing values from [1, n]
- One number A appears twice (repeating)
- One number B is missing

Find: [A, B] where A is repeating, B is missing

Example: [3, 1, 2, 5, 3], n = 5
Expected range: [1, 2, 3, 4, 5]
Actual: [1, 2, 3, 3, 5]
A = 3 (repeating), B = 4 (missing)

===============================================
APPROACH 1: HASH MAP
===============================================
Algorithm:
1. Count frequency of each element
2. Number with frequency 2 is repeating
3. Number with frequency 0 (from 1 to n) is missing

Time: O(n) - single pass + checking 1 to n
Space: O(n) - hash map

Pros: Simple, easy to understand
Cons: Uses extra space

===============================================
APPROACH 2: MATH (Sum and Sum of Squares)
===============================================
Algorithm:
1. Calculate actual sum and actual sum of squares
2. Calculate expected sum and expected sum of squares
3. Use two equations to solve for A and B

Mathematical formulation:
Let A = repeating, B = missing

Equation 1: A - B = (actual sum) - (expected sum)
Equation 2: A² - B² = (actual sum²) - (expected sum²)

From equation 2: (A-B)(A+B) = (actual sum²) - (expected sum²)
Therefore: A + B = [(actual sum²) - (expected sum²)] / (A - B)

Solving:
- A - B = val1
- A + B = val2
- 2A = val1 + val2
- A = (val1 + val2) / 2
- B = A - val1

Expected sum: n*(n+1)/2
Expected sum of squares: n*(n+1)*(2n+1)/6

Time: O(n) - single pass
Space: O(1) - only variables

Pros: Optimal time and space, mathematically elegant
Cons: Need to handle overflow with long long

Example: [3, 1, 2, 5, 3]
Actual sum = 3+1+2+5+3 = 14
Expected sum = 5*6/2 = 15
val1 = 14 - 15 = -1 (A - B = -1)

Actual sum² = 9+1+4+25+9 = 48
Expected sum² = 5*6*11/6 = 55
val2 = 48 - 55 = -7
val2/val1 = -7/-1 = 7 (A + B = 7)

A = (-1 + 7)/2 = 3 ✓
B = 7 - 3 = 4 ✓

===============================================
APPROACH 3: XOR
===============================================
Algorithm:
1. XOR all array elements with [1, n]
2. Result is A ^ B (repeating ^ missing)
3. Find rightmost set bit in A ^ B
4. Divide elements into two buckets based on this bit
5. Each bucket will have one of A or B
6. Verify which is repeating by counting

XOR properties used:
- a ^ a = 0
- a ^ 0 = a
- XOR is associative and commutative

Time: O(n)
Space: O(1)

Pros: Constant space, doesn't use math formulas
Cons: Requires additional verification step

===============================================
APPROACH 4: OPTIMAL (MATH CLEAN)
===============================================
Same as Approach 2 but with cleaner variable naming
and better organized code.

This is the BEST approach:
- Time: O(n)
- Space: O(1)
- Clean and elegant
- Handles overflow properly with long long

===============================================
COMPARISON SUMMARY
===============================================
Approach          Time    Space    Notes
Hash Map          O(n)    O(n)     Simple but uses space
Math (Sum+Sum²)   O(n)    O(1)     Optimal ✓
XOR               O(n)    O(1)     Optimal, bit manipulation
Math Clean        O(n)    O(1)     Optimal ✓, cleanest code

Best Approaches: Math or XOR (both O(n) time, O(1) space)
Recommendation: Math approach is cleaner and easier to understand

Key Insight: 
Using two equations (sum and sum of squares) allows us to 
uniquely solve for two unknowns (A and B) in constant space.
*/
