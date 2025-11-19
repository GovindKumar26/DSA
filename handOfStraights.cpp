#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // LeetCode 846: Hand of Straights
    // Time: O(N log N), Space: O(N)
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if (n % groupSize != 0) return false;
        
        map<int, int> count;
        for (int card : hand) count[card]++;
        
        while (!count.empty()) {
            int start = count.begin()->first;
            for (int i = 0; i < groupSize; ++i) {
                int card = start + i;
                if (count[card] == 0) return false;
                count[card]--;
                if (count[card] == 0) count.erase(card);
            }
        }
        return true;
    }
};

/*
Problem: Hand of Straights (LeetCode 846)

Alice has a hand of cards, given as an array of integers. She wants to rearrange the cards into groups so that each group is size groupSize, and consists of groupSize consecutive cards.

Return true if and only if she can.

Example 1:
Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]

Example 2:
Input: hand = [1,2,3,4,5], groupSize = 4
Output: false
Explanation: Alice's hand cannot be rearranged into groups of 4.

Constraints:
- 1 <= hand.length <= 10^4
- 0 <= hand[i] <= 10^9
- 1 <= groupSize <= hand.length

Approach:
- Count the frequency of each card (use map for ordered keys)
- While there are cards left:
    - Take the smallest card as the start of a group
    - For groupSize consecutive cards, check if each exists
    - Decrement their counts, remove if zero
    - If any card in the group is missing, return false
- If all cards grouped, return true
*/
