#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Approach 1: HashSet Approach
    // Time: O(n³), Space: O(n)
    vector<vector<int>> fourSumHashSet(vector<int>& nums, int target) {
        int n = nums.size();
        set<vector<int>> resultSet;
        
        // Sort to ensure consistent quadruplet ordering
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 3; i++) {
            // Skip duplicates for first element
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            for (int j = i + 1; j < n - 2; j++) {
                // Skip duplicates for second element
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                
                unordered_set<long long> seen;
                long long twoSum = (long long)target - nums[i] - nums[j];
                
                for (int k = j + 1; k < n; k++) {
                    long long complement = twoSum - nums[k];
                    
                    if (seen.find(complement) != seen.end()) {
                        vector<int> quad = {nums[i], nums[j], (int)complement, nums[k]};
                        sort(quad.begin(), quad.end());
                        resultSet.insert(quad);
                    }
                    seen.insert(nums[k]);
                }
            }
        }
        
        return vector<vector<int>>(resultSet.begin(), resultSet.end());
    }
    
    // Approach 2: Two nested loops + Two Pointers
    // Time: O(n³), Space: O(1) excluding result
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 4) return result;
        
        // Sort the array
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 3; i++) {
            // Skip duplicates for first element
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            // Early termination: if minimum sum > target
            if ((long long)nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
            // Skip if maximum sum with nums[i] < target
            if ((long long)nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target) continue;
            
            for (int j = i + 1; j < n - 2; j++) {
                // Skip duplicates for second element
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                
                // Early termination for inner loop
                if ((long long)nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
                if ((long long)nums[i] + nums[j] + nums[n-2] + nums[n-1] < target) continue;
                
                int left = j + 1;
                int right = n - 1;
                long long newTarget = (long long)target - nums[i] - nums[j];
                
                while (left < right) {
                    long long sum = (long long)nums[left] + nums[right];
                    
                    if (sum == newTarget) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
                        
                        // Skip duplicates
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        
                        left++;
                        right--;
                    }
                    else if (sum < newTarget) {
                        left++;
                    }
                    else {
                        right--;
                    }
                }
            }
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    cout << "===== HashSet Approach =====" << endl;
    vector<int> nums1 = {1, -2, 3, 5, 7, 9};
    int target1 = 7;
    cout << "Input: [1, -2, 3, 5, 7, 9], target = 7" << endl;
    vector<vector<int>> res1 = sol.fourSumHashSet(nums1, target1);
    cout << "Output: [";
    for (int i = 0; i < res1.size(); i++) {
        cout << "[" << res1[i][0] << "," << res1[i][1] << "," << res1[i][2] << "," << res1[i][3] << "]";
        if (i < res1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [[-2,1,3,5]]
    
    vector<int> nums2 = {1, 0, -1, 0, -2, 2};
    int target2 = 0;
    cout << "\nInput: [1, 0, -1, 0, -2, 2], target = 0" << endl;
    vector<vector<int>> res2 = sol.fourSum(nums2, target2);
    cout << "Output: [";
    for (int i = 0; i < res2.size(); i++) {
        cout << "[" << res2[i][0] << "," << res2[i][1] << "," << res2[i][2] << "," << res2[i][3] << "]";
        if (i < res2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [[-2,-1,1,2], [-2,0,0,2], [-1,0,0,1]]
    
    vector<int> nums3 = {2, 2, 2, 2, 2};
    int target3 = 8;
    cout << "\nInput: [2, 2, 2, 2, 2], target = 8" << endl;
    vector<vector<int>> res3 = sol.fourSum(nums3, target3);
    cout << "Output: [";
    for (int i = 0; i < res3.size(); i++) {
        cout << "[" << res3[i][0] << "," << res3[i][1] << "," << res3[i][2] << "," << res3[i][3] << "]";
        if (i < res3.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [[2,2,2,2]]
    
    cout << "\n===== Two Pointer Approach =====" << endl;
    vector<int> nums4 = {1, -2, 3, 5, 7, 9};
    int target4 = 7;
    cout << "Input: [1, -2, 3, 5, 7, 9], target = 7" << endl;
    vector<vector<int>> res4 = sol.fourSum(nums4, target4);
    cout << "Output: [";
    for (int i = 0; i < res4.size(); i++) {
        cout << "[" << res4[i][0] << "," << res4[i][1] << "," << res4[i][2] << "," << res4[i][3] << "]";
        if (i < res4.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    vector<int> nums5 = {1, 0, -1, 0, -2, 2};
    int target5 = 0;
    cout << "\nInput: [1, 0, -1, 0, -2, 2], target = 0" << endl;
    vector<vector<int>> res5 = sol.fourSum(nums5, target5);
    cout << "Output: [";
    for (int i = 0; i < res5.size(); i++) {
        cout << "[" << res5[i][0] << "," << res5[i][1] << "," << res5[i][2] << "," << res5[i][3] << "]";
        if (i < res5.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}

/*
LeetCode 18 - 4Sum

Problem: Find all unique quadruplets that sum to target.

Algorithm: Extension of 3Sum
1. Sort the array
2. Fix first element (i)
3. Fix second element (j)
4. Use two pointers for remaining two elements
5. Skip duplicates at each level

Example: [1, 0, -1, 0, -2, 2], target = 0

After sorting: [-2, -1, 0, 0, 1, 2]

i=0 (nums[i]=-2):
  j=1 (nums[j]=-1):
    target for two pointers = 0-(-2)-(-1) = 3
    left=2, right=5: 0+2=2 < 3, left++
    left=3, right=5: 0+2=2 < 3, left++
    left=4, right=5: 1+2=3 == 3 ✓ → [-2,-1,1,2]
    
  j=2 (nums[j]=0):
    target = 0-(-2)-0 = 2
    left=3, right=5: 0+2=2 == 2 ✓ → [-2,0,0,2]
    
i=1 (nums[i]=-1):
  j=2 (nums[j]=0):
    target = 0-(-1)-0 = 1
    left=3, right=5: 0+2=2 > 1, right--
    left=3, right=4: 0+1=1 == 1 ✓ → [-1,0,0,1]

Result: [[-2,-1,1,2], [-2,0,0,2], [-1,0,0,1]]

Important: Use long long to avoid integer overflow!
- Sum of 4 integers can exceed INT_MAX
- Example: nums = [1000000000, 1000000000, 1000000000, 1000000000]

Early termination optimizations:
1. If min possible sum > target, break outer loop
2. If max possible sum < target, continue to next iteration

Time Complexity: O(n³)
Space Complexity: O(1) excluding result
*/
