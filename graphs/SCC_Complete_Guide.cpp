// ====================================================================
// STRONGLY CONNECTED COMPONENTS (SCC) - COMPLETE GUIDE
// ====================================================================

/*
╔════════════════════════════════════════════════════════════════════╗
║                    TABLE OF CONTENTS                               ║
╠════════════════════════════════════════════════════════════════════╣
║ 1. What are Strongly Connected Components?                        ║
║ 2. Kosaraju's Algorithm (Easiest)                                 ║
║ 3. Tarjan's Algorithm (One Pass)                                  ║
║ 4. Applications & Problems                                        ║
║ 5. Comparison: Kosaraju vs Tarjan                                 ║
╚════════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. WHAT ARE STRONGLY CONNECTED COMPONENTS (SCC)?
═══════════════════════════════════════════════════════════════════

DEFINITION:
A Strongly Connected Component (SCC) in a DIRECTED graph is a maximal
set of vertices where every vertex is reachable from every other vertex.

KEY POINTS:
• Only for DIRECTED graphs
• In an SCC, there's a path from u to v AND from v to u for all pairs
• SCCs are maximal (can't add more vertices and keep the property)
• SCCs partition the graph (every vertex in exactly one SCC)

EXAMPLE:
Graph: 0→1→2→0, 2→3→4→5→3, 4→6→7→6
       
       ┌─→1─┐         ┌─→4─┐         ┌─→7
       │    ↓         │    ↓         │    ↓
       0←──2──→3←─────5←──┘   6←──────┘
                              
SCCs: {0,1,2}, {3,4,5}, {6,7}

REAL-WORLD APPLICATIONS:
✓ Web page clustering (pages that link to each other)
✓ Social network communities (mutual connections)
✓ Compiler optimization (code dependency analysis)
✓ Circuit design (feedback loops)
✓ Recommendation systems

═══════════════════════════════════════════════════════════════════
2. KOSARAJU'S ALGORITHM (Easiest to Understand)
═══════════════════════════════════════════════════════════════════

INTUITION:
If you can reach B from A, and B is in a different SCC,
then you CANNOT reach A from B.

Kosaraju uses this by processing vertices in reverse finish order
(from later finishing vertices first) to ensure we process SCCs
in topological order.

ALGORITHM:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Step 1: DFS on original graph
        - Fill stack with vertices by finish time
        - Vertex that finishes LAST goes to TOP of stack
        
Step 2: Reverse the graph
        - For each edge u→v, create edge v→u
        
Step 3: DFS on reversed graph
        - Pop from stack and do DFS on unvisited vertices
        - Each DFS gives one SCC

WHY IT WORKS:
In reversed graph, if we start from a "sink" SCC (no outgoing edges
to other SCCs), DFS stays within that SCC. Processing by finish time
ensures we start from sink SCCs first.
*/

#include <bits/stdc++.h>
using namespace std;

class KosarajuSCC {
private:
    // Step 1: DFS to fill stack with finish times
    void dfs1(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& finishStack) {
        visited[node] = true;
        
        for(int neighbor : adj[node]) {
            if(!visited[neighbor]) {
                dfs1(neighbor, adj, visited, finishStack);
            }
        }
        
        // Push to stack AFTER visiting all descendants
        finishStack.push(node);
    }
    
    // Step 3: DFS on reversed graph to find SCC
    void dfs2(int node, vector<vector<int>>& adjReversed, vector<bool>& visited, 
              vector<int>& currentSCC) {
        visited[node] = true;
        currentSCC.push_back(node);
        
        for(int neighbor : adjReversed[node]) {
            if(!visited[neighbor]) {
                dfs2(neighbor, adjReversed, visited, currentSCC);
            }
        }
    }

public:
    vector<vector<int>> findSCCs(int V, vector<vector<int>>& adj) {
        // STEP 1: Fill stack with vertices by finish time
        stack<int> finishStack;
        vector<bool> visited(V, false);
        
        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                dfs1(i, adj, visited, finishStack);
            }
        }
        
        // STEP 2: Create reversed graph
        vector<vector<int>> adjReversed(V);
        for(int u = 0; u < V; u++) {
            for(int v : adj[u]) {
                adjReversed[v].push_back(u);  // Reverse edge
            }
        }
        
        // STEP 3: Process vertices in order of decreasing finish time
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs;
        
        while(!finishStack.empty()) {
            int node = finishStack.top();
            finishStack.pop();
            
            if(!visited[node]) {
                vector<int> currentSCC;
                dfs2(node, adjReversed, visited, currentSCC);
                sccs.push_back(currentSCC);
            }
        }
        
        return sccs;
    }
    
    int countSCCs(int V, vector<vector<int>>& adj) {
        return findSCCs(V, adj).size();
    }
};

/*
TIME COMPLEXITY: O(V + E)
  - DFS 1: O(V + E)
  - Reverse graph: O(V + E)
  - DFS 2: O(V + E)
  - Total: O(V + E)

SPACE COMPLEXITY: O(V + E)
  - Stack: O(V)
  - Reversed graph: O(V + E)
  - Visited arrays: O(V)

═══════════════════════════════════════════════════════════════════
3. TARJAN'S ALGORITHM (Single DFS Pass)
═══════════════════════════════════════════════════════════════════

INTUITION:
Use DFS to track:
• Discovery time (when first visited)
• Low-link value (earliest ancestor reachable via back edges)

A vertex is root of SCC if its low-link equals its discovery time.

ALGORITHM:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
For each vertex during DFS:
1. Set disc[v] = low[v] = timer++
2. Push v onto stack
3. For each neighbor u:
   - If u not visited: recurse, update low[v] = min(low[v], low[u])
   - If u on stack: update low[v] = min(low[v], disc[u])
4. After processing neighbors:
   - If low[v] == disc[v]: v is root of SCC
   - Pop stack until v is popped (all popped = one SCC)
*/

class TarjanSCC {
private:
    int timer;
    
    void dfs(int node, vector<vector<int>>& adj, vector<int>& disc, 
             vector<int>& low, vector<bool>& onStack, stack<int>& st, 
             vector<vector<int>>& sccs) {
        
        // Initialize discovery time and low-link value
        disc[node] = low[node] = timer++;
        st.push(node);
        onStack[node] = true;
        
        // Explore all neighbors
        for(int neighbor : adj[node]) {
            if(disc[neighbor] == -1) {
                // Neighbor not visited
                dfs(neighbor, adj, disc, low, onStack, st, sccs);
                low[node] = min(low[node], low[neighbor]);
            }
            else if(onStack[neighbor]) {
                // Neighbor is on stack (back edge in current SCC)
                low[node] = min(low[node], disc[neighbor]);
            }
        }
        
        // If node is root of an SCC
        if(low[node] == disc[node]) {
            vector<int> currentSCC;
            
            // Pop all vertices in this SCC
            while(true) {
                int v = st.top();
                st.pop();
                onStack[v] = false;
                currentSCC.push_back(v);
                
                if(v == node) break;
            }
            
            sccs.push_back(currentSCC);
        }
    }

public:
    vector<vector<int>> findSCCs(int V, vector<vector<int>>& adj) {
        timer = 0;
        vector<int> disc(V, -1);      // Discovery time
        vector<int> low(V, -1);       // Low-link value
        vector<bool> onStack(V, false);
        stack<int> st;
        vector<vector<int>> sccs;
        
        for(int i = 0; i < V; i++) {
            if(disc[i] == -1) {
                dfs(i, adj, disc, low, onStack, st, sccs);
            }
        }
        
        return sccs;
    }
    
    int countSCCs(int V, vector<vector<int>>& adj) {
        return findSCCs(V, adj).size();
    }
};

/*
TIME COMPLEXITY: O(V + E)
  - Single DFS traversal

SPACE COMPLEXITY: O(V)
  - disc, low, onStack arrays: O(V)
  - Stack: O(V)
  - Recursion depth: O(V)

KEY CONCEPTS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
disc[v]: Time when v was first visited
low[v]: Earliest discovery time reachable from v (or its subtree)

If low[v] == disc[v]: No back edge to an earlier vertex
                      → v is root of an SCC

═══════════════════════════════════════════════════════════════════
4. APPLICATIONS & PROBLEMS
═══════════════════════════════════════════════════════════════════
*/

// ────────────────────────────────────────────────────────────────
// APPLICATION 1: Check if graph is strongly connected
// ────────────────────────────────────────────────────────────────
class StronglyConnectedChecker {
public:
    bool isStronglyConnected(int V, vector<vector<int>>& adj) {
        KosarajuSCC scc;
        return scc.countSCCs(V, adj) == 1;
    }
};

// ────────────────────────────────────────────────────────────────
// APPLICATION 2: Condensation Graph (DAG of SCCs)
// ────────────────────────────────────────────────────────────────
class CondensationGraph {
public:
    // Build DAG where each node is an SCC
    vector<vector<int>> buildCondensation(int V, vector<vector<int>>& adj) {
        KosarajuSCC sccFinder;
        vector<vector<int>> sccs = sccFinder.findSCCs(V, adj);
        
        // Map vertex to its SCC index
        int numSCCs = sccs.size();
        vector<int> vertexToSCC(V);
        for(int i = 0; i < numSCCs; i++) {
            for(int v : sccs[i]) {
                vertexToSCC[v] = i;
            }
        }
        
        // Build condensation graph
        set<pair<int, int>> edges;  // Use set to avoid duplicate edges
        for(int u = 0; u < V; u++) {
            for(int v : adj[u]) {
                int sccU = vertexToSCC[u];
                int sccV = vertexToSCC[v];
                if(sccU != sccV) {
                    edges.insert({sccU, sccV});
                }
            }
        }
        
        vector<vector<int>> condensation(numSCCs);
        for(auto [u, v] : edges) {
            condensation[u].push_back(v);
        }
        
        return condensation;
    }
};

// ────────────────────────────────────────────────────────────────
// PROBLEM 1: Mother Vertex (GFG)
// A mother vertex is a vertex from which all vertices are reachable
// ────────────────────────────────────────────────────────────────
class MotherVertex {
private:
    void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        for(int neighbor : adj[node]) {
            if(!visited[neighbor]) {
                dfs(neighbor, adj, visited);
            }
        }
    }
    
public:
    int findMotherVertex(int V, vector<vector<int>>& adj) {
        // If graph has mother vertex, it's in the "source" SCC
        // (SCC with no incoming edges from other SCCs)
        
        // Find last finished vertex in DFS
        vector<bool> visited(V, false);
        int lastFinished = 0;
        
        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                dfs(i, adj, visited);
                lastFinished = i;
            }
        }
        
        // Check if lastFinished can reach all vertices
        fill(visited.begin(), visited.end(), false);
        dfs(lastFinished, adj, visited);
        
        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                return -1;  // No mother vertex
            }
        }
        
        return lastFinished;
    }
};

// ────────────────────────────────────────────────────────────────
// PROBLEM 2: Count vertices reachable from all vertices (GFG)
// ────────────────────────────────────────────────────────────────
class ReachableFromAll {
public:
    vector<int> findVerticesReachableFromAll(int V, vector<vector<int>>& adj) {
        // A vertex is reachable from all if it's in a sink SCC
        // (SCC with no outgoing edges to other SCCs)
        
        KosarajuSCC sccFinder;
        vector<vector<int>> sccs = sccFinder.findSCCs(V, adj);
        
        // Map vertex to SCC
        int numSCCs = sccs.size();
        vector<int> vertexToSCC(V);
        for(int i = 0; i < numSCCs; i++) {
            for(int v : sccs[i]) {
                vertexToSCC[v] = i;
            }
        }
        
        // Find which SCCs are sinks
        vector<bool> hasSCCOutEdge(numSCCs, false);
        for(int u = 0; u < V; u++) {
            for(int v : adj[u]) {
                if(vertexToSCC[u] != vertexToSCC[v]) {
                    hasSCCOutEdge[vertexToSCC[u]] = true;
                }
            }
        }
        
        // Collect vertices in sink SCCs
        vector<int> result;
        for(int i = 0; i < numSCCs; i++) {
            if(!hasSCCOutEdge[i]) {
                for(int v : sccs[i]) {
                    result.push_back(v);
                }
            }
        }
        
        return result;
    }
};

/*
═══════════════════════════════════════════════════════════════════
5. COMPARISON: KOSARAJU VS TARJAN
═══════════════════════════════════════════════════════════════════

KOSARAJU'S ALGORITHM:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Pros:
  ✓ Easier to understand and implement
  ✓ Clear three-step process
  ✓ Conceptually intuitive

Cons:
  ✗ Requires two DFS passes
  ✗ Needs to store reversed graph
  ✗ More space (reversed graph + stack)

Best for:
  • When clarity is important (interviews)
  • When you need to understand the algorithm
  • Educational purposes

TARJAN'S ALGORITHM:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Pros:
  ✓ Single DFS pass (more efficient)
  ✓ Less space (no reversed graph)
  ✓ Can be extended for other uses (bridges, articulation points)

Cons:
  ✗ More complex to understand
  ✗ Trickier to implement correctly
  ✗ Low-link calculation can be confusing

Best for:
  • When performance matters
  • Competitive programming
  • When you also need bridges/articulation points

SUMMARY:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Both: O(V + E) time
Kosaraju: Easier, 2 passes
Tarjan: Harder, 1 pass

For interviews: Use Kosaraju (easier to explain)
For contests: Learn both (Tarjan more versatile)

═══════════════════════════════════════════════════════════════════
PRACTICE PROBLEMS:
═══════════════════════════════════════════════════════════════════

EASY/MEDIUM:
✓ GFG: Strongly Connected Components (Basic)
✓ GFG: Mother Vertex
✓ LeetCode 1192: Critical Connections (uses Tarjan)
✓ GFG: Find the number of islands

HARD:
✓ LeetCode 1568: Minimum Days to Disconnect Island
✓ LeetCode 928: Minimize Malware Spread II
✓ GFG: Transitive closure of a graph

KEY TAKEAWAYS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. SCCs only for DIRECTED graphs
2. Kosaraju: 2 DFS + reverse graph
3. Tarjan: 1 DFS + low-link values
4. Both: O(V + E) time
5. Condensation graph is always a DAG
6. Applications: web crawling, recommendation systems, compiler optimization
*/

int main() {
    int V = 8;
    vector<vector<int>> adj(V);
    
    // Build example graph
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);  // SCC: {0, 1, 2}
    adj[2].push_back(3);
    adj[3].push_back(4);
    adj[4].push_back(5);
    adj[5].push_back(3);  // SCC: {3, 4, 5}
    adj[4].push_back(6);
    adj[6].push_back(7);
    adj[7].push_back(6);  // SCC: {6, 7}
    
    cout << "╔═══════════════════════════════════════════╗" << endl;
    cout << "║   STRONGLY CONNECTED COMPONENTS DEMO      ║" << endl;
    cout << "╚═══════════════════════════════════════════╝\n" << endl;
    
    // Using Kosaraju
    cout << "KOSARAJU'S ALGORITHM:" << endl;
    cout << "────────────────────" << endl;
    KosarajuSCC kosaraju;
    vector<vector<int>> sccs1 = kosaraju.findSCCs(V, adj);
    cout << "Found " << sccs1.size() << " SCCs:" << endl;
    for(int i = 0; i < sccs1.size(); i++) {
        cout << "SCC " << i + 1 << ": {";
        for(int j = 0; j < sccs1[i].size(); j++) {
            if(j > 0) cout << ", ";
            cout << sccs1[i][j];
        }
        cout << "}" << endl;
    }
    
    // Using Tarjan
    cout << "\nTARJAN'S ALGORITHM:" << endl;
    cout << "──────────────────" << endl;
    TarjanSCC tarjan;
    vector<vector<int>> sccs2 = tarjan.findSCCs(V, adj);
    cout << "Found " << sccs2.size() << " SCCs:" << endl;
    for(int i = 0; i < sccs2.size(); i++) {
        cout << "SCC " << i + 1 << ": {";
        for(int j = 0; j < sccs2[i].size(); j++) {
            if(j > 0) cout << ", ";
            cout << sccs2[i][j];
        }
        cout << "}" << endl;
    }
    
    return 0;
}
