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
    bool isLeaf(TreeNode* node) {
        return node && !node->left && !node->right;
    }

    void addLeftBoundary(TreeNode* node, vector<int>& res) {
        TreeNode* curr = node->left;
        while (curr) {
            if (!isLeaf(curr)) res.push_back(curr->val);
            if (curr->left) curr = curr->left;
            else curr = curr->right;
        }
    }

    void addLeaves(TreeNode* node, vector<int>& res) {
        if (!node) return;
        if (isLeaf(node)) {
            res.push_back(node->val);
            return;
        }
        addLeaves(node->left, res);
        addLeaves(node->right, res);
    }

    void addRightBoundary(TreeNode* node, vector<int>& res) {
        TreeNode* curr = node->right;
        vector<int> tmp;
        while (curr) {
            if (!isLeaf(curr)) tmp.push_back(curr->val);
            if (curr->right) curr = curr->right;
            else curr = curr->left;
        }
        reverse(tmp.begin(), tmp.end());
        res.insert(res.end(), tmp.begin(), tmp.end());
    }

    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        if (!isLeaf(root)) res.push_back(root->val);
        addLeftBoundary(root, res);
        addLeaves(root, res);
        addRightBoundary(root, res);
        return res;
    }
};

/*
LeetCode-style Question:
------------------------
Given the root of a binary tree, return the values of its boundary in anti-clockwise direction starting from the root.

The boundary includes:
1. The left boundary (excluding leaves)
2. All the leaves (left to right)
3. The right boundary (excluding leaves, in reverse order)

Return the boundary values as a list in anti-clockwise order.

Example:
Input: root = [1,2,3,4,5,6,7,8,9,10,11]
Output: [1,2,4,8,9,10,11,7,6,3]

Constraints:
- The number of nodes in the tree is in the range [1, 10^4].
- -1000 <= Node.val <= 1000
*/
