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
    // Zig Zag (Spiral) Level Order Traversal
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size);
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                int idx = leftToRight ? i : (size - 1 - i);
                level[idx] = node->val;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(level);
            leftToRight = !leftToRight;
        }
        return result;
    }
};

/*
LeetCode-style Question:
------------------------
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

Example:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]

Constraints:
- The number of nodes in the tree is in the range [0, 2000].
- -100 <= Node.val <= 100
*/
