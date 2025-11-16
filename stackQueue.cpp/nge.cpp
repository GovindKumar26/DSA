#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> nextLargerElement(vector<int>& arr) {
        int n = arr.size();
        vector<int> ans(n, -1);
        stack<int> st; // stores potential next greater elements

        for (int i = n - 1; i >= 0; i--) {
            // Pop elements smaller or equal to arr[i]
            while (!st.empty() && st.top() <= arr[i]) {
                st.pop();
            }

            // If stack not empty, top is next greater
            if (!st.empty()) {
                ans[i] = st.top();
            }

            // Push current element onto stack
            st.push(arr[i]);
        }

        return ans;
    }
};





// circular array
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> st;  // stores values (not indices, since circular check works in 2 passes)

        for (int i = 2*n - 1; i >= 0; i--) {
            int num = nums[i % n];

            // Pop all smaller or equal elements
            while (!st.empty() && st.top() <= num) {
                st.pop();
            }

            // Assign answer only in the first pass
            if (i < n) {
                ans[i] = st.empty() ? -1 : st.top();
            }

            // Push current element
            st.push(num);
        } 

        return ans;
    }
};