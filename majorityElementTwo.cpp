#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Approach 1: Using HashMap
    // Time: O(n), Space: O(n)
    vector<int> majorityElementTwoMap(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        unordered_map<int, int> freq;
        
        // Count frequencies
        for (int num : nums) {
            freq[num]++;
        }
        
        // Find elements with frequency > n/3
        for (auto& [num, count] : freq) {
            if (count > n / 3) {
                result.push_back(num);
            }
        }
        
        return result;
    }
    
    // Approach 2: Using Boyer-Moore Majority Voting Algorithm (Extended Version)
    // Time: O(n), Space: O(1)
    vector<int> majorityElementTwo(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        
        // At most 2 elements can appear more than n/3 times
        int candidate1 = 0, candidate2 = 0;
        int count1 = 0, count2 = 0;
        
        // First pass: Find potential candidates
        for (int num : nums) {
            if (num == candidate1) {
                count1++;
            } else if (num == candidate2) {
                count2++;
            } else if (count1 == 0) {
                candidate1 = num;
                count1 = 1;
            } else if (count2 == 0) {
                candidate2 = num;
                count2 = 1;
            } else {
                count1--;
                count2--;
            }
        }
        
        // Second pass: Verify the candidates
        count1 = 0;
        count2 = 0;
        for (int num : nums) {
            if (num == candidate1) count1++;
            else if (num == candidate2) count2++;
        }
        
        if (count1 > n / 3) result.push_back(candidate1);
        if (count2 > n / 3) result.push_back(candidate2);
        
        return result;
    }
};

int main() {
    Solution sol;
    
    cout << "===== Using Map Approach =====" << endl;
    
    // Test case 1
    vector<int> nums1 = {3, 2, 3};
    vector<int> result1 = sol.majorityElementTwoMap(nums1);
    cout << "Test 1: [3,2,3] -> ";
    for (int num : result1) cout << num << " ";
    cout << endl;
    
    // Test case 2
    vector<int> nums2 = {1};
    vector<int> result2 = sol.majorityElementTwoMap(nums2);
    cout << "Test 2: [1] -> ";
    for (int num : result2) cout << num << " ";
    cout << endl;
    
    // Test case 3
    vector<int> nums3 = {1, 2};
    vector<int> result3 = sol.majorityElementTwoMap(nums3);
    cout << "Test 3: [1,2] -> ";
    for (int num : result3) cout << num << " ";
    cout << endl;
    
    // Test case 4
    vector<int> nums4 = {1, 1, 1, 3, 3, 2, 2, 2};
    vector<int> result4 = sol.majorityElementTwoMap(nums4);
    cout << "Test 4: [1,1,1,3,3,2,2,2] -> ";
    for (int num : result4) cout << num << " ";
    cout << endl;
    
    cout << "\n===== Using Boyer-Moore Voting Algorithm =====" << endl;
    
    // Test case 1
    vector<int> nums5 = {3, 2, 3};
    vector<int> result5 = sol.majorityElementTwo(nums5);
    cout << "Test 1: [3,2,3] -> ";
    for (int num : result5) cout << num << " ";
    cout << endl;
    
    // Test case 2
    vector<int> nums6 = {1};
    vector<int> result6 = sol.majorityElementTwo(nums6);
    cout << "Test 2: [1] -> ";
    for (int num : result6) cout << num << " ";
    cout << endl;
    
    // Test case 3
    vector<int> nums7 = {1, 2};
    vector<int> result7 = sol.majorityElementTwo(nums7);
    cout << "Test 3: [1,2] -> ";
    for (int num : result7) cout << num << " ";
    cout << endl;
    
    // Test case 4
    vector<int> nums8 = {1, 1, 1, 3, 3, 2, 2, 2};
    vector<int> result8 = sol.majorityElementTwo(nums8);
    cout << "Test 4: [1,1,1,3,3,2,2,2] -> ";
    for (int num : result8) cout << num << " ";
    cout << endl;
    
    return 0;
}
