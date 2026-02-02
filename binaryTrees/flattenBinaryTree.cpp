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
private:
    TreeNode* prev = nullptr;
    
public:
    // LeetCode 114: Flatten Binary Tree to Linked List
    // Approach 1: Using prev pointer (Reverse Postorder)
    void flatten(TreeNode* root) {
        if (!root) return;
        
        // Process in reverse preorder: right -> left -> root
        flatten(root->right);
        flatten(root->left);
        
        // Connect current node
        root->right = prev;
        root->left = nullptr;
        prev = root;
    }
    
    // Approach 2: Using Morris Traversal (O(1) space)
    void flattenMorris(TreeNode* root) {
        TreeNode* curr = root;
        
        while (curr) {
            if (curr->left) {
                // Find the rightmost node in left subtree
                TreeNode* rightmost = curr->left;
                while (rightmost->right) {
                    rightmost = rightmost->right;
                }
                
                // Connect rightmost to current's right
                rightmost->right = curr->right;
                
                // Move left subtree to right
                curr->right = curr->left;
                curr->left = nullptr;
            }
            
            // Move to next node
            curr = curr->right;
        }
    }
    
    // Approach 3: Using Stack (Preorder)
    void flattenStack(TreeNode* root) {
        if (!root) return;
        
        stack<TreeNode*> st;
        st.push(root);
        
        while (!st.empty()) {
            TreeNode* curr = st.top();
            st.pop();
            
            if (curr->right) st.push(curr->right);
            if (curr->left) st.push(curr->left);
            
            if (!st.empty()) {
                curr->right = st.top();
            }
            curr->left = nullptr;
        }
    }
};

/*
LeetCode 114: Flatten Binary Tree to Linked List
-------------------------------------------------
Given the root of a binary tree, flatten the tree into a "linked list":
- The "linked list" should use the same TreeNode class where the right child pointer points to the next node 
  in the list and the left child pointer is always null.
- The "linked list" should be in the same order as a preorder traversal of the binary tree.

Example 1:
Input: root = [1,2,5,3,4,null,6]
    1
   / \
  2   5
 / \   \
3   4   6

Output: [1,null,2,null,3,null,4,null,5,null,6]
1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [0]
Output: [0]

Constraints:
- The number of nodes in the tree is in the range [0, 2000].
- -100 <= Node.val <= 100

Follow up: Can you flatten the tree in-place (with O(1) extra space)?

-----------------------------------------------------------
APPROACH COMPARISON:
-----------------------------------------------------------

1. prev Pointer (BEST - Elegant Recursion):
   - Use global/class prev pointer to track last processed node
   - Process in reverse preorder: right -> left -> root
   - Connect current node's right to prev, set left to null
   - Update prev to current
   - Time: O(n), Space: O(n) recursion stack
   - Cleanest and most intuitive approach!

2. Morris Traversal (O(1) space):
   - Find rightmost node in left subtree
   - Connect it to current's right subtree
   - Move left subtree to right
   - Set left to null
   - Move to next node
   - Time: O(n), Space: O(1)

3. Stack (Preorder):
   - Use stack to simulate preorder traversal
   - Push right then left (so left is processed first)
   - Connect nodes in preorder
   - Time: O(n), Space: O(n) for stack

Key Insight:
The flattened tree follows preorder traversal order (root -> left -> right).
Processing in reverse preorder (right -> left -> root) with prev pointer is most elegant!
*/


