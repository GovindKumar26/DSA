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

class Codec {
public:
    // Encodes a tree to a single string (Level Order)
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        string result = "";
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node) {
                result += to_string(node->val) + ",";
                q.push(node->left);
                q.push(node->right);
            } else {
                result += "#,";
            }
        }
        
        return result;
    }

    // Decodes your encoded data to tree
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        vector<string> nodes;
        stringstream ss(data);
        string item;
        
        while (getline(ss, item, ',')) {
            nodes.push_back(item);
        }
        
        TreeNode* root = new TreeNode(stoi(nodes[0]));
        queue<TreeNode*> q;
        q.push(root);
        int i = 1;
        
        while (!q.empty() && i < nodes.size()) {
            TreeNode* node = q.front();
            q.pop();
            
            // Process left child
            if (nodes[i] != "#") {
                node->left = new TreeNode(stoi(nodes[i]));
                q.push(node->left);
            }
            i++;
            
            // Process right child
            if (i < nodes.size() && nodes[i] != "#") {
                node->right = new TreeNode(stoi(nodes[i]));
                q.push(node->right);
            }
            i++;
        }
        
        return root;
    }
};

/*
LeetCode 297: Serialize and Deserialize Binary Tree
----------------------------------------------------
Serialization is the process of converting a data structure or object into a sequence of bits 
so that it can be stored in a file or memory buffer, or transmitted across a network connection link 
to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your 
serialization/deserialization algorithm should work. You just need to ensure that a binary tree can 
be serialized to a string and this string can be deserialized to the original tree structure.

Example 1:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:
Input: root = []
Output: []

Constraints:
- The number of nodes in the tree is in the range [0, 10^4].
- -1000 <= Node.val <= 1000

Algorithm:
Serialize (Level Order BFS):
1. Use queue for level order traversal
2. For each node, append value + comma
3. For null nodes, append "#,"
4. Return resulting string

Deserialize:
1. Split string by comma to get node values
2. Create root from first value
3. Use queue to reconstruct tree level by level
4. For each node, attach left and right children from the values list

Time: O(n), Space: O(n)
*/
