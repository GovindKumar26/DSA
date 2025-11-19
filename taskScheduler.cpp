#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Approach: Max Heap (Greedy Simulation)
    // Time Complexity: O(N * log(26)) = O(N) where N is number of tasks
    // Space Complexity: O(1) since heap size is at most 26
    int leastInterval(vector<char>& tasks, int n) {
        // Step 1: Count frequency of each task
        unordered_map<char, int> counts;
        for (char t : tasks) {
            counts[t]++;
        }

        // Step 2: Push frequencies into Max Heap
        // We want to process the most frequent tasks first to minimize idle time
        priority_queue<int> pq;
        for (auto& pair : counts) {
            pq.push(pair.second);
        }

        int time = 0;

        // Step 3: Simulation
        while (!pq.empty()) {
            vector<int> remaining;
            int cycle = n + 1; // We try to execute n+1 tasks in each round (1 task + n cooldown)
            int taskCount = 0;

            // Try to fill the cycle with distinct tasks from heap
            while (cycle > 0 && !pq.empty()) {
                int freq = pq.top();
                pq.pop();
                
                // If task still has remaining instances, save it to push back later
                if (freq > 1) {
                    remaining.push_back(freq - 1);
                }
                
                taskCount++;
                cycle--;
            }

            // Push remaining tasks back to heap
            for (int count : remaining) {
                pq.push(count);
            }

            // Calculate time for this cycle
            if (pq.empty()) {
                // If heap is empty, we are done. 
                // Just add the actual number of tasks processed in this last cycle.
                time += taskCount;
            } else {
                // If heap is not empty, it means we have more tasks to process.
                // We MUST finish the full cycle of (n + 1) units.
                // If taskCount < n + 1, the rest is idle time.
                time += (n + 1);
            }
        }

        return time;
    }
};

/*
Problem: Task Scheduler (LeetCode 621)

Given a characters array tasks, representing the tasks a CPU needs to do, where each letter 
represents a different task. Tasks could be done in any order. Each task is done in one unit of time. 
For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period between two same tasks 
(the same letter in the array), that is that there must be at least n units of time between any two same tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.

Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.

Example 2:
Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
...
And so on.

-----------------------------------------------------------
INTUITION:
-----------------------------------------------------------
The key constraint is the cooldown `n`. This means if we schedule task 'A', we cannot schedule 'A' again 
for the next `n` time slots. This creates a "cycle" or "window" of size `n + 1`.

To minimize total time (and idle slots), we should be greedy. We should always try to schedule the 
task that has the highest remaining frequency. Why? Because the most frequent task is the bottleneck. 
If we delay scheduling it, we might be forced to idle at the end waiting for its cooldowns.

Algorithm:
1. Count frequencies of all tasks.
2. Use a Max Heap to store these frequencies. This gives us access to the most frequent task in O(1).
3. Process in cycles of `n + 1`:
   - In each cycle, try to pull `n + 1` distinct tasks from the heap.
   - Decrement their counts.
   - If a task still has remaining count, store it temporarily.
   - After the cycle (or when heap runs out), push the remaining tasks back to heap.
   - If the heap is not empty after this, it means we haven't finished. We must count the full `n + 1` time 
     (tasks + idle).
   - If the heap IS empty, we just count the actual tasks processed (no trailing idle time needed).

Complexity:
- Time: O(N), where N is total number of tasks. 
  - Counting takes O(N).
  - Heap operations: The number of distinct tasks is constant (26 uppercase letters). 
    So heap size is small constant. The loop runs based on max frequency, roughly proportional to N.
- Space: O(1) (or O(26) for map and heap).
*/
