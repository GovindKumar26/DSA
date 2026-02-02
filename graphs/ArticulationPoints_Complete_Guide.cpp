// ====================================================================
// ARTICULATION POINTS (CUT VERTICES) - COMPLETE GUIDE
// ====================================================================

/*
╔════════════════════════════════════════════════════════════════════╗
║                    TABLE OF CONTENTS                               ║
╠════════════════════════════════════════════════════════════════════╣
║ 1. What are Articulation Points?                                  ║
║ 2. Tarjan's Algorithm                                             ║
║ 3. Special Cases & Edge Cases                                     ║
║ 4. Practice Problems                                              ║
║ 5. Comparison: Bridges vs Articulation Points                     ║
╚════════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. WHAT ARE ARTICULATION POINTS?
═══════════════════════════════════════════════════════════════════

DEFINITION:
An articulation point (or cut vertex) is a vertex whose removal
increases the number of connected components in the graph.

KEY POINTS:
• Only for UNDIRECTED graphs
• Removing an articulation point disconnects the graph
• A single vertex (unlike bridges which are edges)
• Critical for network reliability

EXAMPLE:
Graph:  0─1─2─3
        │     │
        4─────5

Articulation Points: 1, 2
- Removing 1: {0,4} and {2,3,5} become separate
- Removing 2: {0,1,4} and {3,5} become separate
- 0, 3, 4, 5 are not articulation points

REAL-WORLD APPLICATIONS:
✓ Network reliability (single points of failure)
✓ Social network analysis (key influencers)
✓ Circuit design (critical components)
✓ Transportation networks (critical junctions)
✓ Internet routers (critical nodes)

═══════════════════════════════════════════════════════════════════
2. TARJAN'S ALGORITHM FOR ARTICULATION POINTS
═══════════════════════════════════════════════════════════════════

INTUITION:
A vertex u is an articulation point if:
1. u is the root of DFS tree AND has 2+ children, OR
2. u is not root AND has a child v where no back edge goes
   from v's subtree to u's ancestors

KEY CONCEPTS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
disc[u]: Discovery time of vertex u
low[u]: Lowest discovery time reachable from u via its subtree

ARTICULATION POINT CONDITIONS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Root: children >= 2
2. Non-root: has child v where low[v] >= disc[u]

Note: >= not > (unlike bridges where we use >)

ALGORITHM:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Initialize disc[] and low[] arrays
2. For each unvisited vertex, do DFS:
   a) Set disc[u] = low[u] = timer++
   b) For each neighbor v:
      - If v is parent: skip
      - If v not visited:
          * children++
          * Recurse on v
          * Update low[u] = min(low[u], low[v])
          * Check articulation point conditions
      - If v visited:
          * Update low[u] = min(low[u], disc[v])
   c) If root and children >= 2: articulation point
   d) If not root and low[v] >= disc[u]: articulation point

TIME: O(V + E)
SPACE: O(V)
*/

#include <bits/stdc++.h>
using namespace std;

class ArticulationPointFinder {
private:
    int timer;
    
    void dfs(int node, int parent, vector<vector<int>>& adj,
             vector<int>& disc, vector<int>& low,
             vector<bool>& isArticulation) {
        
        disc[node] = low[node] = timer++;
        int children = 0;
        
        for(int neighbor : adj[node]) {
            if(neighbor == parent) continue;
            
            if(disc[neighbor] == -1) {
                // Neighbor not visited
                children++;
                dfs(neighbor, node, adj, disc, low, isArticulation);
                
                // Update low value
                low[node] = min(low[node], low[neighbor]);
                
                // CHECK ARTICULATION POINT CONDITIONS
                
                // Condition 1: Root with 2+ children
                if(parent == -1 && children >= 2) {
                    isArticulation[node] = true;
                }
                
                // Condition 2: Non-root with child that can't reach above
                if(parent != -1 && low[neighbor] >= disc[node]) {
                    isArticulation[node] = true;
                }
            }
            else {
                // Back edge (neighbor already visited)
                low[node] = min(low[node], disc[neighbor]);
            }
        }
    }
    
public:
    vector<int> findArticulationPoints(int V, vector<vector<int>>& adj) {
        timer = 0;
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<bool> isArticulation(V, false);
        
        // Handle disconnected components
        for(int i = 0; i < V; i++) {
            if(disc[i] == -1) {
                dfs(i, -1, adj, disc, low, isArticulation);
            }
        }
        
        // Collect articulation points
        vector<int> result;
        for(int i = 0; i < V; i++) {
            if(isArticulation[i]) {
                result.push_back(i);
            }
        }
        
        return result;
    }
    
    int countArticulationPoints(int V, vector<vector<int>>& adj) {
        return findArticulationPoints(V, adj).size();
    }
};

/*
═══════════════════════════════════════════════════════════════════
3. SPECIAL CASES & EDGE CASES
═══════════════════════════════════════════════════════════════════

CASE 1: ROOT NODE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Root is articulation point ONLY if it has 2+ children in DFS tree.

Example:
    0          0─1─2
   / \   vs      |
  1   2          3

Left: 0 is articulation point (2 children)
Right: 0 is NOT (only 1 child, even though degree=2)

CASE 2: LEAF NODE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Leaf is NEVER an articulation point (no children to separate).

CASE 3: DISCONNECTED GRAPH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Must run DFS from each component.

CASE 4: PARALLEL EDGES
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Same as bridges, need to handle multiple edges between same pair.
*/

// ────────────────────────────────────────────────────────────────
// VARIATION 1: Count components after removing each vertex
// ────────────────────────────────────────────────────────────────
class ComponentCounter {
private:
    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, int skip) {
        if(node == skip) return;
        visited[node] = true;
        
        for(int neighbor : adj[node]) {
            if(!visited[neighbor] && neighbor != skip) {
                dfs(neighbor, adj, visited, skip);
            }
        }
    }
    
    int countComponents(int V, vector<vector<int>>& adj, int skip) {
        vector<bool> visited(V, false);
        if(skip != -1) visited[skip] = true;
        
        int components = 0;
        for(int i = 0; i < V; i++) {
            if(!visited[i] && i != skip) {
                dfs(i, adj, visited, skip);
                components++;
            }
        }
        
        return components;
    }
    
public:
    map<int, int> componentsAfterRemoval(int V, vector<vector<int>>& adj) {
        map<int, int> result;
        
        int originalComponents = countComponents(V, adj, -1);
        
        for(int i = 0; i < V; i++) {
            int newComponents = countComponents(V, adj, i);
            if(newComponents > originalComponents) {
                result[i] = newComponents;
            }
        }
        
        return result;
    }
};

// ────────────────────────────────────────────────────────────────
// VARIATION 2: Biconnected Components
// Components that remain connected after removing any single vertex
// ────────────────────────────────────────────────────────────────
class BiconnectedComponents {
private:
    int timer;
    
    void dfs(int node, int parent, vector<vector<int>>& adj,
             vector<int>& disc, vector<int>& low,
             stack<pair<int,int>>& edgeStack,
             vector<vector<pair<int,int>>>& biconnectedComps) {
        
        disc[node] = low[node] = timer++;
        int children = 0;
        
        for(int neighbor : adj[node]) {
            if(neighbor == parent) continue;
            
            if(disc[neighbor] == -1) {
                children++;
                edgeStack.push({node, neighbor});
                
                dfs(neighbor, node, adj, disc, low, edgeStack, biconnectedComps);
                
                low[node] = min(low[node], low[neighbor]);
                
                // Found articulation point: pop edges forming biconnected component
                if((parent == -1 && children >= 2) || 
                   (parent != -1 && low[neighbor] >= disc[node])) {
                    
                    vector<pair<int,int>> component;
                    pair<int,int> edge;
                    
                    do {
                        edge = edgeStack.top();
                        edgeStack.pop();
                        component.push_back(edge);
                    } while(edge.first != node || edge.second != neighbor);
                    
                    biconnectedComps.push_back(component);
                }
            }
            else if(disc[neighbor] < disc[node]) {
                // Back edge
                edgeStack.push({node, neighbor});
                low[node] = min(low[node], disc[neighbor]);
            }
        }
    }
    
public:
    vector<vector<pair<int,int>>> findBiconnectedComponents(int V, vector<vector<int>>& adj) {
        timer = 0;
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        stack<pair<int,int>> edgeStack;
        vector<vector<pair<int,int>>> biconnectedComps;
        
        for(int i = 0; i < V; i++) {
            if(disc[i] == -1) {
                dfs(i, -1, adj, disc, low, edgeStack, biconnectedComps);
                
                // Remaining edges form a component
                if(!edgeStack.empty()) {
                    vector<pair<int,int>> component;
                    while(!edgeStack.empty()) {
                        component.push_back(edgeStack.top());
                        edgeStack.pop();
                    }
                    biconnectedComps.push_back(component);
                }
            }
        }
        
        return biconnectedComps;
    }
};

/*
═══════════════════════════════════════════════════════════════════
4. PRACTICE PROBLEMS
═══════════════════════════════════════════════════════════════════
*/

// ────────────────────────────────────────────────────────────────
// PROBLEM 1: Critical Nodes (Similar to LeetCode but for vertices)
// ────────────────────────────────────────────────────────────────
class Solution_CriticalNodes {
public:
    vector<int> criticalNodes(int n, vector<vector<int>>& connections) {
        // Build adjacency list
        vector<vector<int>> adj(n);
        for(auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }
        
        ArticulationPointFinder finder;
        return finder.findArticulationPoints(n, adj);
    }
};

// ────────────────────────────────────────────────────────────────
// PROBLEM 2: Tarjan's Offline LCA (uses similar concept)
// ────────────────────────────────────────────────────────────────

// ────────────────────────────────────────────────────────────────
// PROBLEM 3: Count Critical Edges after removing a vertex
// ────────────────────────────────────────────────────────────────
class CriticalEdgesAfterRemoval {
public:
    map<int, int> countCriticalEdges(int V, vector<vector<int>>& adj) {
        ArticulationPointFinder apFinder;
        vector<int> articulationPoints = apFinder.findArticulationPoints(V, adj);
        
        map<int, int> result;
        
        for(int ap : articulationPoints) {
            // Build graph without this articulation point
            vector<vector<int>> modifiedAdj(V);
            for(int u = 0; u < V; u++) {
                if(u == ap) continue;
                for(int v : adj[u]) {
                    if(v != ap) {
                        modifiedAdj[u].push_back(v);
                    }
                }
            }
            
            // Count bridges in modified graph
            // (implementation omitted for brevity)
        }
        
        return result;
    }
};

/*
═══════════════════════════════════════════════════════════════════
5. COMPARISON: BRIDGES VS ARTICULATION POINTS
═══════════════════════════════════════════════════════════════════

                 BRIDGES              ARTICULATION POINTS
─────────────────────────────────────────────────────────────────
Type            Edges                Vertices
Removal         Edge removal         Vertex removal
Condition       low[v] > disc[u]     low[v] >= disc[u]
Root case       Not applicable       children >= 2
Algorithm       Tarjan               Tarjan (modified)
Complexity      O(V + E)             O(V + E)

KEY DIFFERENCES:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. OPERATOR:
   - Bridges: low[v] > disc[u] (strictly greater)
   - AP: low[v] >= disc[u] (greater or equal)
   
   Why? Consider edge u-v where low[v] == disc[u]:
   - As edge: not a bridge (v can reach u)
   - As vertex: u is AP (removing u disconnects v from u's ancestors)

2. ROOT HANDLING:
   - Bridges: root treated like any other vertex
   - AP: root is special (needs 2+ children)

3. MULTIPLE EDGES:
   - Bridges: parallel edges not bridges (form cycle)
   - AP: vertex with parallel edges can still be AP

VISUALIZATION:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Example: 0─1─2─3
             │
             4

Bridges: (0,1), (1,2), (2,3), (2,4)
         [all edges disconnect graph]

Articulation Points: 1, 2
         [removing 1 separates 0 from rest]
         [removing 2 separates 1,0 from 3,4]
         [0, 3, 4 are not APs]

═══════════════════════════════════════════════════════════════════
KEY INSIGHTS & COMMON MISTAKES
═══════════════════════════════════════════════════════════════════

COMMON MISTAKES:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
❌ Using > instead of >= for articulation points
❌ Forgetting root case (2+ children check)
❌ Not skipping parent edge
❌ Confusing bridges with articulation points
❌ Checking condition before DFS completes

DEBUGGING TIPS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✓ Print disc[] and low[] values
✓ Trace DFS tree structure
✓ Check root separately
✓ Test with simple graphs first
✓ Verify with brute force on small inputs

INTERVIEW TIPS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✓ Explain disc/low concept clearly
✓ Draw DFS tree to visualize
✓ Mention root case explicitly
✓ Compare with bridges if asked
✓ State time/space complexity

═══════════════════════════════════════════════════════════════════
PRACTICE PROBLEMS:
═══════════════════════════════════════════════════════════════════

MEDIUM:
✓ GFG: Articulation Point
✓ SPOJ: SUBMERGE - Submerging Islands
✓ Codeforces: Tourist's Notes

HARD:
✓ LeetCode 1568: Minimum Days to Disconnect Island (modified)
✓ GFG: Biconnected Components
✓ SPOJ: GRAPH - Critical Edges and Nodes

KEY TAKEAWAYS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Articulation point = vertex whose removal disconnects graph
2. Condition: low[v] >= disc[u] (note: >= not >)
3. Root special case: needs 2+ children
4. O(V + E) time using Tarjan's algorithm
5. Similar to bridges but for vertices
6. Applications: network reliability, critical infrastructure
*/

int main() {
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║    ARTICULATION POINTS DEMO                ║" << endl;
    cout << "╚════════════════════════════════════════════╝\n" << endl;
    
    // Example 1: Simple articulation point
    cout << "Example 1: Linear graph 0-1-2-3" << endl;
    int V1 = 4;
    vector<vector<int>> adj1(V1);
    adj1[0].push_back(1);
    adj1[1].push_back(0);
    adj1[1].push_back(2);
    adj1[2].push_back(1);
    adj1[2].push_back(3);
    adj1[3].push_back(2);
    
    ArticulationPointFinder finder1;
    vector<int> aps1 = finder1.findArticulationPoints(V1, adj1);
    
    cout << "Articulation Points: ";
    for(int ap : aps1) {
        cout << ap << " ";
    }
    cout << "\n(Expected: 1, 2)\n" << endl;
    
    // Example 2: Graph with cycle (no articulation points)
    cout << "Example 2: Cycle 0-1-2-3-0" << endl;
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
    
    ArticulationPointFinder finder2;
    vector<int> aps2 = finder2.findArticulationPoints(V2, adj2);
    
    cout << "Articulation Points: " << (aps2.empty() ? "None" : "") << endl;
    for(int ap : aps2) {
        cout << ap << " ";
    }
    cout << "(Expected: None - all vertices in a cycle)\n" << endl;
    
    // Example 3: Root with multiple children
    cout << "Example 3: Root with 2 children" << endl;
    cout << "    0" << endl;
    cout << "   / \\" << endl;
    cout << "  1   2" << endl;
    
    int V3 = 3;
    vector<vector<int>> adj3(V3);
    adj3[0].push_back(1);
    adj3[1].push_back(0);
    adj3[0].push_back(2);
    adj3[2].push_back(0);
    
    ArticulationPointFinder finder3;
    vector<int> aps3 = finder3.findArticulationPoints(V3, adj3);
    
    cout << "Articulation Points: ";
    for(int ap : aps3) {
        cout << ap << " ";
    }
    cout << "\n(Expected: 0 - root with 2+ children)\n" << endl;
    
    // Example 4: Complex graph
    cout << "Example 4: Complex graph" << endl;
    cout << "  0---1---2" << endl;
    cout << "  |   |   |" << endl;
    cout << "  4---3   5" << endl;
    
    int V4 = 6;
    vector<vector<int>> adj4(V4);
    adj4[0].push_back(1);
    adj4[1].push_back(0);
    adj4[0].push_back(4);
    adj4[4].push_back(0);
    adj4[1].push_back(2);
    adj4[2].push_back(1);
    adj4[1].push_back(3);
    adj4[3].push_back(1);
    adj4[3].push_back(4);
    adj4[4].push_back(3);
    adj4[2].push_back(5);
    adj4[5].push_back(2);
    
    ArticulationPointFinder finder4;
    vector<int> aps4 = finder4.findArticulationPoints(V4, adj4);
    
    cout << "Articulation Points: ";
    for(int ap : aps4) {
        cout << ap << " ";
    }
    cout << "\n(Expected: 1, 2)\n" << endl;
    
    return 0;
}
