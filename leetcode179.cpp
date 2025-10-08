class Solution {
public:
    string largestNumber(vector<int>& nums) {
        // Step 1: Convert numbers to strings
        vector<string> strNums;
        for (int num : nums) strNums.push_back(to_string(num));

        // Step 2: Sort strings using custom comparator
        sort(strNums.begin(), strNums.end(), [](const string &a, const string &b){
            return a + b > b + a; // if a+b is bigger, a comes first
        });

        // Step 3: Concatenate all strings
        string result;
        for (string s : strNums) result += s;

        // Step 4: Handle the case where all numbers are zero
        if (result[0] == '0') return "0";

        return result;
    }
};


// 179. Largest Number
// Solved
// Medium
// Topics
// premium lock icon
// Companies
// Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.

// Since the result may be very large, so you need to return a string instead of an integer.

 

// Example 1:

// Input: nums = [10,2]
// Output: "210"
// Example 2:

// Input: nums = [3,30,34,5,9]
// Output: "9534330"
 