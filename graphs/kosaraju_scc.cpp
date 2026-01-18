// G-54: Strongly Connected Components - Kosaraju's Algorithm
// A strongly connected component is a maximal set of vertices where
// every vertex is reachable from every other vertex
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // DFS to fill stack with vertices in order of finish time
    void dfs1(int node, vector<int> adj[], vector<bool>& visited, stack<int>& st) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs1(neighbor, adj, visited, st);
            }
        }
        st.push(node);  // Push after all descendants are processed
    }
    
    // DFS on reversed graph to find SCC
    void dfs2(int node, vector<int> adjT[], vector<bool>& visited, vector<int>& component) {
        visited[node] = true;
        component.push_back(node);
        for (int neighbor : adjT[node]) {
            if (!visited[neighbor]) {
                dfs2(neighbor, adjT, visited, component);
            }
        }
    }
    
public:
    // Returns number of SCCs
    int kosaraju(int V, vector<int> adj[]) {
        // Step 1: Do DFS and store vertices by finish time
        stack<int> st;
        vector<bool> visited(V, false);
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs1(i, adj, visited, st);
            }
        }
        
        // Step 2: Create reversed graph
        vector<int> adjT[V];
        for (int i = 0; i < V; i++) {
            for (int neighbor : adj[i]) {
                adjT[neighbor].push_back(i);  // Reverse edge
            }
        }
        
        // Step 3: Do DFS on reversed graph in order of decreasing finish time
        fill(visited.begin(), visited.end(), false);
        int sccCount = 0;
        
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            
            if (!visited[node]) {
                vector<int> component;
                dfs2(node, adjT, visited, component);
                sccCount++;
                
                // Print the SCC
                cout << "SCC " << sccCount << ": ";
                for (int v : component) {
                    cout << v << " ";
                }
                cout << endl;
            }
        }
        
        return sccCount;
    }
    
    // Alternative: Return all SCCs
    vector<vector<int>> findSCCs(int V, vector<int> adj[]) {
        stack<int> st;
        vector<bool> visited(V, false);
        
        // Step 1: Fill stack with finish times
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs1(i, adj, visited, st);
            }
        }
        
        // Step 2: Create reversed graph
        vector<int> adjT[V];
        for (int i = 0; i < V; i++) {
            for (int neighbor : adj[i]) {
                adjT[neighbor].push_back(i);
            }
        }
        
        // Step 3: Find SCCs
        vector<vector<int>> sccs;
        fill(visited.begin(), visited.end(), false);
        
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            
            if (!visited[node]) {
                vector<int> component;
                dfs2(node, adjT, visited, component);
                sccs.push_back(component);
            }
        }
        
        return sccs;
    }
};

int main() {
    Solution sol;
    
    int V = 8;
    vector<int> adj[V];
    
    // Example graph with 3 SCCs
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);  // SCC: 0-1-2
    adj[2].push_back(3);
    adj[3].push_back(4);
    adj[4].push_back(5);
    adj[5].push_back(3);  // SCC: 3-4-5
    adj[4].push_back(6);
    adj[6].push_back(7);
    adj[7].push_back(6);  // SCC: 6-7
    
    cout << "Finding Strongly Connected Components:" << endl;
    int count = sol.kosaraju(V, adj);
    cout << "\nTotal SCCs: " << count << endl;
    
    return 0;
}

/*
Kosaraju's Algorithm:
1. Do DFS on original graph and push vertices to stack by finish time
2. Reverse all edges in the graph
3. Pop vertices from stack and do DFS on reversed graph
   - Each DFS from an unvisited vertex finds one SCC

Time Complexity: O(V + E)
Space Complexity: O(V + E)

Why it works:
- In step 1, vertices with higher finish times are leaders of SCCs
- In reversed graph, we can only reach vertices in the same SCC
- By processing in order of decreasing finish time, we ensure
  we start from SCC leaders and don't cross into other SCCs
*/
