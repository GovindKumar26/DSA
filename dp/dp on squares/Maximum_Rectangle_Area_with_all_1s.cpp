// Maximum Rectangle Area with all 1s (DP-55) - LC 85
// Problem: Find largest rectangle containing only 1s in binary matrix.

#include <bits/stdc++.h>
using namespace std;

int largestRectangleHistogram(vector<int>& heights) {
    stack<int> st;
    int maxArea = 0;
    int n = heights.size();
    
    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }
    
    while (!st.empty()) {
        int h = heights[st.top()];
        st.pop();
        int width = st.empty() ? n : n - st.top() - 1;
        maxArea = max(maxArea, h * width);
    }
    
    return maxArea;
}

int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    
    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> heights(m, 0);
    int maxArea = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == '1') {
                heights[j]++;
            } else {
                heights[j] = 0;
            }
        }
        maxArea = max(maxArea, largestRectangleHistogram(heights));
    }
    
    return maxArea;
}

int main() {
    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    cout << "Maximum rectangle area: " << maximalRectangle(matrix) << endl;
    return 0;
}

// Time Complexity: O(n*m)
// Space Complexity: O(m)