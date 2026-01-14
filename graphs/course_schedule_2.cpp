// Course Schedule - II (LeetCode 210)
// Problem: There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
// You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must 
// take course bi first if you want to take course ai.
// Return the ordering of courses you should take to finish all courses. 
// If there are many valid answers, return any of them. If it's impossible, return an empty array.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
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
        
        vector<int> result;
        
        // Process courses using BFS (Kahn's Algorithm)
        while(!q.empty()) {
            int course = q.front();
            q.pop();
            result.push_back(course);
            
            // Reduce indegree of dependent courses
            for(int nextCourse : adj[course]) {
                indegree[nextCourse]--;
                if(indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        
        // If all courses can be completed, return the order
        if(result.size() == numCourses) {
            return result;
        }
        
        // Otherwise, return empty array (cycle detected)
        return {};
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
    vector<int> result = obj.findOrder(numCourses, prerequisites);
    
    if(result.empty()) {
        cout << "Impossible to complete all courses (cycle detected)" << endl;
    } else {
        cout << "Course order: ";
        for(int course : result) {
            cout << course << " ";
        }
        cout << endl;
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
// - Result array: O(V)
// - Overall: O(V + E)
//
// Explanation:
// This is an extension of Course Schedule I where we need to return the actual order.
// We use topological sorting to find a valid course completion order.
//
// Algorithm:
// 1. Build adjacency list from prerequisites (prerequisite -> course)
// 2. Calculate indegree for each course
// 3. Use Kahn's Algorithm (BFS-based topological sort):
//    - Start with courses having no prerequisites (indegree 0)
//    - Add each processed course to result
//    - Reduce indegree of dependent courses
//    - Add courses with indegree 0 to queue
// 4. If result contains all courses, return it; otherwise return empty array
//
// Key Insight: The BFS order gives us a valid topological ordering, which represents
// a valid course completion sequence. If there's a cycle, we can't complete all courses,
// so we return an empty array.
