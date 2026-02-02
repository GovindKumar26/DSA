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
    int widthOfBinaryTree(TreeNode* root) {
       if (root == NULL)
            return 0;
            
        int ans = 0;
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push(make_pair(root, 0));

        while (!q.empty()) {
            int size = q.size();
            unsigned long long mmin = q.front().second;
            unsigned long long first, last;

            for (int i = 0; i < size; i++) {
                unsigned long long cur_id = q.front().second - mmin;
                TreeNode* node = q.front().first;
                q.pop();
                if (i == 0)
                    first = cur_id;
                if (i == size - 1)
                    last = cur_id;
                if (node->left) {
                    q.push(make_pair(node->left, cur_id * 2 + 1));
                }
                if (node->right) {
                    q.push(make_pair(node->right, cur_id * 2 + 2));
                }
            }
            ans = max((unsigned long long)ans, last - first + 1);
        }
        return ans;
    }
};

/*
LeetCode 662: Maximum Width of Binary Tree
-------------------------------------------
Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), 
where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that 
level are also counted into the length calculation.

Example 1:
Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).

Example 2:
Input: root = [1,3,2,5,null,null,9,6,null,7]
Output: 7
Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).

Example 3:
Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width exists in the second level with length 2 (3,2).

Constraints:
- The number of nodes in the tree is in the range [1, 3000].
- -100 <= Node.val <= 100
*/
