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
    // LeetCode 106: Construct Binary Tree from Inorder and Postorder Traversal
    TreeNode* buildTreeInPost(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> inMap;
        for (int i = 0; i < inorder.size(); i++) {
            inMap[inorder[i]] = i;
        }
        return buildInPost(inorder, 0, inorder.size() - 1,
                           postorder, 0, postorder.size() - 1, inMap);
    }
    
private:
    TreeNode* buildInPost(vector<int>& inorder, int inStart, int inEnd,
                          vector<int>& postorder, int postStart, int postEnd,
                          unordered_map<int, int>& inMap) {
        if (inStart > inEnd || postStart > postEnd) return nullptr;
        
        TreeNode* root = new TreeNode(postorder[postEnd]);
        int inRoot = inMap[root->val];
        int numsLeft = inRoot - inStart;
        
        root->left = buildInPost(inorder, inStart, inRoot - 1,
                                 postorder, postStart, postStart + numsLeft - 1, inMap);
        root->right = buildInPost(inorder, inRoot + 1, inEnd,
                                  postorder, postStart + numsLeft, postEnd - 1, inMap);
        
        return root;
    }
};

/*
LeetCode 106: Construct Binary Tree from Inorder and Postorder Traversal
-------------------------------------------------------------------------
Given two integer arrays inorder and postorder where:
- inorder is the inorder traversal of a binary tree
- postorder is the postorder traversal of the same tree

Construct and return the binary tree.

Example 1:
Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]

Example 2:
Input: inorder = [-1], postorder = [-1]
Output: [-1]

Constraints:
- 1 <= inorder.length <= 3000
- postorder.length == inorder.length
- -3000 <= inorder[i], postorder[i] <= 3000
- inorder and postorder consist of unique values.
- Each value of postorder also appears in inorder.
- inorder is guaranteed to be the inorder traversal of the tree.
- postorder is guaranteed to be the postorder traversal of the tree.

Algorithm:
1. Last element in postorder is always root
2. Find root in inorder to determine left and right subtrees
3. Elements to left of root in inorder = left subtree
4. Elements to right of root in inorder = right subtree
5. Recursively build left and right subtrees

Key Difference from Preorder approach:
- Preorder: root is at START → process left first
- Postorder: root is at END → process right first (but we build left first in recursion)

Time: O(n), Space: O(n)
*/
