#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // Approach 1: Min Heap (Priority Queue)
    // Time: O(N*log(k)) where N = total nodes, k = number of lists
    // Space: O(k) for heap
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Min heap with custom comparator
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minHeap(cmp);
        
        // Add first node of each list to heap
        for (ListNode* head : lists) {
            if (head) {
                minHeap.push(head);
            }
        }
        
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        
        // Extract min and add its next to heap
        while (!minHeap.empty()) {
            ListNode* minNode = minHeap.top();
            minHeap.pop();
            
            tail->next = minNode;
            tail = tail->next;
            
            if (minNode->next) {
                minHeap.push(minNode->next);
            }
        }
        
        return dummy->next;
    }
    
    // Approach 2: Divide and Conquer
    // Time: O(N*log(k))
    // Space: O(log(k)) for recursion stack
    ListNode* mergeKListsDivideConquer(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        return mergeHelper(lists, 0, lists.size() - 1);
    }
    
private:
    ListNode* mergeHelper(vector<ListNode*>& lists, int left, int right) {
        if (left == right) {
            return lists[left];
        }
        
        if (left + 1 == right) {
            return mergeTwoLists(lists[left], lists[right]);
        }
        
        int mid = left + (right - left) / 2;
        ListNode* leftMerged = mergeHelper(lists, left, mid);
        ListNode* rightMerged = mergeHelper(lists, mid + 1, right);
        
        return mergeTwoLists(leftMerged, rightMerged);
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        tail->next = l1 ? l1 : l2;
        return dummy->next;
    }
    
public:
    // Approach 3: Sequential Merge (Simple but less efficient)
    // Time: O(N*k) where N = total nodes, k = number of lists
    // Space: O(1)
    ListNode* mergeKListsSequential(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        
        ListNode* result = lists[0];
        for (int i = 1; i < lists.size(); i++) {
            result = mergeTwoLists(result, lists[i]);
        }
        
        return result;
    }
    
    // Approach 4: Using map (TreeMap equivalent)
    // Time: O(N*log(N))
    // Space: O(N)
    ListNode* mergeKListsMap(vector<ListNode*>& lists) {
        map<int, int> freq; // value -> count
        
        // Count all values
        for (ListNode* head : lists) {
            ListNode* curr = head;
            while (curr) {
                freq[curr->val]++;
                curr = curr->next;
            }
        }
        
        // Build result list from sorted map
        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;
        
        for (auto& [val, count] : freq) {
            for (int i = 0; i < count; i++) {
                tail->next = new ListNode(val);
                tail = tail->next;
            }
        }
        
        return dummy->next;
    }
};

/*
Problem: Merge k Sorted Lists (LeetCode 23)

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Example 1:
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6

Example 2:
Input: lists = []
Output: []

Example 3:
Input: lists = [[]]
Output: []

Constraints:
- k == lists.length
- 0 <= k <= 10^4
- 0 <= lists[i].length <= 500
- -10^4 <= lists[i][j] <= 10^4
- lists[i] is sorted in ascending order.
- The sum of lists[i].length will not exceed 10^4.

-----------------------------------------------------------
APPROACH COMPARISON:
-----------------------------------------------------------

1. MIN HEAP (RECOMMENDED) ⭐
   Time: O(N*log(k))
   Space: O(k)
   - Most efficient for large k
   - Heap maintains k candidates at most
   - Extract min, add its next node
   
2. DIVIDE AND CONQUER
   Time: O(N*log(k))
   Space: O(log(k)) recursion
   - Similar to merge sort
   - Pair-wise merging in log(k) levels
   - Good when heap operations expensive
   
3. SEQUENTIAL MERGE
   Time: O(N*k)
   Space: O(1)
   - Simplest to implement
   - Merge lists one by one
   - Inefficient for large k
   
4. MAP/MULTISET
   Time: O(N*log(N))
   Space: O(N)
   - Collect all values, sort, rebuild
   - Not recommended (destroys node structure)

-----------------------------------------------------------
WHY MIN HEAP IS BEST:
-----------------------------------------------------------
- At any moment, next smallest must be at head of one of k lists
- Heap keeps track of k candidates efficiently
- Only log(k) comparisons per node extraction
- Total: N nodes × log(k) = O(N*log(k))

-----------------------------------------------------------
OPTIMIZATION NOTES:
-----------------------------------------------------------
1. Handle empty lists before adding to heap
2. Use dummy node for clean result building
3. For k=2, direct merge is better
4. For very small k, sequential might be simpler

-----------------------------------------------------------
*/
