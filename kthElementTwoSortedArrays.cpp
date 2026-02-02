class Solution {
public:
    int kthElement(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size(), n2 = nums2.size();
        
        // Ensure nums1 is the smaller array for efficiency
        if (n1 > n2)
            return kthElement(nums2, nums1, k);
        
        // Binary search on the smaller array
        int low = max(0, k - n2), high = min(k, n1);
        
        while (low <= high) {
            int mid1 = (low + high) >> 1;  // Number of elements from nums1
            int mid2 = k - mid1;            // Number of elements from nums2
            
            int l1 = INT_MIN, l2 = INT_MIN;
            int r1 = INT_MAX, r2 = INT_MAX;
            
            // Get the boundary elements
            if (mid1 > 0) l1 = nums1[mid1 - 1];
            if (mid2 > 0) l2 = nums2[mid2 - 1];
            if (mid1 < n1) r1 = nums1[mid1];
            if (mid2 < n2) r2 = nums2[mid2];
            
            // Check if we found the correct partition
            if (l1 <= r2 && l2 <= r1) {
                // k-th element is the maximum of left partition
                return max(l1, l2);
            }
            else if (l1 > r2) {
                // Too many elements from nums1, move left
                high = mid1 - 1;
            }
            else {
                // Too few elements from nums1, move right
                low = mid1 + 1;
            }
        }
        
        return 0;
    }
};

// Time Complexity: O(log(min(n1, n2)))
// Space Complexity: O(1)

// Problem: Given two sorted arrays nums1 and nums2 of sizes n1 and n2 respectively,
// find the k-th element (1-indexed) in the merged sorted array.
//
// Approach: Binary Search on Smaller Array
// 1. Perform binary search on the smaller array to optimize time complexity
// 2. For each mid1, calculate mid2 = k - mid1 (total k elements in left partition)
// 3. Get boundary elements: l1, l2 (left partition max), r1, r2 (right partition min)
// 4. Valid partition: l1 <= r2 && l2 <= r1
//    - k-th element = max(l1, l2)
// 5. If l1 > r2: too many from nums1, search left half
// 6. If l2 > r1: too few from nums1, search right half
//
// Edge cases handled:
// - low = max(0, k - n2): ensure we don't take negative elements from nums1
// - high = min(k, n1): ensure we don't exceed nums1 size
//
// Example:
// nums1 = [2, 3, 6, 7, 9], nums2 = [1, 4, 8, 10], k = 5
// Merged: [1, 2, 3, 4, 6, 7, 8, 9, 10]
// 5-th element (1-indexed) = 6
