/*
class Node {
public:
    int data;
    Node* next;
    Node* bottom;

    Node(int x) {
        data = x;
        next = NULL;
        bottom = NULL;
    }
};
*/

Node* merge(Node* list1, Node* list2){
    // Create a dummy node as a
    // placeholder for the result
    Node* dummyNode = new Node(-1);
    Node* res = dummyNode;

    // Merge the lists based on data values
    while(list1 != NULL && list2 != NULL){
        if(list1->data < list2->data){
            res->bottom = list1;
            res = list1;
            list1 = list1->bottom;
        }
        else{
            res->bottom = list2;
            res = list2;
            list2 = list2->bottom;
        }
        res->next = NULL;
    }

    // Connect the remaining
    // elements if any
    if(list1){
        res->bottom = list1;
    } else {
        res->bottom = list2;
    }

    // Break the last node's
    // link to prevent cycles
    if(dummyNode->bottom){
        dummyNode->bottom->next = NULL;
    }

    return dummyNode->bottom;
}

class Solution {
  public:
    Node *flatten(Node *root) {
       
        // If root is null or there 
    // is no next node, return root
    if(root == NULL || root->next == NULL){
        return root;
    }

    // Recursively flatten the
    // rest of the linked list
    Node* mergedroot = flatten(root->next);
    root = merge(root, mergedroot);
    return root;
        
    }
};

// Given a linked list where every node represents a linked list and contains two pointers of its type:
// 1. Pointer to next node in the main list (right pointer)
// 2. Pointer to the bottom node in the same list (downward pointer)
// Each of the linked lists is in sorted order. Flatten the linked list such that all the nodes appear in a single level while maintaining the sorted order.
// The flattened list will be printed using the bottom pointer instead of the next pointer.
// time complexity: O(N*M) where N is the number of linked lists and M is the average number of nodes in each linked list
// space complexity: O(1)
// Approach: Merge two sorted linked lists at a time using recursion
