#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Count total nodes in the tree
    int countNodes(Node* root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    // Check if the binary tree is a complete binary tree
    bool isComplete(Node* root, int index, int totalNodes) {
        if (!root) return true;
        
        // If index assigned to current node is more than or equal to
        // number of nodes in tree, then tree is not complete
        if (index >= totalNodes) return false;
        
        // Recursively check left and right subtrees
        return isComplete(root->left, 2 * index + 1, totalNodes) &&
               isComplete(root->right, 2 * index + 2, totalNodes);
    }
    
    // Check if the tree satisfies max heap property
    bool isMaxHeapProperty(Node* root) {
        // If leaf node, return true
        if (!root->left && !root->right) return true;
        
        // If only left child exists
        if (root->right == nullptr) {
            return root->data >= root->left->data;
        }
        
        // If both children exist, check heap property and recurse
        if (root->data >= root->left->data && root->data >= root->right->data) {
            return isMaxHeapProperty(root->left) && isMaxHeapProperty(root->right);
        }
        
        return false;
    }
    
    // Main function to check if binary tree is a max heap
    bool isHeap(Node* root) {
        if (!root) return true;
        
        int totalNodes = countNodes(root);
        
        // Check if tree is complete and satisfies heap property
        return isComplete(root, 0, totalNodes) && isMaxHeapProperty(root);
    }
};

// Alternative approach using level order traversal
class Solution2 {
public:
    bool isHeap(Node* root) {
        if (!root) return true;
        
        queue<Node*> q;
        q.push(root);
        bool nullFound = false;
        
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            // Check left child
            if (curr->left) {
                // If we already found a null, tree is not complete
                if (nullFound) return false;
                
                // Check max heap property
                if (curr->data < curr->left->data) return false;
                
                q.push(curr->left);
            } else {
                nullFound = true;
            }
            
            // Check right child
            if (curr->right) {
                // If we already found a null, tree is not complete
                if (nullFound) return false;
                
                // Check max heap property
                if (curr->data < curr->right->data) return false;
                
                q.push(curr->right);
            } else {
                nullFound = true;
            }
        }
        
        return true;
    }
};

// Helper function to create a new node
Node* newNode(int data) {
    return new Node(data);
}

// Test cases
int main() {
    Solution sol;
    
    cout << "========== TEST CASE 1: Valid Max Heap ==========" << endl;
    /*
            90
           /  \
          80  70
         / \  /
        40 30 60
    */
    Node* root1 = newNode(90);
    root1->left = newNode(80);
    root1->right = newNode(70);
    root1->left->left = newNode(40);
    root1->left->right = newNode(30);
    root1->right->left = newNode(60);
    
    cout << "Is Heap: " << (sol.isHeap(root1) ? "Yes" : "No") << endl;
    cout << "Expected: Yes\n" << endl;
    
    cout << "========== TEST CASE 2: Not a Heap (violates heap property) ==========" << endl;
    /*
            90
           /  \
          80  70
         / \  /
        85 30 60  (85 > 80 violates heap property)
    */
    Node* root2 = newNode(90);
    root2->left = newNode(80);
    root2->right = newNode(70);
    root2->left->left = newNode(85);
    root2->left->right = newNode(30);
    root2->right->left = newNode(60);
    
    cout << "Is Heap: " << (sol.isHeap(root2) ? "Yes" : "No") << endl;
    cout << "Expected: No\n" << endl;
    
    cout << "========== TEST CASE 3: Not Complete Binary Tree ==========" << endl;
    /*
            90
           /  \
          80  70
             \
             30  (not complete - right child without left)
    */
    Node* root3 = newNode(90);
    root3->left = newNode(80);
    root3->right = newNode(70);
    root3->right->right = newNode(30);
    
    cout << "Is Heap: " << (sol.isHeap(root3) ? "Yes" : "No") << endl;
    cout << "Expected: No\n" << endl;
    
    cout << "========== TEST CASE 4: Single Node ==========" << endl;
    Node* root4 = newNode(50);
    cout << "Is Heap: " << (sol.isHeap(root4) ? "Yes" : "No") << endl;
    cout << "Expected: Yes\n" << endl;
    
    cout << "========== TEST CASE 5: Empty Tree ==========" << endl;
    Node* root5 = nullptr;
    cout << "Is Heap: " << (sol.isHeap(root5) ? "Yes" : "No") << endl;
    cout << "Expected: Yes\n" << endl;
    
    cout << "========== TEST CASE 6: Not Complete (gap in middle) ==========" << endl;
    /*
            90
           /  \
          80  70
         /     \
        40     60  (gap - not complete)
    */
    Node* root6 = newNode(90);
    root6->left = newNode(80);
    root6->right = newNode(70);
    root6->left->left = newNode(40);
    root6->right->right = newNode(60);
    
    cout << "Is Heap: " << (sol.isHeap(root6) ? "Yes" : "No") << endl;
    cout << "Expected: No\n" << endl;
    
    // Test with Solution2 (level order approach)
    cout << "\n========== Testing with Solution2 (Level Order) ==========" << endl;
    Solution2 sol2;
    cout << "Test Case 1: " << (sol2.isHeap(root1) ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "Test Case 2: " << (sol2.isHeap(root2) ? "Yes" : "No") << " (Expected: No)" << endl;
    cout << "Test Case 3: " << (sol2.isHeap(root3) ? "Yes" : "No") << " (Expected: No)" << endl;
    
    return 0;
}

/*
Problem: Check if a given Binary Tree is a Heap

A binary tree is a max heap if:
1. It's a complete binary tree (all levels filled except possibly last, filled left to right)
2. Every node's value >= its children's values (max heap property)

Approach 1 (Solution):
- Count total nodes
- Check if complete using index-based approach (like array representation)
- Check max heap property recursively

Approach 2 (Solution2):
- Use level order traversal
- Track if any null encountered
- Check completeness: no node should come after first null
- Check heap property: parent >= children

Time Complexity: O(n) - visit each node once
Space Complexity: 
- Solution: O(h) recursive stack, h = height
- Solution2: O(w) queue space, w = max width

Key Points:
- Complete binary tree: all levels filled left to right
- Index property: left child at 2*i+1, right at 2*i+2
- Max heap: parent >= children (min heap: parent <= children)
*/
