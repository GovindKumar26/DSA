#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Count subarrays with XOR equal to k
    // Using prefix XOR and hash map
    // Time: O(n), Space: O(n)
    int subarraysWithXorK(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> prefixXorCount; // stores frequency of each prefix XOR
        int prefixXor = 0;
        int count = 0;
        
        // Important: Initialize with 0 XOR appearing once (empty prefix)
        prefixXorCount[0] = 1;
        
        for (int i = 0; i < n; i++) {
            prefixXor ^= nums[i];
            
            // If (prefixXor ^ k) exists in map, it means there are subarrays 
            // ending at current index with XOR = k
            // Because: if prefixXor[j] = prefixXor[i] ^ k
            // then XOR of subarray (j+1 to i) = prefixXor[i] ^ prefixXor[j] = k
            int target = prefixXor ^ k;
            
            if (prefixXorCount.find(target) != prefixXorCount.end()) {
                count += prefixXorCount[target];
            }
            
            // Add current prefix XOR to map
            prefixXorCount[prefixXor]++;
        }
        
        return count;
    }
};

int main() {
    Solution sol;
    
    // Test case 1
    vector<int> nums1 = {4, 2, 2, 6, 4};
    int k1 = 6;
    cout << "Test 1: nums = [4, 2, 2, 6, 4], k = 6" << endl;
    cout << "Output: " << sol.subarraysWithXorK(nums1, k1) << endl;
    cout << "Expected: 4" << endl;
    cout << "Subarrays: [4,2], [4,2,2,6,4], [2,2,6], [6]" << endl << endl;
    
    // Test case 2
    vector<int> nums2 = {5, 6, 7, 8, 9};
    int k2 = 5;
    cout << "Test 2: nums = [5, 6, 7, 8, 9], k = 5" << endl;
    cout << "Output: " << sol.subarraysWithXorK(nums2, k2) << endl;
    cout << "Expected: 2" << endl;
    cout << "Subarrays: [5], [5,6,7,8,9]" << endl << endl;
    
    // Test case 3
    vector<int> nums3 = {1, 1, 1, 1};
    int k3 = 0;
    cout << "Test 3: nums = [1, 1, 1, 1], k = 0" << endl;
    cout << "Output: " << sol.subarraysWithXorK(nums3, k3) << endl;
    cout << "Expected: 6" << endl;
    cout << "Subarrays: [1,1], [1,1] (2nd pair), [1,1] (3rd pair), [1,1,1,1], [1,1] at indices (0,1,2,3), (1,2,3,4), etc." << endl << endl;
    
    // Test case 4
    vector<int> nums4 = {4, 2, 2, 6, 4};
    int k4 = 4;
    cout << "Test 4: nums = [4, 2, 2, 6, 4], k = 4" << endl;
    cout << "Output: " << sol.subarraysWithXorK(nums4, k4) << endl << endl;
    
    return 0;
}

/*
Algorithm Explanation:

Key Insight: XOR Property
- If XOR(i to j) = k, then prefixXor[j] = prefixXor[i-1] ^ k
- Rearranging: prefixXor[i-1] = prefixXor[j] ^ k

For each position j, we need to find how many positions i exist where:
prefixXor[i] = prefixXor[j] ^ k

Example: nums = [4, 2, 2, 6, 4], k = 6

Index:       0   1   2   3   4
nums:       [4,  2,  2,  6,  4]
prefixXor:  [4,  6,  4,  2,  6]

Map evolution:
i=0: prefixXor=4, target=4^6=2, count=0, map={0:1, 4:1}
i=1: prefixXor=6, target=6^6=0, count=1 (found 0), map={0:1, 4:1, 6:1}
i=2: prefixXor=4, target=4^6=2, count=1, map={0:1, 4:2, 6:1}
i=3: prefixXor=2, target=2^6=4, count=3 (found 4 twice), map={0:1, 4:2, 6:1, 2:1}
i=4: prefixXor=6, target=6^6=0, count=4 (found 0), map={0:1, 4:2, 6:2, 2:1}

Result: 4 subarrays
- [4,2] (i=0 to 1): XOR = 4^2 = 6
- [2,2,6] (i=1 to 3): XOR = 2^2^6 = 6
- [6] (i=3): XOR = 6
- [4,2,2,6,4] (i=0 to 4): XOR = 4^2^2^6^4 = 6

Time Complexity: O(n)
Space Complexity: O(n) for hash map
*/
