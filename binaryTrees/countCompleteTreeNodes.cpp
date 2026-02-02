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
    int countNodes(TreeNode* root) {
        // Your code here
         if (!root) return 0;

        // compute leftmost depth
        int leftDepth = 0;
        TreeNode* p = root;
        while (p) {
            ++leftDepth;
            p = p->left;
        }

        // compute rightmost depth
        int rightDepth = 0;
        p = root;
        while (p) {
            ++rightDepth;
            p = p->right;
        }

        // if perfect tree
        if (leftDepth == rightDepth) {
            // Use 64-bit shift to avoid overflow
            return static_cast<int>((1ULL << leftDepth) - 1);
        }

        // otherwise recurse on subtrees
        return 1 + countNodes(root->left) + countNodes(root->right);

    }
};

/*
LeetCode 222: Count Complete Tree Nodes
----------------------------------------
Given the root of a complete binary tree, return the number of the nodes in the tree.

A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, 
and all nodes in the last level are as far left as possible. It can have between 1 and 2^h nodes inclusive 
at the last level h.

Design an algorithm that runs in less than O(n) time complexity.

Example 1:
Input: root = [1,2,3,4,5,6]
Output: 6

Example 2:
Input: root = []
Output: 0

Example 3:
Input: root = [1]
Output: 1

Constraints:
- The number of nodes in the tree is in the range [0, 5 * 10^4].
- 0 <= Node.val <= 5 * 10^4
- The tree is guaranteed to be complete.

Approach:
1. Simple O(n): Traverse all nodes and count
2. Optimized O(log^2 n): Use complete tree property
   - If left height == right height → left subtree is perfect, use formula 2^h - 1
   - Otherwise, recursively count both subtrees
*/
