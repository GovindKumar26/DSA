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

  TreeNode* findTarget(TreeNode* root, int target) {
        if (root == NULL)
            return nullptr;
        if (root->val == target)
            return root;

        TreeNode* leftSearch = findTarget(root->left, target);
        if (leftSearch)
            return leftSearch;

        TreeNode* rightSearch = findTarget(root->right, target);
        if (rightSearch)
            return rightSearch;

            return nullptr;
    }

    void markParents(TreeNode* root,
                     unordered_map<TreeNode*, TreeNode*>& parent_track,
                     TreeNode* target) {
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            if (current->left) {
                parent_track[current->left] = current;
                q.push(current->left);
            }
            if (current->right) {
                parent_track[current->right] = current;
                q.push(current->right);
            }
        }
    }

    // TODO: Complete this function
    int minTimeToBurn(TreeNode* root, int target) {
        TreeNode* targetNode = findTarget(root, target);
        if (!targetNode) return 0;

        unordered_map<TreeNode*, TreeNode*> parent_track;
        markParents(root, parent_track, targetNode);

        unordered_map<TreeNode*, bool> visited;
        queue<TreeNode*> q;
        q.push(targetNode);
        visited[targetNode] = true;
        int cur_level = 0;

        while (!q.empty()) {
            int size = q.size();
            bool burned = false;

            for (int i = 0; i < size; i++) {
                TreeNode* current = q.front();
                q.pop();

                if (current->left && !visited[current->left]) {
                    q.push(current->left);
                    visited[current->left] = true;
                    burned = true;
                }

                if (current->right && !visited[current->right]) {
                    q.push(current->right);
                    visited[current->right] = true;
                    burned = true;
                }

                if (parent_track[current] && !visited[parent_track[current]]) {
                    q.push(parent_track[current]);
                    visited[parent_track[current]] = true;
                    burned = true;
                }
            }
            
            if (burned) cur_level++;
        }

        return cur_level;
    }
};

/*
Minimum Time to Burn Binary Tree from a Node
---------------------------------------------
Given a binary tree and a target node value, find the minimum time required to burn the entire tree if fire starts 
from the target node.

The fire spreads from a node to its adjacent nodes (left child, right child, and parent) in 1 unit of time.

Example 1:
Input: 
          1
        /   \
       2     3
      / \     \
     4   5     6
            / \
           7   8
target = 5
Output: 4
Explanation: 
- At time 0: Node 5 burns
- At time 1: Nodes 2 and 6 burn (adjacent to 5 through parent path)
- At time 2: Nodes 1, 4 burn
- At time 3: Node 3 burns
- At time 4: Nodes 7, 8 burn
Total time = 4

Example 2:
Input:
     1
    / \
   2   3
target = 2
Output: 2
Explanation:
- Time 0: Node 2 burns
- Time 1: Node 1 burns
- Time 2: Node 3 burns

Constraints:
- 1 <= Number of nodes <= 10^5
- 1 <= Node.val <= 10^5
- The target value exists in the tree.

Approach:
1. Build parent pointers for all nodes
2. Find the target node
3. Do BFS from target treating tree as undirected graph
4. Track visited nodes to avoid cycles
5. Count levels - that's the burn time
*/
