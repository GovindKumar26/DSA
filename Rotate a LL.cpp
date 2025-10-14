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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL) {
            return NULL;
        }

        int l = 1;
        ListNode *tail = head, *temp;
        while (tail->next) {
            l++;
            tail = tail->next;
        }

        k = k % l;
        temp = head;

        int x = l - k - 1;
        while (x) {
            temp = temp->next;
            x--;
        }

        tail->next = head;
        head = temp->next;
        temp->next = NULL;

        return head;
    }
};


// Given the head of a linked list, rotate the list to the right by k places.
// time complexity: O(n)
// space complexity: O(1)
// Approach: Make the linked list circular and then break the circle at the right point
// Edge cases: If the list is empty or has only one node, return the head as is. If k is 0, return the head as is.
// If k is greater than the length of the list, take k modulo length of the list.
// If k is 0 after modulo operation, return the head as is.
// If k is equal to the length of the list, return the head as is.
