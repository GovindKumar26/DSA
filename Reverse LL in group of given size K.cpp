/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseLL(ListNode* head) {
        if (head == NULL)
            return nullptr;

        ListNode *prev = NULL, *curr = head, *forward = NULL;

        while (curr) {
            forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;  
        }
        return prev;
     }

    ListNode* findKthNode(ListNode* temp, int k) {
        while (--k && temp) {
            temp = temp->next;
        }
        return temp;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *temp = head, *prevNode = NULL;

        while (temp) {
            ListNode* kthNode = findKthNode(temp, k);
            if (kthNode == nullptr) {
                if (prevNode != NULL)
                    prevNode->next = temp;
                break;
            }

            ListNode* nextNode = kthNode->next;
            kthNode->next = NULL;
            reverseLL(temp);
            if (temp == head) {
                head = kthNode;
            } else {
                prevNode->next = kthNode;
            }
            prevNode = temp;
            temp = nextNode;
        }
        return head;
    }
};


// Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
// k is a positive integer and is less than or equal to the length of the linked list
// If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
// You may not alter the values in the list's nodes, only nodes themselves may be changed
// time complexity: O(n)
// space complexity: O(1)
// Approach: Iterative approach
// 1. Find the kth node from the current node
// 2. If the kth node is null, then break the loop
// 3. Reverse the linked list from the current node to the kth node
// 4. Connect the previous part with the reversed part
// 5. Move the current node to the next part
// 6. Repeat the process until the end of the linked list