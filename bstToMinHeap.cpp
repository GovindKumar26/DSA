#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/*
===================================================================================
PROBLEM: Convert BST to Min Heap
===================================================================================

INTUITION:
---------
1. BST Property: Inorder traversal gives sorted array in ascending order
2. Min Heap Property: Parent < Children AND Complete Binary Tree
3. For min heap in level order: smaller elements should come before larger ones

KEY INSIGHT:
- If we do INORDER traversal of BST, we get sorted array [smallest...largest]
- If we fill this sorted array into tree using PREORDER traversal, we get min heap!

WHY PREORDER?
- Preorder visits: Root → Left → Right
- This ensures parent is filled before children
- When we fill sorted array (ascending), parent gets smaller value than children
- Result: Min heap property satisfied!

EXAMPLE:
        4                   Inorder: [1,2,3,4]
       / \        
      2   6                 Preorder fill with [1,2,3,4]:
     / \                    Visit root(1), left(2), right(3), left-left(4)
    1   3                   
                                  1
BST (inorder sorted)             / \
                                2   3
                               /
                              4
                            
                            Min Heap (preorder filled)

ALGORITHM:
1. Do inorder traversal of BST → store in array (sorted ascending)
2. Do preorder traversal and fill values from array
3. Result is min heap!

Time: O(n) - two traversals
Space: O(n) - array to store inorder
===================================================================================
*/

class Solution {
private:
    // Step 1: Get inorder traversal (sorted array)
    void inorderTraversal(Node* root, vector<int>& arr) {
        if (!root) return;
        
        inorderTraversal(root->left, arr);
        arr.push_back(root->data);
        inorderTraversal(root->right, arr);
    }
    
    // Step 2: Fill values using preorder (root, left, right)
    void preorderFill(Node* root, vector<int>& arr, int& index) {
        if (!root) return;
        
        // Fill current node with next value from sorted array
        root->data = arr[index++];
        
        // Fill left subtree
        preorderFill(root->left, arr, index);
        
        // Fill right subtree
        preorderFill(root->right, arr, index);
    }
    
public:
    // Main function to convert BST to Min Heap
    void bstToMinHeap(Node* root) {
        if (!root) return;
        
        // Step 1: Get sorted array via inorder
        vector<int> inorder;
        inorderTraversal(root, inorder);
        
        // Step 2: Fill tree with sorted values using preorder
        int index = 0;
        preorderFill(root, inorder, index);
    }
};

// Alternative: Single pass using Morris Traversal (Space O(1))
class Solution2 {
private:
    void preorderFill(Node* root, vector<int>& arr, int& index) {
        if (!root) return;
        root->data = arr[index++];
        preorderFill(root->left, arr, index);
        preorderFill(root->right, arr, index);
    }
    
public:
    void bstToMinHeap(Node* root) {
        if (!root) return;
        
        vector<int> inorder;
        
        // Morris Inorder Traversal (O(1) space for traversal)
        Node* curr = root;
        while (curr) {
            if (!curr->left) {
                inorder.push_back(curr->data);
                curr = curr->right;
            } else {
                Node* pred = curr->left;
                while (pred->right && pred->right != curr) {
                    pred = pred->right;
                }
                
                if (!pred->right) {
                    pred->right = curr;
                    curr = curr->left;
                } else {
                    pred->right = nullptr;
                    inorder.push_back(curr->data);
                    curr = curr->right;
                }
            }
        }
        
        int index = 0;
        preorderFill(root, inorder, index);
    }
};

// Utility functions
Node* newNode(int data) {
    return new Node(data);
}

void printPreorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

void printInorder(Node* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}

void printLevelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

bool isMinHeap(Node* root) {
    if (!root) return true;
    
    queue<Node*> q;
    q.push(root);
    bool nullFound = false;
    
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        
        if (curr->left) {
            if (nullFound) return false;
            if (curr->data > curr->left->data) return false;
            q.push(curr->left);
        } else {
            nullFound = true;
        }
        
        if (curr->right) {
            if (nullFound) return false;
            if (curr->data > curr->right->data) return false;
            q.push(curr->right);
        } else {
            nullFound = true;
        }
    }
    return true;
}

int main() {
    Solution sol;
    
    cout << "========================================" << endl;
    cout << "   BST to Min Heap Conversion" << endl;
    cout << "========================================\n" << endl;
    
    // Test Case 1
    cout << "TEST CASE 1:" << endl;
    cout << "------------" << endl;
    /*
            4
           / \
          2   6
         / \
        1   3
    */
    Node* root1 = newNode(4);
    root1->left = newNode(2);
    root1->right = newNode(6);
    root1->left->left = newNode(1);
    root1->left->right = newNode(3);
    
    cout << "Original BST (Inorder): ";
    printInorder(root1);
    cout << "\nOriginal BST (Level Order): ";
    printLevelOrder(root1);
    cout << endl;
    
    sol.bstToMinHeap(root1);
    
    cout << "\nAfter Conversion:" << endl;
    cout << "Min Heap (Preorder): ";
    printPreorder(root1);
    cout << "\nMin Heap (Level Order): ";
    printLevelOrder(root1);
    cout << "\nIs valid Min Heap? " << (isMinHeap(root1) ? "Yes" : "No") << endl;
    cout << endl;
    
    // Test Case 2
    cout << "TEST CASE 2:" << endl;
    cout << "------------" << endl;
    /*
               8
              / \
             4   12
            / \  / \
           2  6 10 14
    */
    Node* root2 = newNode(8);
    root2->left = newNode(4);
    root2->right = newNode(12);
    root2->left->left = newNode(2);
    root2->left->right = newNode(6);
    root2->right->left = newNode(10);
    root2->right->right = newNode(14);
    
    cout << "Original BST (Inorder): ";
    printInorder(root2);
    cout << "\nOriginal BST (Level Order): ";
    printLevelOrder(root2);
    cout << endl;
    
    sol.bstToMinHeap(root2);
    
    cout << "\nAfter Conversion:" << endl;
    cout << "Min Heap (Preorder): ";
    printPreorder(root2);
    cout << "\nMin Heap (Level Order): ";
    printLevelOrder(root2);
    cout << "\nIs valid Min Heap? " << (isMinHeap(root2) ? "Yes" : "No") << endl;
    cout << endl;
    
    // Test Case 3 - Skewed BST
    cout << "TEST CASE 3 (Skewed BST):" << endl;
    cout << "-------------------------" << endl;
    /*
        1
         \
          2
           \
            3
             \
              4
    */
    Node* root3 = newNode(1);
    root3->right = newNode(2);
    root3->right->right = newNode(3);
    root3->right->right->right = newNode(4);
    
    cout << "Original BST (Inorder): ";
    printInorder(root3);
    cout << "\nOriginal BST (Level Order): ";
    printLevelOrder(root3);
    cout << endl;
    
    sol.bstToMinHeap(root3);
    
    cout << "\nAfter Conversion:" << endl;
    cout << "Min Heap (Preorder): ";
    printPreorder(root3);
    cout << "\nMin Heap (Level Order): ";
    printLevelOrder(root3);
    cout << "\nIs valid Min Heap? " << (isMinHeap(root3) ? "Yes" : "No") << endl;
    cout << endl;
    
    cout << "========================================" << endl;
    cout << "VISUAL EXPLANATION:" << endl;
    cout << "========================================" << endl;
    cout << "BST Inorder (sorted): [1, 2, 3, 4, 6]" << endl;
    cout << "Fill using Preorder traversal:" << endl;
    cout << "  Step 1: Root gets 1" << endl;
    cout << "  Step 2: Left child gets 2" << endl;
    cout << "  Step 3: Right child gets 3" << endl;
    cout << "  Step 4: Left-Left gets 4" << endl;
    cout << "  Step 5: Left-Right gets 6" << endl;
    cout << "\nResult: Min Heap! (parent < children)" << endl;
    cout << "========================================" << endl;
    
    return 0;
}

/*
===================================================================================
COMPLEXITY ANALYSIS:
===================================================================================

Time Complexity: O(n)
- Inorder traversal: O(n)
- Preorder fill: O(n)
- Total: O(n) + O(n) = O(n)

Space Complexity: O(n)
- Array to store inorder: O(n)
- Recursion stack: O(h) where h is height
- Total: O(n)

Alternative with Morris: O(n) time, O(n) space (only for array)

===================================================================================
WHY THIS WORKS:
===================================================================================

1. BST gives sorted array via inorder
2. Preorder ensures parent is visited before children
3. Filling sorted array in preorder order ensures:
   - Smaller elements go to parents
   - Larger elements go to children
   - Min heap property: parent < children ✓
4. Original tree structure is complete (BST shape preserved)
   - Min heap requires complete binary tree ✓

IMPORTANT NOTE:
- This works when BST is already a complete binary tree
- If BST is not complete, result won't be a valid heap
- For general case, might need to rebuild tree structure

===================================================================================
*/
