// Kruskal's Algorithm - Minimum Spanning Tree (MST)
// Problem: Given a weighted, undirected, and connected graph with V vertices and E edges,
// find the Minimum Spanning Tree using Kruskal's algorithm with Disjoint Set Union (DSU).

#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> parent, rank;
    
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int findParent(int node) {
        if(node == parent[node]) {
            return node;
        }
        // Path compression
        return parent[node] = findParent(parent[node]);
    }
    
    void unionByRank(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
        
        if(pu == pv) return;
        
        // Union by rank
        if(rank[pu] < rank[pv]) {
            parent[pu] = pv;
        } else if(rank[pu] > rank[pv]) {
            parent[pv] = pu;
        } else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }
};

class Solution {
public:
    int spanningTree(int V, vector<vector<int>>& edges) {
        // Sort edges by weight
        sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
        });
        
        DisjointSet ds(V);
        int mstWeight = 0;
        int edgesUsed = 0;
        
        // Process edges in increasing order of weight
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            
            // If u and v are in different components, add this edge
            if(ds.findParent(u) != ds.findParent(v)) {
                mstWeight += wt;
                ds.unionByRank(u, v);
                edgesUsed++;
                
                // MST has V-1 edges
                if(edgesUsed == V - 1) break;
            }
        }
        
        return mstWeight;
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    
    vector<vector<int>> edges;
    
    for(int i = 0; i < E; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back({u, v, wt});
    }
    
    Solution obj;
    int result = obj.spanningTree(V, edges);
    
    cout << "Minimum Spanning Tree weight: " << result << endl;
    
    return 0;
}

// Time Complexity: O(E log E + E × α(V))
// - Sorting edges: O(E log E)
// - Processing edges with DSU: O(E × α(V)) where α is inverse Ackermann (nearly constant)
// - Overall: O(E log E) dominates
//
// Space Complexity: O(V + E)
// - Edges array: O(E)
// - DSU parent and rank arrays: O(V)
// - Overall: O(V + E)
//
// Explanation:
// Kruskal's algorithm builds MST by greedily selecting edges in increasing order of weight,
// ensuring no cycles are formed using Disjoint Set Union (DSU).
//
// Algorithm:
// 1. Sort all edges by weight in ascending order
// 2. Initialize Disjoint Set Union (DSU) for cycle detection
// 3. For each edge (u, v, weight) in sorted order:
//    - Check if u and v are in different components (using DSU)
//    - If yes, add edge to MST and union the components
//    - If no, skip (would create a cycle)
// 4. Stop when MST has V-1 edges
// 5. Return total MST weight
//
// Key Insight:
// - Process edges from smallest to largest weight
// - DSU efficiently checks if adding an edge creates a cycle
// - If u and v have same parent in DSU, they're already connected (cycle)
// - If different parents, we can safely add the edge
//
// Disjoint Set Union (DSU):
// - findParent(node): finds the root/representative of node's component
// - unionByRank(u, v): merges components containing u and v
// - Path compression: optimize findParent by flattening tree
// - Union by rank: attach smaller tree under larger tree
//
// Why it works:
// - Greedy choice: always pick minimum weight edge that doesn't create cycle
// - This is safe because of the cut property of MSTs
// - DSU ensures we never create cycles
// - After V-1 edges, all vertices are connected (spanning tree property)
//
// Comparison with Prim's:
// - Prim's: grows MST from a single vertex (vertex-centric)
// - Kruskal's: adds edges globally (edge-centric)
// - Prim's: better for dense graphs (many edges)
// - Kruskal's: better for sparse graphs (few edges)
// - Both produce same total MST weight (may differ in actual edges)
//
// Example:
// Graph with 5 vertices:
// Edges: (0,1,2), (0,3,6), (1,2,3), (1,3,8), (1,4,5), (2,4,7), (3,4,9)
//
// After sorting: (0,1,2), (1,2,3), (1,4,5), (0,3,6), (2,4,7), (1,3,8), (3,4,9)
//
// Step-by-step:
// 1. Add (0,1,2): components = {{0,1}, {2}, {3}, {4}}, weight = 2
// 2. Add (1,2,3): components = {{0,1,2}, {3}, {4}}, weight = 5
// 3. Add (1,4,5): components = {{0,1,2,4}, {3}}, weight = 10
// 4. Add (0,3,6): components = {{0,1,2,3,4}}, weight = 16
// 5. Stop (4 edges added, V-1 = 4)
//
// MST edges: (0,1), (1,2), (1,4), (0,3)
// Total weight: 16
