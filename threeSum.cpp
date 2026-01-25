#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Approach 1: HashSet Approach
    // Time: O(n²), Space: O(n)
    vector<vector<int>> threeSumHashSet(vector<int>& nums) {
        int n = nums.size();
        set<vector<int>> resultSet; // Use set to avoid duplicates
        
        // Sort to ensure consistent triplet ordering
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 2; i++) {
            // Skip duplicates for first element
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            unordered_set<int> seen;
            int target = -nums[i];
            
            for (int j = i + 1; j < n; j++) {
                int complement = target - nums[j];
                
                if (seen.find(complement) != seen.end()) {
                    vector<int> triplet = {nums[i], complement, nums[j]};
                    sort(triplet.begin(), triplet.end());
                    resultSet.insert(triplet);
                }
                seen.insert(nums[j]);
            }
        }
        
        return vector<vector<int>>(resultSet.begin(), resultSet.end());
    }
    
    // Approach 2: Two Pointer Approach (after sorting)
    // Time: O(n²), Space: O(1) excluding result
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        
        // Sort the array
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < n - 2; i++) {
            // Skip duplicates for first element
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            // Early termination: if smallest is > 0, no solution possible
            if (nums[i] > 0) break;
            
            int left = i + 1;
            int right = n - 1;
            int target = -nums[i];  // We need nums[left] + nums[right] = -nums[i]
            
            while (left < right) {
                int sum = nums[left] + nums[right];
                
                if (sum == target) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // Skip duplicates for second element
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    // Skip duplicates for third element
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    
                    left++;
                    right--;
                }
                else if (sum < target) {
                    left++;
                }
                else {
                    right--;
                }
            }
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    cout << "===== HashSet Approach =====" << endl;
    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    cout << "Input: [-1, 0, 1, 2, -1, -4]" << endl;
    vector<vector<int>> res1 = sol.threeSumHashSet(nums1);
    cout << "Output: [";
    for (int i = 0; i < res1.size(); i++) {
        cout << "[" << res1[i][0] << "," << res1[i][1] << "," << res1[i][2] << "]";
        if (i < res1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [[-1,-1,2], [-1,0,1]]
    
    vector<int> nums2 = {0, 0, 0, 0};
    cout << "\nInput: [0, 0, 0, 0]" << endl;
    vector<vector<int>> res2 = sol.threeSum(nums2);
    cout << "Output: [";
    for (int i = 0; i < res2.size(); i++) {
        cout << "[" << res2[i][0] << "," << res2[i][1] << "," << res2[i][2] << "]";
        if (i < res2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    // Output: [[0,0,0]]
    
    cout << "\n===== Two Pointer Approach =====" << endl;
    vector<int> nums3 = {-1, 0, 1, 2, -1, -4};
    cout << "Input: [-1, 0, 1, 2, -1, -4]" << endl;
    vector<vector<int>> res3 = sol.threeSum(nums3);
    cout << "Output: [";
    for (int i = 0; i < res3.size(); i++) {
        cout << "[" << res3[i][0] << "," << res3[i][1] << "," << res3[i][2] << "]";
        if (i < res3.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    vector<int> nums4 = {0, 0, 0, 0};
    cout << "\nInput: [0, 0, 0, 0]" << endl;
    vector<vector<int>> res4 = sol.threeSum(nums4);
    cout << "Output: [";
    for (int i = 0; i < res4.size(); i++) {
        cout << "[" << res4[i][0] << "," << res4[i][1] << "," << res4[i][2] << "]";
        if (i < res4.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}

/*
LeetCode 15 - 3Sum

Problem: Find all unique triplets that sum to zero.

Algorithm:
1. Sort the array
2. Fix first element (i), use two pointers for remaining two
3. Skip duplicates to avoid duplicate triplets

Example: [-1, 0, 1, 2, -1, -4]

After sorting: [-4, -1, -1, 0, 1, 2]

i=0, nums[i]=-4:
  target=4, left=1, right=5
  -1+2=1 < 4, left++
  -1+2=1 < 4, left++
  0+2=2 < 4, left++
  1+2=3 < 4, left++
  left >= right, done

i=1, nums[i]=-1:
  target=1, left=2, right=5
  -1+2=1 == 1 ✓ → [-1,-1,2]
  skip dups, left=3, right=4
  0+1=1 == 1 ✓ → [-1,0,1]
  left=4, right=3, done

i=2, nums[i]=-1:
  skip (duplicate of i=1)

i=3, nums[i]=0:
  target=0, left=4, right=5
  1+2=3 > 0, right--
  left >= right, done

Result: [[-1,-1,2], [-1,0,1]]

Why sort?
1. Enables two-pointer technique
2. Makes duplicate detection easy (adjacent duplicates)
3. Early termination when nums[i] > 0

Handling duplicates:
- For i: skip if nums[i] == nums[i-1]
- For left: skip while nums[left] == nums[left+1]
- For right: skip while nums[right] == nums[right-1]

Time Complexity: O(n²) - O(n log n) sort + O(n²) two pointer
Space Complexity: O(1) excluding result (or O(n) for sorting)
*/
