#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Approach 1: Brute Force - Copy all elements and sort
    // Time: O((m+n) log(m+n)), Space: O(1)
    void mergeBruteForce(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // Copy all elements from nums2 to end of nums1
        for (int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }
        
        // Sort the entire array
        sort(nums1.begin(), nums1.end());
    }
    
    // Approach 2: Using Extra Space - Two Pointer from start
    // Time: O(m+n), Space: O(m+n)
    void mergeExtraSpace(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> temp(m + n);
        int i = 0, j = 0, k = 0;
        
        // Merge elements from both arrays
        while (i < m && j < n) {
            if (nums1[i] <= nums2[j]) {
                temp[k++] = nums1[i++];
            } else {
                temp[k++] = nums2[j++];
            }
        }
        
        // Copy remaining elements from nums1
        while (i < m) {
            temp[k++] = nums1[i++];
        }
        
        // Copy remaining elements from nums2
        while (j < n) {
            temp[k++] = nums2[j++];
        }
        
        // Copy back to nums1
        for (int i = 0; i < m + n; i++) {
            nums1[i] = temp[i];
        }
    }
    
    // Approach 3: Swap and Sort Method
    // Time: O((m+n) log(m+n)), Space: O(1)
    void mergeSwapAndSort(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // First copy nums2 to end of nums1
        for (int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }
        
        // Two pointers: left at end of first part, right at start of second part
        int left = m - 1;
        int right = m;
        
        // Swap elements to ensure all elements in first part <= all in second part
        while (left >= 0 && right < m + n) {
            if (nums1[left] > nums1[right]) {
                swap(nums1[left], nums1[right]);
                left--;
                right++;
            } else {
                break;
            }
        }
        
        // Sort both parts separately
        sort(nums1.begin(), nums1.begin() + m);
        sort(nums1.begin() + m, nums1.end());
    }
    
    // Approach 4: Gap Method (Shell Sort inspired)
    // Time: O((m+n) log(m+n)), Space: O(1)
    void mergeGapMethod(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // First copy nums2 to end of nums1
        for (int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }
        
        int total = m + n;
        int gap = (total + 1) / 2;
        
        while (gap > 0) {
            int left = 0;
            int right = left + gap;
            
            while (right < total) {
                if (nums1[left] > nums1[right]) {
                    swap(nums1[left], nums1[right]);
                }
                left++;
                right++;
            }
            
            if (gap == 1) break;
            gap = (gap + 1) / 2;
        }
    }
    
    // Approach 5: OPTIMAL - Two Pointer from End (In-place)
    // Time: O(m+n), Space: O(1)
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;      // Last element of nums1's valid part
        int j = n - 1;      // Last element of nums2
        int k = m + n - 1;  // Last position of nums1
        
        // Fill nums1 from the end
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
        
        // Copy remaining elements from nums2 (if any)
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
        
        // No need to copy remaining from nums1 as they're already in place
    }
};

void printArray(vector<int>& arr, int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ",";
    }
    cout << "]";
}

int main() {
    Solution sol;
    
    cout << "===== Approach 1: Brute Force (Copy and Sort) =====" << endl;
    vector<int> nums1_1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2_1 = {2, 5, 6};
    cout << "Before: nums1 = ";
    printArray(nums1_1, 6);
    cout << ", nums2 = ";
    printArray(nums2_1, 3);
    cout << endl;
    sol.mergeBruteForce(nums1_1, 3, nums2_1, 3);
    cout << "After: ";
    printArray(nums1_1, 6);
    cout << "\n" << endl;
    
    cout << "===== Approach 2: Using Extra Space =====" << endl;
    vector<int> nums1_2 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2_2 = {2, 5, 6};
    cout << "Before: nums1 = ";
    printArray(nums1_2, 6);
    cout << ", nums2 = ";
    printArray(nums2_2, 3);
    cout << endl;
    sol.mergeExtraSpace(nums1_2, 3, nums2_2, 3);
    cout << "After: ";
    printArray(nums1_2, 6);
    cout << "\n" << endl;
    
    cout << "===== Approach 3: Swap and Sort =====" << endl;
    vector<int> nums1_3 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2_3 = {2, 5, 6};
    cout << "Before: nums1 = ";
    printArray(nums1_3, 6);
    cout << ", nums2 = ";
    printArray(nums2_3, 3);
    cout << endl;
    sol.mergeSwapAndSort(nums1_3, 3, nums2_3, 3);
    cout << "After: ";
    printArray(nums1_3, 6);
    cout << "\n" << endl;
    
    cout << "===== Approach 4: Gap Method =====" << endl;
    vector<int> nums1_4 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2_4 = {2, 5, 6};
    cout << "Before: nums1 = ";
    printArray(nums1_4, 6);
    cout << ", nums2 = ";
    printArray(nums2_4, 3);
    cout << endl;
    sol.mergeGapMethod(nums1_4, 3, nums2_4, 3);
    cout << "After: ";
    printArray(nums1_4, 6);
    cout << "\n" << endl;
    
    cout << "===== Approach 5: OPTIMAL (Two Pointer from End) =====" << endl;
    vector<int> nums1_5 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2_5 = {2, 5, 6};
    cout << "Before: nums1 = ";
    printArray(nums1_5, 6);
    cout << ", nums2 = ";
    printArray(nums2_5, 3);
    cout << endl;
    sol.merge(nums1_5, 3, nums2_5, 3);
    cout << "After: ";
    printArray(nums1_5, 6);
    cout << "\n" << endl;
    
    // Test case 2
    cout << "===== Test Case 2 (OPTIMAL) =====" << endl;
    vector<int> nums1_6 = {1};
    vector<int> nums2_6 = {};
    cout << "Before: nums1 = ";
    printArray(nums1_6, 1);
    cout << ", nums2 = []" << endl;
    sol.merge(nums1_6, 1, nums2_6, 0);
    cout << "After: ";
    printArray(nums1_6, 1);
    cout << "\n" << endl;
    
    // Test case 3
    cout << "===== Test Case 3 (OPTIMAL) =====" << endl;
    vector<int> nums1_7 = {0};
    vector<int> nums2_7 = {1};
    cout << "Before: nums1 = [0], nums2 = [1]" << endl;
    sol.merge(nums1_7, 0, nums2_7, 1);
    cout << "After: ";
    printArray(nums1_7, 1);
    cout << endl;
    
    return 0;
}

/*
===============================================
DETAILED EXPLANATION OF ALL APPROACHES
===============================================

Problem: Merge two sorted arrays nums1 and nums2 into nums1 in-place.
- nums1 has size m+n (first m elements are valid, rest are 0s)
- nums2 has size n

Example: nums1 = [1,2,3,0,0,0], m = 3
         nums2 = [2,5,6], n = 3
Output:  nums1 = [1,2,2,3,5,6]

===============================================
APPROACH 1: BRUTE FORCE
===============================================
Algorithm:
1. Copy all elements from nums2 to the end of nums1
2. Sort the entire nums1 array

Time: O((m+n) log(m+n)) - due to sorting
Space: O(1) - in-place sorting

Pros: Simple, straightforward
Cons: Not efficient, doesn't utilize the fact that arrays are already sorted

===============================================
APPROACH 2: EXTRA SPACE
===============================================
Algorithm:
1. Create temporary array of size m+n
2. Use two pointers to merge elements from both arrays
3. Copy result back to nums1

Time: O(m+n) - single pass through both arrays
Space: O(m+n) - temporary array

Pros: O(n) time complexity
Cons: Uses extra space

Step-by-step for [1,2,3] and [2,5,6]:
i=0, j=0: 1 < 2 → temp[0]=1, i=1
i=1, j=0: 2 = 2 → temp[1]=2, i=2
i=2, j=1: 3 < 5 → temp[2]=3, i=3
i=3 (done), j=1: temp[3]=5, j=2
j=2: temp[4]=6, j=3
Result: [1,2,3,5,6] ✗ Wait, let me recalculate...

Actually:
i=0, j=0: nums1[0]=1, nums2[0]=2 → 1≤2, temp[0]=1, i=1
i=1, j=0: nums1[1]=2, nums2[0]=2 → 2≤2, temp[1]=2, i=2
i=2, j=1: nums1[2]=3, nums2[1]=5 → 3≤5, temp[2]=3, i=3
i=3 (done), copy remaining from nums2:
temp[3]=2, temp[4]=5, temp[5]=6
Wait, j should be 0 still...

Let me trace again:
nums1=[1,2,3,0,0,0], m=3
nums2=[2,5,6], n=3

i=0, j=0: 1≤2 → temp[0]=1, i=1, k=1
i=1, j=0: 2≤2 → temp[1]=2, i=2, k=2
i=2, j=0: 3>2 → temp[2]=2, j=1, k=3
i=2, j=1: 3≤5 → temp[3]=3, i=3, k=4
i=3 (done), j=1: temp[4]=5, j=2, k=5
j=2: temp[5]=6, j=3
Result: [1,2,2,3,5,6] ✓

===============================================
APPROACH 3: SWAP AND SORT METHOD
===============================================
Algorithm:
1. Copy nums2 to end of nums1
2. Use two pointers: left at end of first part, right at start of second
3. While arr1[left] > arr2[right], swap them and move pointers
4. Sort both parts separately

Time: O((m+n) log(m+n)) - due to sorting both parts
Space: O(1) - in-place

Pros: Efficient swapping reduces work needed for sorting
Cons: Still requires sorting after swapping

Step-by-step for [1,2,3] and [2,5,6]:
After copying: [1,2,3,2,5,6]
left=2 (idx 2, val=3), right=3 (idx 3, val=2)
3>2 → swap → [1,2,2,3,5,6], left=1, right=4
2<5 → break
Sort [1,2] and [2,3,5,6]
Result: [1,2,2,3,5,6] ✓

This approach ensures all elements in first part ≤ all in second part
before sorting, which can optimize the sorting step.

===============================================
APPROACH 4: GAP METHOD (Shell Sort)
===============================================
Algorithm:
1. Copy nums2 to end of nums1
2. Use decreasing gaps to compare and swap elements
3. Start with gap = ceil((m+n)/2), reduce to gap/2 each iteration

Time: O((m+n) log(m+n))
Space: O(1)

Pros: In-place, interesting technique
Cons: Not as efficient as optimal approach

===============================================
APPROACH 5: OPTIMAL (Two Pointer from End)
===============================================
Algorithm:
1. Start from the end of both arrays
2. Compare elements and place larger one at the end of nums1
3. Move backwards, filling nums1 from right to left

Time: O(m+n) - single pass
Space: O(1) - truly in-place

This is OPTIMAL because:
- Uses the fact that arrays are already sorted
- Fills from end, avoiding overwriting needed elements
- No extra space needed
- Linear time complexity

Step-by-step for [1,2,3,0,0,0] and [2,5,6]:
           i           j           k
Initial:   2(idx 2)    2(idx 2)    5(idx 5)
nums1[2]=3, nums2[2]=6 → 6>3, nums1[5]=6, j=1, k=4
nums1[2]=3, nums2[1]=5 → 5>3, nums1[4]=5, j=0, k=3
nums1[2]=3, nums2[0]=2 → 3>2, nums1[3]=3, i=1, k=2
nums1[1]=2, nums2[0]=2 → 2=2, nums1[2]=2, j=-1, k=1
j<0, done (remaining nums1 elements already in place)

Result: [1,2,2,3,5,6] ✓

Why start from end?
- Starting from beginning would overwrite nums1 elements we haven't processed yet
- Starting from end, we have empty space (the 0s) to fill
- Larger elements naturally go to the end

===============================================
COMPARISON SUMMARY
===============================================
Approach          Time              Space    In-place?  Optimal?
Brute Force       O(n log n)       O(1)      Yes        No
Extra Space       O(n)             O(n)      No         No
Swap & Sort       O(n log n)       O(1)      Yes        No
Gap Method        O(n log n)       O(1)      Yes        No
Two Ptr from End  O(n)             O(1)      Yes        YES ✓

Best Approach: Two Pointer from End
- Linear time: O(m+n)
- Constant space: O(1)
- Truly in-place
- Elegant and efficient
*/
