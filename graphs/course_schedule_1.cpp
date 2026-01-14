// Course Schedule - I (LeetCode 207)
// Problem: There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
// You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must 
// take course bi first if you want to take course ai.
// Return true if you can finish all courses. Otherwise, return false.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Build adjacency list
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        
        for(auto& prereq : prerequisites) {
            int course = prereq[0];
            int prerequisite = prereq[1];
            adj[prerequisite].push_back(course);
            indegree[course]++;
        }
        
        // Add all courses with no prerequisites to queue
        queue<int> q;
        for(int i = 0; i < numCourses; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int count = 0; // Count of courses that can be completed
        
        // Process courses using BFS (Kahn's Algorithm)
        while(!q.empty()) {
            int course = q.front();
            q.pop();
            count++;
            
            // Reduce indegree of dependent courses
            for(int nextCourse : adj[course]) {
                indegree[nextCourse]--;
                if(indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        
        // If all courses can be completed, return true
        return count == numCourses;
    }
};

int main() {
    int numCourses, numPrerequisites;
    cin >> numCourses >> numPrerequisites;
    
    vector<vector<int>> prerequisites;
    
    for(int i = 0; i < numPrerequisites; i++) {
        int a, b;
        cin >> a >> b;
        prerequisites.push_back({a, b});
    }
    
    Solution obj;
    
    if(obj.canFinish(numCourses, prerequisites)) {
        cout << "true - Can finish all courses" << endl;
    } else {
        cout << "false - Cannot finish all courses (cycle detected)" << endl;
    }
    
    return 0;
}

// Time Complexity: O(V + E)
// where V = numCourses and E = number of prerequisites
// - Building adjacency list: O(E)
// - BFS traversal: O(V + E)
// - Overall: O(V + E)
//
// Space Complexity: O(V + E)
// - Adjacency list: O(V + E)
// - Indegree array: O(V)
// - Queue: O(V) in worst case
// - Overall: O(V + E)
//
// Explanation:
// This is a classic cycle detection problem in a directed graph.
// We model courses as vertices and prerequisites as directed edges.
//
// Algorithm:
// 1. Build adjacency list from prerequisites (prerequisite -> course)
// 2. Calculate indegree for each course
// 3. Use Kahn's Algorithm (BFS-based topological sort):
//    - Start with courses having no prerequisites (indegree 0)
//    - Process each course and reduce indegree of dependent courses
//    - Add courses with indegree 0 to queue
// 4. If we can process all courses, return true; otherwise false
//
// Key Insight: If there's a cycle in the prerequisite graph, some courses will
// never have indegree 0, making it impossible to complete all courses.
// Example: Course A requires B, and B requires A (cycle).
