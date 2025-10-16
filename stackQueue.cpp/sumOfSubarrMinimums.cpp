class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> PSE(n), NSE(n);
        stack<int> st;

        // Previous Smaller Element
        for(int i = 0; i < n; i++){
            while(!st.empty() && arr[st.top()] > arr[i]) st.pop(); // strictly smaller
            PSE[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        while(!st.empty()) st.pop();

        // Next Smaller Element
        for(int i = n-1; i >= 0; i--){
            while(!st.empty() && arr[st.top()] >= arr[i]) st.pop(); // next smaller or equal
            NSE[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        long res = 0, mod = 1e9+7;
        for(int i = 0; i < n; i++){
            long left = i - PSE[i];
            long right = NSE[i] - i;
            res = (res + arr[i]*left*right) % mod;
        }

        return res;
    }
};

// Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 10^9 + 7.
// time complexity: O(n)
// space complexity: O(n)
// 