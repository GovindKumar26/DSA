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
    // Version 1: Check if tree satisfies children sum property
    bool isSumProperty(TreeNode* root) {
        if(root == nullptr) return true;
        if(root->left == nullptr && root->right == nullptr) return true;
        
        int ldata = root->left ? root->left->val : 0;
        int rdata = root->right ? root->right->val : 0;
        
        bool l = isSumProperty(root->left);
        bool r = isSumProperty(root->right);
        
        return l && r && (ldata + rdata == root->val);
    }
    
    // Version 2: Modify tree to satisfy children sum property
    void changeTree(TreeNode* root) {
        if(root == nullptr) return;
        
        int child = 0;
        if(root->left) child += root->left->val;
        if(root->right) child += root->right->val;
        
        // If children sum is less than current node value,
        // increase children to match parent
        if(child >= root->val) {
            root->val = child;
        } else {
            // If children sum is less, increase children values
            if(root->left) root->left->val = root->val;
            if(root->right) root->right->val = root->val;
        }
        
        // Recursively process left and right subtrees
        changeTree(root->left);
        changeTree(root->right);
        
        // After processing children, update current node
        // to be sum of its children
        int total = 0;
        if(root->left) total += root->left->val;
        if(root->right) total += root->right->val;
        
        // Only update if not a leaf node
        if(root->left || root->right) {
            root->val = total;
        }
    }
};

/*
Children Sum Property in Binary Tree
-------------------------------------
Given a binary tree, check whether it satisfies the Children Sum Property.

Children Sum Property: For every node, the value of the node should be equal to the sum of values of its children 
(left child + right child). For leaf nodes, the sum is considered as 0.

Example 1 (isSumProperty):
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

---

MODIFICATION VERSION (changeTree):
Given a binary tree, modify it to satisfy the children sum property. Rules:
- You can only increment node values (cannot decrement)
- You can increment a node value any number of times

Example:
Input:
       50
      /  \
    20   30
   / \
  10  5

Process:
1. At root: child sum = 20+30 = 50, already equal ✓
2. At 20: child sum = 10+5 = 15 < 20, so increase children to 20
   - Set left = 20, right = 20 (or distribute)
3. Recursively process and backtrack
4. Update parent = sum of children on the way back

Output:
       50
      /  \
    25   25
   / \
  12  13

Algorithm:
- If child sum >= parent: update parent = child sum
- If child sum < parent: increase children to match parent
- Process subtrees recursively
- On backtrack: update parent = sum of children

Time: O(N), Space: O(H)

Constraints:
- The number of nodes in the tree is in the range [1, 10^5].
- -10^9 <= Node.val <= 10^9
*/
