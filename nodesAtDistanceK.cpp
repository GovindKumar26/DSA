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

   void markParents(TreeNode* root,  unordered_map<TreeNode*, TreeNode*> &parent_track, TreeNode* target){
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* current = q.front();
            q.pop();
            if(current->left){
                parent_track[current->left] = current;
                q.push(current->left);
            }
            if(current->right){
                parent_track[current->right] = current;
                q.push(current->right);
            }
        }
    }
    // TODO: Complete this function
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        // Your code here
         unordered_map<TreeNode*, TreeNode*> parent_track;
        markParents(root, parent_track, target);

        unordered_map<TreeNode*, bool> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited[target] = true;
        int cur_level = 0;

        while(!q.empty()){
            int size = q.size();
            if(cur_level==k) break;
            else cur_level++;

            for(int i=0 ; i<size ; i++){
                TreeNode* current = q.front();
                q.pop();

                if(current->left && !visited[current->left]){
                    q.push(current->left);
                    visited[current->left] = true;
                }

                 if(current->right && !visited[current->right]){
                    q.push(current->right);
                    visited[current->right] = true;
                }

                 if(parent_track[current] && !visited[parent_track[current]]){
                    q.push(parent_track[current]);
                    visited[parent_track[current]] = true;
                }


            }
        }

        vector<int> res;
        while(!q.empty()){
            TreeNode* temp = q.front();
            q.pop();
            res.push_back(temp->val);
        }
        return res;
    }
};

/*
LeetCode 863: All Nodes Distance K in Binary Tree
--------------------------------------------------
Given the root of a binary tree, a target node in the tree, and an integer k, return an array of the values of all 
nodes that have a distance k from the target node.

You can return the answer in any order.

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes at distance 2 from target node 5 are nodes 7, 4, and 1.

Example 2:
Input: root = [1], target = 1, k = 3
Output: []

Constraints:
- The number of nodes in the tree is in the range [1, 500].
- 0 <= Node.val <= 500
- All the values Node.val are unique.
- target is the value of one of the nodes in the tree.
- 0 <= k <= 1000

Approach:
1. Build parent pointers (map each node to its parent) using BFS/DFS
2. From target node, do BFS in all directions (left, right, parent)
3. Track visited nodes to avoid cycles
4. When distance reaches k, collect all nodes at that level
*/
