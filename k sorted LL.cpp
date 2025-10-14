#include <queue>

class Solution {
public:
    struct compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val; // min-heap
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;

        // Step 1: push head of each list
        for(auto node : lists) {
            if(node) minHeap.push(node);
        }

        ListNode dummy(0);
        ListNode* tail = &dummy;

        // Step 2: pop and push
        while(!minHeap.empty()) {
            ListNode* curr = minHeap.top();
            minHeap.pop();

            tail->next = curr;
            tail = tail->next;

            if(curr->next) minHeap.push(curr->next);
        }

        return dummy.next;
    }
};


// Given an array of k linked-lists lists, each linked-list is sorted in ascending order. Merge all the linked-lists into one sorted linked-list and return it.
// time complexity: O(N log k) where N is the total number of nodes and k is the number of linked lists.
// space complexity: O(k) for the min-heap
// Approach: Use a min-heap (priority queue) to keep track of the smallest current node among the k lists. Continuously extract the smallest node and add it to the merged list, then push the next node from the same list into the heap.
