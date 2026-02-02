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
    // Morris Inorder Traversal: O(1) space, O(n) time
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* curr = root;
        while (curr) {
            if (!curr->left) {
                result.push_back(curr->val);
                curr = curr->right;
            } else {
                TreeNode* pred = curr->left;
                while (pred->right && pred->right != curr) {
                    pred = pred->right;
                }
                if (!pred->right) {
                    pred->right = curr;
                    curr = curr->left;
                } else {
                    pred->right = nullptr;
                    result.push_back(curr->val);
                    curr = curr->right;
                }
            }
        }
        return result;
    }
};

/*
Morris Inorder Traversal:
- O(1) space (no stack, no recursion)
- Uses threaded binary tree: temporarily modifies tree structure
- Restores tree after traversal

Steps:
1. For each node, if left child is null, visit node and go right
2. If left child exists, find rightmost node in left subtree (predecessor)
   - If predecessor's right is null, set it to current node, go left
   - If predecessor's right is current node, restore to null, visit node, go right
*/
