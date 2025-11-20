#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // TODO: Complete this function
    vector<vector<int>> verticalOrder(TreeNode* root) {
        // Your code here
        
    }
};

/*
LeetCode-style Question:
------------------------
Given the root of a binary tree, return the vertical order traversal of its nodes' values.

For each node at position (row, col), its left child is at (row+1, col-1) and its right child is at (row+1, col+1).

Return a list of lists of integers representing the vertical order traversal from leftmost column to rightmost column.

Example:
Input: root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]

Constraints:
- The number of nodes in the tree is in the range [0, 1000].
- -100 <= Node.val <= 100
*/
