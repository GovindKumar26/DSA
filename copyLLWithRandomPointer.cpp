/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        // brute force
        // Node* temp = head;
        // map<Node*, Node*> mpp;


        // while(temp) {
        //     mpp[temp] = new Node(temp->val);
        //     temp = temp->next;
        // }

        // temp = head;

        // while(temp) {
        //     Node*  copyNode = mpp[temp];
        //     copyNode->next = mpp[temp->next];
        //     copyNode->random = mpp[temp->random];
        //     temp = temp->next;
        // }

        // return mpp[head];

          if (!head) return NULL;

        Node* temp = head;

        // Step 1: Insert copied nodes
        while (temp) {
            Node* copyNode = new Node(temp->val);
            copyNode->next = temp->next;
            temp->next = copyNode;
            temp = copyNode->next;
        }

        // Step 2: Assign random pointers
        temp = head;
        while (temp) {
            if (temp->random) {
                temp->next->random = temp->random->next;
            }
            temp = temp->next->next;
        }

        // Step 3: Separate original and copied lists
        Node* dummy = new Node(0);
        Node* copyHead = dummy;
        temp = head;

        while (temp) {
            Node* copyNode = temp->next;
            temp->next = copyNode->next;   // restore original
            copyHead->next = copyNode;     // build copied list
            copyHead = copyNode;
            temp = temp->next;
        }

        return dummy->next; 
    }
}; 


// Given a linked list of length n, where each node has an additional random pointer, which could point to any node in the list or null, return a deep copy of the list.
// time complexity: O(n)
// space complexity: O(1)
// Approach: Optimized approach without extra space