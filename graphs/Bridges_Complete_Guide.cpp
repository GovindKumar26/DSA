// ====================================================================
// BRIDGES IN GRAPH - COMPLETE GUIDE
// ====================================================================

/*
╔════════════════════════════════════════════════════════════════════╗
║                    TABLE OF CONTENTS                               ║
╠════════════════════════════════════════════════════════════════════╣
║ 1. What are Bridges?                                               ║
║ 2. Tarjan's Algorithm for Bridges                                 ║
║ 3. Implementation & Variations                                    ║
║ 4. Practice Problems                                              ║
╚════════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. WHAT ARE BRIDGES?
═══════════════════════════════════════════════════════════════════

DEFINITION:
A bridge (or cut edge) is an edge whose removal increases the number
of connected components in the graph.

KEY POINTS:
• Only for UNDIRECTED graphs
• Removing a bridge disconnects the graph
• A bridge is NOT part of any cycle
• Critical for network reliability analysis

EXAMPLE:
Graph:  0─1─2─3
        │     │
        4─────5

Bridges: (0,1), (1,2), (2,3)
Not bridges: (0,4), (4,5), (3,5) [they form cycles]

REAL-WORLD APPLICATIONS:
✓ Network reliability (critical connections)
✓ Finding single points of failure
✓ Road/bridge infrastructure analysis
✓ Internet backbone connections
✓ Supply chain weak links

═══════════════════════════════════════════════════════════════════
2. TARJAN'S ALGORITHM FOR BRIDGES
═══════════════════════════════════════════════════════════════════

INTUITION:
An edge u-v is a bridge if there's NO back edge from v's subtree
to u or any ancestor of u.

KEY CONCEPTS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
disc[u]: Discovery time of vertex u (when first visited)
low[u]: Lowest discovery time reachable from u via its subtree

BRIDGE CONDITION:
Edge u-v is a bridge if:  low[v] > disc[u]

Meaning: v's subtree has NO back edge to u or u's ancestors

ALGORITHM:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Initialize disc[] and low[] arrays
2. For each unvisited vertex, do DFS:
   a) Set disc[u] = low[u] = timer++
   b) For each neighbor v:
      - If v is parent: skip (same edge we came from)
      - If v not visited:
          * Recurse on v
          * Update low[u] = min(low[u], low[v])
          * If low[v] > disc[u]: u-v is a BRIDGE
      - If v visited and not parent:
          * Update low[u] = min(low[u], disc[v])

TIME: O(V + E)
SPACE: O(V)
*/

#include <bits/stdc++.h>
using namespace std;

class BridgeFinder {
private:
    int timer;
    
    void dfs(int node, int parent, vector<vector<int>>& adj, 
             vector<int>& disc, vector<int>& low, vector<pair<int, int>>& bridges) {
        
        // Initialize discovery and low value
        disc[node] = low[node] = timer++;
        
        for(int neighbor : adj[node]) {
            // Skip parent edge (undirected graph)
            if(neighbor == parent) continue;
            
            if(disc[neighbor] == -1) {
                // Neighbor not visited yet
                dfs(neighbor, node, adj, disc, low, bridges);
                
                // Update low value after returning from DFS
                low[node] = min(low[node], low[neighbor]);
                
                // CHECK BRIDGE CONDITION
                if(low[neighbor] > disc[node]) {
                    // No back edge from neighbor's subtree to node or above
                    bridges.push_back({node, neighbor});
                }
            }
            else {
                // Neighbor already visited (back edge)
                // Update low value with neighbor's discovery time
                low[node] = min(low[node], disc[neighbor]);
            }
        }
    }
    
public:
    vector<pair<int, int>> findBridges(int V, vector<vector<int>>& adj) {
        timer = 0;
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<pair<int, int>> bridges;
        
        // Handle disconnected components
        for(int i = 0; i < V; i++) {
            if(disc[i] == -1) {
                dfs(i, -1, adj, disc, low, bridges);
            }
        }
        
        return bridges;
    }
    
    int countBridges(int V, vector<vector<int>>& adj) {
        return findBridges(V, adj).size();
    }
};

/*
═══════════════════════════════════════════════════════════════════
3. VARIATIONS & EDGE CASES
═══════════════════════════════════════════════════════════════════
*/

// ────────────────────────────────────────────────────────────────
// VARIATION 1: Handle Multiple Edges (Multigraph)
// ────────────────────────────────────────────────────────────────
class BridgeFinderMultigraph {
private:
    int timer;
    
    void dfs(int node, int parent, vector<vector<int>>& adj, 
             vector<int>& disc, vector<int>& low, 
             vector<pair<int, int>>& bridges,
             map<pair<int,int>, int>& edgeCount) {
        
        disc[node] = low[node] = timer++;
        
        for(int neighbor : adj[node]) {
            if(neighbor == parent) {
                // Check if there are multiple edges between node and parent
                pair<int,int> edge = {min(node, parent), max(node, parent)};
                if(edgeCount[edge] > 1) {
                    // Multiple edges exist, treat as cycle
                    low[node] = min(low[node], disc[neighbor]);
                }
                continue;
            }
            
            if(disc[neighbor] == -1) {
                dfs(neighbor, node, adj, disc, low, bridges, edgeCount);
                low[node] = min(low[node], low[neighbor]);
                
                if(low[neighbor] > disc[node]) {
                    bridges.push_back({node, neighbor});
                }
            }
            else {
                low[node] = min(low[node], disc[neighbor]);
            }
        }
    }
    
public:
    vector<pair<int, int>> findBridges(int V, vector<vector<int>>& adj) {
        timer = 0;
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<pair<int, int>> bridges;
        
        // Count edges between each pair
        map<pair<int,int>, int> edgeCount;
        for(int u = 0; u < V; u++) {
            for(int v : adj[u]) {
                if(u < v) {
                    edgeCount[{u, v}]++;
                }
            }
        }
        
        for(int i = 0; i < V; i++) {
            if(disc[i] == -1) {
                dfs(i, -1, adj, disc, low, bridges, edgeCount);
            }
        }
        
        return bridges;
    }
};

// ────────────────────────────────────────────────────────────────
// VARIATION 2: Bridge Tree (Condensed Graph)
// Condense all edges that are not bridges into single nodes
// ────────────────────────────────────────────────────────────────
class BridgeTree {
private:
    BridgeFinder bridgeFinder;
    
    void markComponent(int node, int compId, vector<vector<int>>& adj,
                      vector<int>& component, set<pair<int,int>>& bridgeSet) {
        component[node] = compId;
        
        for(int neighbor : adj[node]) {
            if(component[neighbor] != -1) continue;
            
            // Check if edge is a bridge
            pair<int,int> edge = {min(node, neighbor), max(node, neighbor)};
            if(bridgeSet.count(edge)) continue;  // Don't cross bridges
            
            markComponent(neighbor, compId, adj, component, bridgeSet);
        }
    }
    
public:
    vector<vector<int>> buildBridgeTree(int V, vector<vector<int>>& adj) {
        // Find all bridges
        vector<pair<int,int>> bridges = bridgeFinder.findBridges(V, adj);
        
        // Store bridges in set for O(1) lookup
        set<pair<int,int>> bridgeSet;
        for(auto [u, v] : bridges) {
            bridgeSet.insert({min(u, v), max(u, v)});
        }
        
        // Mark components (vertices connected without crossing bridges)
        vector<int> component(V, -1);
        int numComponents = 0;
        
        for(int i = 0; i < V; i++) {
            if(component[i] == -1) {
                markComponent(i, numComponents++, adj, component, bridgeSet);
            }
        }
        
        // Build tree of components
        set<pair<int,int>> treeEdges;
        for(auto [u, v] : bridges) {
            int compU = component[u];
            int compV = component[v];
            treeEdges.insert({min(compU, compV), max(compU, compV)});
        }
        
        vector<vector<int>> tree(numComponents);
        for(auto [u, v] : treeEdges) {
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        
        return tree;
    }
};

/*
═══════════════════════════════════════════════════════════════════
4. PRACTICE PROBLEMS
═══════════════════════════════════════════════════════════════════
*/

// ────────────────────────────────────────────────────────────────
// PROBLEM 1: Critical Connections (LeetCode 1192)
// ────────────────────────────────────────────────────────────────
class Solution_CriticalConnections {
private:
    int timer;
    
    void dfs(int node, int parent, vector<vector<int>>& adj,
             vector<int>& disc, vector<int>& low,
             vector<vector<int>>& result) {
        
        disc[node] = low[node] = timer++;
        
        for(int neighbor : adj[node]) {
            if(neighbor == parent) continue;
            
            if(disc[neighbor] == -1) {
                dfs(neighbor, node, adj, disc, low, result);
                low[node] = min(low[node], low[neighbor]);
                
                if(low[neighbor] > disc[node]) {
                    result.push_back({node, neighbor});
                }
            }
            else {
                low[node] = min(low[node], disc[neighbor]);
            }
        }
    }
    
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Build adjacency list
        vector<vector<int>> adj(n);
        for(auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }
        
        timer = 0;
        vector<int> disc(n, -1);
        vector<int> low(n, -1);
        vector<vector<int>> result;
        
        dfs(0, -1, adj, disc, low, result);
        
        return result;
    }
};

// ────────────────────────────────────────────────────────────────
// PROBLEM 2: Minimum Days to Disconnect Island (LeetCode 1568)
// ────────────────────────────────────────────────────────────────
class Solution_MinDaysToDisconnect {
private:
    int m, n;
    int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    void dfs(int i, int j, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
        if(i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0 || visited[i][j])
            return;
        
        visited[i][j] = true;
        for(auto& dir : dirs) {
            dfs(i + dir[0], j + dir[1], grid, visited);
        }
    }
    
    int countIslands(vector<vector<int>>& grid) {
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int count = 0;
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1 && !visited[i][j]) {
                    dfs(i, j, grid, visited);
                    count++;
                }
            }
        }
        
        return count;
    }
    
public:
    int minDays(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        // Check if already disconnected or empty
        if(countIslands(grid) != 1) return 0;
        
        // Try removing each land cell
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    grid[i][j] = 0;
                    if(countIslands(grid) != 1) {
                        return 1;  // Found bridge
                    }
                    grid[i][j] = 1;
                }
            }
        }
        
        // Maximum 2 days needed (remove any two adjacent cells)
        return 2;
    }
};

/*
═══════════════════════════════════════════════════════════════════
KEY INSIGHTS & VISUALIZATION
═══════════════════════════════════════════════════════════════════

BRIDGE vs NON-BRIDGE:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

BRIDGE:
    0───1───2
        
Edge 0-1 is a bridge because:
  - No alternative path from 0 to 1
  - Removing it disconnects the graph
  - low[1] = 1, disc[0] = 0
  - low[1] > disc[0] ✓

NON-BRIDGE (in cycle):
    0───1
    │   │
    3───2

Edge 0-1 is NOT a bridge because:
  - Alternative path: 0→3→2→1
  - Graph stays connected if removed
  - low[1] = 0 (can reach 0 via back edge)
  - low[1] ≤ disc[0] ✗

DISCOVERY & LOW VALUES:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Example: 0─1─2─3
          │   │
          4───5

DFS from 0:
  disc[0]=0, low[0]=0
  ↓
  disc[1]=1, low[1]=1
  ↓
  disc[2]=2, low[2]=2
  ↓
  disc[3]=3, low[3]=2 (back edge to 2)
  
  After backtracking:
  low[2]=2 (no back edge to 0 or 1)
  low[1]=1 (no back edge to 0)
  
  Bridges: 0-1 (low[1]>disc[0]), 1-2 (low[2]>disc[1])

COMMON MISTAKES:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
❌ Forgetting to skip parent edge in undirected graph
❌ Using low[neighbor] > disc[node] instead of >
❌ Not handling disconnected components
❌ Confusing with articulation points (vertices, not edges)

TIME COMPLEXITY:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
O(V + E) - Single DFS traversal

SPACE COMPLEXITY:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
O(V) - disc, low arrays + recursion stack

═══════════════════════════════════════════════════════════════════
PRACTICE PROBLEMS:
═══════════════════════════════════════════════════════════════════

MEDIUM:
✓ LeetCode 1192: Critical Connections in a Network
✓ GFG: Bridge edge in a graph
✓ Codeforces: Find Bridges

HARD:
✓ LeetCode 1568: Minimum Number of Days to Disconnect Island
✓ GFG: Bridges in DFS Tree
✓ SPOJ: SUBMERGE - Submerging Islands

KEY TAKEAWAYS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Bridge = edge whose removal disconnects graph
2. Condition: low[v] > disc[u] for edge u-v
3. Must skip parent edge in undirected graph
4. O(V + E) time using Tarjan's algorithm
5. Similar to articulation points but for edges
6. Applications: network reliability, infrastructure analysis
*/

int main() {
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║         BRIDGES IN GRAPH DEMO              ║" << endl;
    cout << "╚════════════════════════════════════════════╝\n" << endl;
    
    // Example 1: Simple bridge
    int V1 = 4;
    vector<vector<int>> adj1(V1);
    adj1[0].push_back(1);
    adj1[1].push_back(0);
    adj1[1].push_back(2);
    adj1[2].push_back(1);
    adj1[2].push_back(3);
    adj1[3].push_back(2);
    
    BridgeFinder finder1;
    vector<pair<int,int>> bridges1 = finder1.findBridges(V1, adj1);
    
    cout << "Example 1: Linear graph 0-1-2-3" << endl;
    cout << "Bridges found: " << bridges1.size() << endl;
    for(auto [u, v] : bridges1) {
        cout << "  " << u << " - " << v << endl;
    }
    
    // Example 2: Graph with cycle
    cout << "\nExample 2: Graph with cycle" << endl;
    cout << "  0---1" << endl;
    cout << "  |   |" << endl;
    cout << "  3---2" << endl;
    
    int V2 = 4;
    vector<vector<int>> adj2(V2);
    adj2[0].push_back(1);
    adj2[1].push_back(0);
    adj2[1].push_back(2);
    adj2[2].push_back(1);
    adj2[2].push_back(3);
    adj2[3].push_back(2);
    adj2[3].push_back(0);
    adj2[0].push_back(3);
    
    BridgeFinder finder2;
    vector<pair<int,int>> bridges2 = finder2.findBridges(V2, adj2);
    
    cout << "Bridges found: " << bridges2.size() << " (none - all edges in cycles)" << endl;
    
    // Example 3: Complex graph
    cout << "\nExample 3: Complex graph with bridges" << endl;
    int V3 = 7;
    vector<vector<int>> adj3(V3);
    // Component 1: 0-1-2 (cycle)
    adj3[0].push_back(1);
    adj3[1].push_back(0);
    adj3[1].push_back(2);
    adj3[2].push_back(1);
    adj3[2].push_back(0);
    adj3[0].push_back(2);
    // Bridge
    adj3[2].push_back(3);
    adj3[3].push_back(2);
    // Component 2: 3-4-5 (cycle)
    adj3[3].push_back(4);
    adj3[4].push_back(3);
    adj3[4].push_back(5);
    adj3[5].push_back(4);
    adj3[5].push_back(3);
    adj3[3].push_back(5);
    // Bridge
    adj3[5].push_back(6);
    adj3[6].push_back(5);
    
    BridgeFinder finder3;
    vector<pair<int,int>> bridges3 = finder3.findBridges(V3, adj3);
    
    cout << "Bridges found: " << bridges3.size() << endl;
    for(auto [u, v] : bridges3) {
        cout << "  " << u << " - " << v << endl;
    }
    
    return 0;
}
