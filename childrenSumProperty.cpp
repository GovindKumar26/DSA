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
    bool isSumProperty(TreeNode* root) {
        if(root == nullptr) return true;
        if(root->left == nullptr && root->right == nullptr) return true;
        
        int ldata = root->left ? root->left->val : 0;
        int rdata = root->right ? root->right->val : 0;
        
        bool l = isSumProperty(root->left);
        bool r = isSumProperty(root->right);
        
        return l && r && (ldata + rdata == root->val);
    }
};

/*
Children Sum Property in Binary Tree
-------------------------------------
Given a binary tree, check whether it satisfies the Children Sum Property.

Children Sum Property: For every node, the value of the node should be equal to the sum of values of its children 
(left child + right child). For leaf nodes, the sum is considered as 0.

Example 1:
Input: 
       10
      /  \
     8    2
    / \  / \
   3  5  2  0
Output: true
Explanation: For every node, the value equals sum of left and right children.
10 = 8 + 2, 8 = 3 + 5, 2 = 2 + 0

Example 2:
Input:
       10
      /  \
     8    3
Output: false
Explanation: 10 ≠ 8 + 3

Constraints:
- The number of nodes in the tree is in the range [1, 10^5].
- -10^9 <= Node.val <= 10^9
*/
