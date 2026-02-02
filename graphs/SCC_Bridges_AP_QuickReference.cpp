// ====================================================================
// SCC, BRIDGES, ARTICULATION POINTS - QUICK REFERENCE & COMPARISON
// ====================================================================

/*
╔════════════════════════════════════════════════════════════════════╗
║                    QUICK COMPARISON TABLE                          ║
╚════════════════════════════════════════════════════════════════════╝

┌──────────────┬────────────┬─────────────┬──────────────────────┐
│   FEATURE    │    SCC     │   BRIDGES   │ ARTICULATION POINTS  │
├──────────────┼────────────┼─────────────┼──────────────────────┤
│ Graph Type   │ DIRECTED   │ UNDIRECTED  │ UNDIRECTED           │
│ Identifies   │ Components │ Edges       │ Vertices             │
│ Algorithm    │ Kosaraju/  │ Tarjan      │ Tarjan (modified)    │
│              │ Tarjan     │             │                      │
│ Time         │ O(V + E)   │ O(V + E)    │ O(V + E)             │
│ Space        │ O(V + E)   │ O(V)        │ O(V)                 │
│ Key Concept  │ Mutual     │ Critical    │ Critical vertices    │
│              │ reachability│ edges       │                      │
│ Condition    │ low[] calc │ low[v] >    │ low[v] >= disc[u]    │
│              │            │ disc[u]     │                      │
│ Root Special │ No         │ No          │ Yes (2+ children)    │
└──────────────┴────────────┴─────────────┴──────────────────────┘

═══════════════════════════════════════════════════════════════════
WHEN TO USE WHICH?
═══════════════════════════════════════════════════════════════════

STRONGLY CONNECTED COMPONENTS (SCC):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Use when:
✓ Working with DIRECTED graphs
✓ Need to find mutually reachable vertices
✓ Building condensation graph (DAG of components)
✓ Detecting cycles in directed graphs
✓ 2-SAT problems

Keywords: "directed", "reach from", "reach to", "strongly connected"

BRIDGES:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Use when:
✓ Working with UNDIRECTED graphs
✓ Finding critical EDGES
✓ Network reliability (edge failures)
✓ Edges that disconnect graph when removed
✓ Not part of any cycle

Keywords: "critical connections", "remove edge", "disconnect"

ARTICULATION POINTS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Use when:
✓ Working with UNDIRECTED graphs
✓ Finding critical VERTICES
✓ Network reliability (node failures)
✓ Vertices that disconnect graph when removed
✓ Single points of failure

Keywords: "critical nodes", "remove vertex", "cut vertex"

═══════════════════════════════════════════════════════════════════
COMPLETE IMPLEMENTATION TEMPLATES
═══════════════════════════════════════════════════════════════════
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════
// TEMPLATE 1: STRONGLY CONNECTED COMPONENTS (Kosaraju)
// ═══════════════════════════════════════════════════════════════
class KosarajuSCC {
    void dfs1(int node, vector<vector<int>>& adj, vector<bool>& vis, stack<int>& st) {
        vis[node] = true;
        for(int nbr : adj[node])
            if(!vis[nbr]) dfs1(nbr, adj, vis, st);
        st.push(node);
    }
    
    void dfs2(int node, vector<vector<int>>& adjT, vector<bool>& vis, vector<int>& comp) {
        vis[node] = true;
        comp.push_back(node);
        for(int nbr : adjT[node])
            if(!vis[nbr]) dfs2(nbr, adjT, vis, comp);
    }
    
public:
    vector<vector<int>> findSCCs(int V, vector<vector<int>>& adj) {
        stack<int> st;
        vector<bool> vis(V, false);
        
        // Step 1: Fill stack
        for(int i = 0; i < V; i++)
            if(!vis[i]) dfs1(i, adj, vis, st);
        
        // Step 2: Reverse graph
        vector<vector<int>> adjT(V);
        for(int u = 0; u < V; u++)
            for(int v : adj[u])
                adjT[v].push_back(u);
        
        // Step 3: DFS on reversed graph
        fill(vis.begin(), vis.end(), false);
        vector<vector<int>> sccs;
        
        while(!st.empty()) {
            int node = st.top(); st.pop();
            if(!vis[node]) {
                vector<int> comp;
                dfs2(node, adjT, vis, comp);
                sccs.push_back(comp);
            }
        }
        
        return sccs;
    }
};

// ═══════════════════════════════════════════════════════════════
// TEMPLATE 2: BRIDGES
// ═══════════════════════════════════════════════════════════════
class BridgeFinder {
    int timer;
    
    void dfs(int u, int p, vector<vector<int>>& adj, vector<int>& tin, 
             vector<int>& low, vector<bool>& vis, vector<pair<int,int>>& bridges) {
        vis[u] = true;
        tin[u] = low[u] = timer++;
        
        for(int v : adj[u]) {
            if(v == p) continue;
            if(vis[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, u, adj, tin, low, vis, bridges);
                low[u] = min(low[u], low[v]);
                if(low[v] > tin[u])  // Bridge condition
                    bridges.push_back({u, v});
            }
        }
    }
    
public:
    vector<pair<int,int>> findBridges(int V, vector<vector<int>>& adj) {
        timer = 0;
        vector<int> tin(V, -1), low(V, -1);
        vector<bool> vis(V, false);
        vector<pair<int,int>> bridges;
        
        for(int i = 0; i < V; i++)
            if(!vis[i])
                dfs(i, -1, adj, tin, low, vis, bridges);
        
        return bridges;
    }
};

// ═══════════════════════════════════════════════════════════════
// TEMPLATE 3: ARTICULATION POINTS
// ═══════════════════════════════════════════════════════════════
class ArticulationPointFinder {
    int timer;
    
    void dfs(int u, int p, vector<vector<int>>& adj, vector<int>& disc,
             vector<int>& low, vector<bool>& isAP) {
        disc[u] = low[u] = timer++;
        int children = 0;
        
        for(int v : adj[u]) {
            if(v == p) continue;
            if(disc[v] == -1) {
                children++;
                dfs(v, u, adj, disc, low, isAP);
                low[u] = min(low[u], low[v]);
                
                // Root with 2+ children
                if(p == -1 && children >= 2)
                    isAP[u] = true;
                
                // Non-root articulation point
                if(p != -1 && low[v] >= disc[u])
                    isAP[u] = true;
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }
    
public:
    vector<int> findArticulationPoints(int V, vector<vector<int>>& adj) {
        timer = 0;
        vector<int> disc(V, -1), low(V, -1);
        vector<bool> isAP(V, false);
        
        for(int i = 0; i < V; i++)
            if(disc[i] == -1)
                dfs(i, -1, adj, disc, low, isAP);
        
        vector<int> result;
        for(int i = 0; i < V; i++)
            if(isAP[i]) result.push_back(i);
        
        return result;
    }
};

/*
═══════════════════════════════════════════════════════════════════
KEY DIFFERENCES IN DETAIL
═══════════════════════════════════════════════════════════════════

1. CONDITION COMPARISON:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

BRIDGES: low[v] > disc[u]
  → v's subtree has NO way back to u or above
  → Removing edge u-v disconnects v's subtree
  → Strictly greater (>)

ARTICULATION POINTS: low[v] >= disc[u]
  → v's subtree reaches at most u (not above)
  → Removing vertex u disconnects v from u's ancestors
  → Greater or equal (>=)

Example:
    0───1───2
    
For edge 0-1:
  low[1] = 1, disc[0] = 0
  low[1] > disc[0] ✓ → Bridge

For vertex 1:
  low[2] = 2, disc[1] = 1
  low[2] >= disc[1] ✓ → Articulation Point

2. PARENT HANDLING:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

SCC: No parent concept (directed graph)
BRIDGES: Skip parent edge (undirected)
ARTICULATION POINTS: Skip parent + count children

3. ROOT HANDLING:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

SCC: No special root case
BRIDGES: No special root case
ARTICULATION POINTS: Root is AP if children >= 2

═══════════════════════════════════════════════════════════════════
VISUAL EXAMPLES
═══════════════════════════════════════════════════════════════════

EXAMPLE 1: All Three Concepts
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Directed Graph (SCC):
    0→1→2→0
    ↓
    3→4→5→3
    
SCCs: {0,1,2}, {3,4,5}

Undirected version (Bridges & AP):
    0─1─2─0
    │
    3─4─5─3
    
Bridges: (0,3) [only this edge disconnects]
Articulation Points: 0, 3 [removing these disconnects]

EXAMPLE 2: Tree Structure
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

      0
     / \
    1   2
   / \
  3   4

Bridges: ALL edges (0-1, 0-2, 1-3, 1-4)
Articulation Points: 0 (root with 2 children), 1 (separates 3,4 from rest)

EXAMPLE 3: Complete Cycle
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

    0───1
    │   │
    3───2

Bridges: NONE (all edges in cycle)
Articulation Points: NONE (all vertices in cycle)

═══════════════════════════════════════════════════════════════════
COMMON PROBLEM PATTERNS
═══════════════════════════════════════════════════════════════════

PATTERN 1: Network Reliability
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem: Find critical connections/nodes in network
Solution: Find bridges or articulation points
Example: LeetCode 1192 (Bridges)

PATTERN 2: Graph Decomposition
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem: Break graph into components
Solution: Use bridges/APs to find components
Example: Biconnected components

PATTERN 3: Condensation Graph
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem: Build DAG from directed graph
Solution: Find SCCs, create edges between them
Example: Solve problems on DAG after condensation

PATTERN 4: Minimum Operations
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem: Minimum removals to disconnect
Solution: Find all bridges/APs
Example: LeetCode 1568

═══════════════════════════════════════════════════════════════════
INTERVIEW CHECKLIST
═══════════════════════════════════════════════════════════════════

BEFORE THE INTERVIEW:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Can implement all three from scratch
□ Understand disc[] and low[] arrays
□ Know time/space complexity
□ Can explain difference between bridges and APs
□ Practiced on 5+ problems each
□ Can draw DFS tree
□ Understand when to use which

DURING THE INTERVIEW:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Clarify: directed or undirected?
□ Clarify: edges or vertices?
□ Draw small example
□ Explain approach before coding
□ Mention Tarjan's algorithm by name
□ State time/space complexity
□ Test with edge cases

COMMON INTERVIEW QUESTIONS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Q: What's the difference between bridges and articulation points?
A: Bridges are edges; APs are vertices. Use > vs >=.

Q: Why do we need low[] array?
A: To track earliest reachable vertex via back edges.

Q: What's the time complexity?
A: O(V + E) for all three algorithms.

Q: Can you have bridges without articulation points?
A: Yes! Example: 0─1 (bridge 0-1, but no APs)

Q: When would you use Kosaraju vs Tarjan for SCC?
A: Kosaraju is simpler; Tarjan is more efficient (one pass).

═══════════════════════════════════════════════════════════════════
DEBUGGING TIPS
═══════════════════════════════════════════════════════════════════

FOR SCC:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✓ Verify stack order (finish times)
✓ Check if graph is properly reversed
✓ Ensure both DFS complete
✓ Test on simple directed cycle

FOR BRIDGES:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✓ Print disc[] and low[] values
✓ Ensure parent is skipped
✓ Use > not >=
✓ Test on tree (all bridges) and cycle (no bridges)

FOR ARTICULATION POINTS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✓ Check root case separately
✓ Use >= not >
✓ Count children correctly
✓ Test on star graph (root is AP)

═══════════════════════════════════════════════════════════════════
PRACTICE PROBLEM LIST
═══════════════════════════════════════════════════════════════════

SCC:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ GFG: Strongly Connected Components
□ GFG: Mother Vertex
□ LeetCode 1192: Critical Connections (can use Tarjan)

BRIDGES:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ LeetCode 1192: Critical Connections in a Network
□ GFG: Bridge edge in a graph
□ LeetCode 1568: Minimum Days to Disconnect Island

ARTICULATION POINTS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ GFG: Articulation Point
□ SPOJ: SUBMERGE - Submerging Islands
□ GFG: Biconnected Components

*/

// ═══════════════════════════════════════════════════════════════
// COMPREHENSIVE TEST
// ═══════════════════════════════════════════════════════════════

int main() {
    cout << "╔═══════════════════════════════════════════════════════╗\n";
    cout << "║  SCC, BRIDGES, ARTICULATION POINTS - DEMO            ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n\n";
    
    // Test 1: Undirected Graph
    cout << "TEST 1: Undirected Graph\n";
    cout << "───────────────────────\n";
    cout << "Graph: 0─1─2─3\n";
    cout << "       │     │\n";
    cout << "       4─────5\n\n";
    
    int V = 6;
    vector<vector<int>> adjU(V);
    adjU[0] = {1, 4};
    adjU[1] = {0, 2};
    adjU[2] = {1, 3};
    adjU[3] = {2, 5};
    adjU[4] = {0, 5};
    adjU[5] = {3, 4};
    
    BridgeFinder bFinder;
    auto bridges = bFinder.findBridges(V, adjU);
    cout << "Bridges: ";
    for(auto [u, v] : bridges) {
        cout << u << "-" << v << " ";
    }
    cout << "\n(Expected: 1-2, 2-3)\n\n";
    
    ArticulationPointFinder apFinder;
    auto aps = apFinder.findArticulationPoints(V, adjU);
    cout << "Articulation Points: ";
    for(int ap : aps) {
        cout << ap << " ";
    }
    cout << "\n(Expected: 2)\n\n";
    
    // Test 2: Directed Graph (SCC)
    cout << "TEST 2: Directed Graph (SCC)\n";
    cout << "────────────────────────────\n";
    cout << "Graph: 0→1→2→0 (cycle 1)\n";
    cout << "       ↓\n";
    cout << "       3→4→5→3 (cycle 2)\n\n";
    
    int V2 = 6;
    vector<vector<int>> adjD(V2);
    adjD[0] = {1};
    adjD[1] = {2};
    adjD[2] = {0, 3};
    adjD[3] = {4};
    adjD[4] = {5};
    adjD[5] = {3};
    
    KosarajuSCC sccFinder;
    auto sccs = sccFinder.findSCCs(V2, adjD);
    cout << "SCCs found: " << sccs.size() << "\n";
    for(int i = 0; i < sccs.size(); i++) {
        cout << "SCC " << i+1 << ": {";
        for(int j = 0; j < sccs[i].size(); j++) {
            if(j > 0) cout << ", ";
            cout << sccs[i][j];
        }
        cout << "}\n";
    }
    cout << "(Expected: 2 SCCs)\n\n";
    
    cout << "╔═══════════════════════════════════════════════════════╗\n";
    cout << "║                    STUDY FILES                        ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n\n";
    
    cout << "1. SCC_Complete_Guide.cpp - Strongly Connected Components\n";
    cout << "2. Bridges_Complete_Guide.cpp - Critical Edges\n";
    cout << "3. ArticulationPoints_Complete_Guide.cpp - Critical Vertices\n";
    cout << "4. This file - Quick Reference & Comparison\n\n";
    
    cout << "Key Differences:\n";
    cout << "  SCC         : Directed graphs, components\n";
    cout << "  Bridges     : Undirected, edges, low[v] > disc[u]\n";
    cout << "  Art. Points : Undirected, vertices, low[v] >= disc[u]\n\n";
    
    return 0;
}
