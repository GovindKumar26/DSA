class Solution {
public:
    int trap(vector<int>& height) {
        // int n = height.size();

        // vector<int> prefixMax(n, -1), suffixMax(n, -1);

        // prefixMax[0] = height[0], suffixMax[n-1] = height[n-1];

        // for(int i=1 ; i<n ; i++) {
        //     prefixMax[i] = max(prefixMax[i-1], height[i]);
        //     suffixMax[n-i-1] = max(suffixMax[n-i], height[n-1-i]);
        // }

        // int total = 0;
        // for(int i=0 ; i<n ; i++) {
        //     int leftMax = prefixMax[i], rightMax = suffixMax[i];
        //     if(height[i] < leftMax && height[i] < rightMax) {
        //         total += min(leftMax, rightMax) - height[i]; 
        //     }
        // }

        // return total;



        int n = height.size();
        int left = 0, right = n-1;
        int leftMax = 0, rightMax = 0;
        int total = 0;

        while(left <= right) {
            if(height[left] < height[right]) {
                if(height[left] >= leftMax)
                    leftMax = height[left];
                else
                    total += leftMax - height[left];
                left++;
            }  else {
                if(height[right] >= rightMax)
                    rightMax = height[right];
                else
                    total += rightMax - height[right];
                right--;
            }
        }

        return total;


    }
};

// Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
// time complexity: O(n)    
// space complexity: O(1)
// Approach: Use two pointers to traverse the height array from both ends. Maintain two variables, leftMax and rightMax, to keep track of the maximum heights encountered from the left and right sides, respectively. At each step, compare the heights at the left and right pointers. Move the pointer with the smaller height inward, updating the corresponding max variable and calculating the trapped water at that position if the current height is less than the max. This approach ensures that we only traverse the array once, achieving O(n) time complexity with O(1) space complexity.
// The key insight is that the amount of water that can be trapped at any position is determined by the shorter of the two maximum heights (leftMax and rightMax) minus the height at that position. By always moving the pointer with the smaller height, we ensure that we are working with a valid boundary for trapping water.