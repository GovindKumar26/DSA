// ====================================================================
// DSU - ADVANCED CONCEPTS & INTERVIEW GUIDE
// ====================================================================

#include <bits/stdc++.h>
using namespace std;

/*
╔════════════════════════════════════════════════════════════════════╗
║              ADVANCED DSU CONCEPTS                                 ║
╚════════════════════════════════════════════════════════════════════╝

1. WEIGHTED DSU
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Track relationships/distances between elements in same component.
Example: Track relative positions, ratios, etc.
*/

class WeightedDSU {
    vector<int> parent;
    vector<int> weight;  // weight[i] = weight from i to parent[i]
    
public:
    WeightedDSU(int n) {
        parent.resize(n);
        weight.resize(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    pair<int, int> find(int node) {
        if(node == parent[node]) {
            return {node, 0};
        }
        
        auto [root, w] = find(parent[node]);
        weight[node] += w;  // Path compression: update weight
        parent[node] = root;
        return {root, weight[node]};
    }
    
    void unite(int u, int v, int w) {
        // w represents: weight[u] - weight[v] = w
        auto [rootU, wU] = find(u);
        auto [rootV, wV] = find(v);
        
        if(rootU == rootV) return;
        
        parent[rootU] = rootV;
        weight[rootU] = wV - wU + w;
    }
    
    int diff(int u, int v) {
        // Returns weight[u] - weight[v]
        auto [rootU, wU] = find(u);
        auto [rootV, wV] = find(v);
        
        if(rootU != rootV) return INT_MAX;  // Not connected
        
        return wU - wV;
    }
};

/*
Use case: LeetCode 399 - Evaluate Division
Given equations a/b = k, find value of queries like c/d.
*/

/*
2. DSU WITH ROLLBACK
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Support undo operations (useful for offline queries).
*/

class RollbackDSU {
    vector<int> parent, rank;
    stack<pair<int, int>> history;  // (node, old_parent)
    
public:
    RollbackDSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int node) {
        // No path compression (would break rollback)
        while(node != parent[node]) {
            node = parent[node];
        }
        return node;
    }
    
    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU == rootV) return false;
        
        if(rank[rootU] < rank[rootV]) swap(rootU, rootV);
        
        history.push({rootV, parent[rootV]});
        history.push({rootU, rank[rootU]});
        
        parent[rootV] = rootU;
        if(rank[rootU] == rank[rootV]) {
            rank[rootU]++;
        }
        
        return true;
    }
    
    void rollback() {
        if(history.empty()) return;
        
        auto [node, oldVal] = history.top(); history.pop();
        rank[node] = oldVal;
        
        auto [node2, oldParent] = history.top(); history.pop();
        parent[node2] = oldParent;
    }
};

/*
3. PERSISTENT DSU
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Keep history of all versions (very advanced, uses persistent data structures).
Not commonly needed in interviews.
*/

/*
╔════════════════════════════════════════════════════════════════════╗
║              COMMON INTERVIEW PATTERNS                             ║
╚════════════════════════════════════════════════════════════════════╝

PATTERN 1: GRID CONNECTIVITY
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

class GridDSU {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        
        int m = grid.size(), n = grid[0].size();
        DSU dsu(m * n);
        int count = 0;
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == '1') {
                    count++;
                    int idx = i * n + j;
                    
                    // Check right
                    if(j + 1 < n && grid[i][j + 1] == '1') {
                        if(dsu.unite(idx, i * n + (j + 1))) {
                            count--;
                        }
                    }
                    
                    // Check down
                    if(i + 1 < m && grid[i + 1][j] == '1') {
                        if(dsu.unite(idx, (i + 1) * n + j)) {
                            count--;
                        }
                    }
                }
            }
        }
        
        return count;
    }
    
private:
    class DSU {
        vector<int> parent, rank;
    public:
        DSU(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for(int i = 0; i < n; i++) parent[i] = i;
        }
        
        int find(int x) {
            if(x != parent[x]) parent[x] = find(parent[x]);
            return parent[x];
        }
        
        bool unite(int x, int y) {
            int px = find(x), py = find(y);
            if(px == py) return false;
            if(rank[px] < rank[py]) swap(px, py);
            parent[py] = px;
            if(rank[px] == rank[py]) rank[px]++;
            return true;
        }
    };
};

/*
PATTERN 2: ONLINE VS OFFLINE QUERIES
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Online: Must answer queries as they come
  - Use standard DSU
  - Each query answered independently

Offline: Have all queries upfront
  - Can reorder queries for efficiency
  - Can process in reverse
  - Can use rollback DSU

Example: "Remove edges and answer connectivity queries"
  → Process in reverse: add edges instead!
*/

/*
╔════════════════════════════════════════════════════════════════════╗
║              DSU VARIATIONS CHEAT SHEET                            ║
╚════════════════════════════════════════════════════════════════════╝

STANDARD DSU (Most Common)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Operations: find, union, connected
Optimizations: Path compression + Union by rank/size
Time: O(α(n)) per operation
Use: 90% of interview problems

DSU WITH COMPONENT COUNT
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Extra: Track number of components
Union: Decrease count when merging
Use: "Count number of components" problems

DSU WITH COMPONENT SIZE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Extra: Track size of each component
Union: Update size array
Use: "Find largest component" problems

WEIGHTED DSU
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Extra: Track relationships between nodes
Union: Update weights based on relationship
Use: Division problems, relative position problems

ROLLBACK DSU
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Extra: Support undo operations
Trade-off: No path compression
Use: Offline queries, time travel problems
*/

/*
╔════════════════════════════════════════════════════════════════════╗
║              INTERVIEW TIPS & TRICKS                               ║
╚════════════════════════════════════════════════════════════════════╝

RECOGNIZE DSU PROBLEMS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Keywords that suggest DSU:
✓ "connected components"
✓ "connectivity"
✓ "union" / "merge"
✓ "groups"
✓ "cycles" (in undirected graphs)
✓ "minimum spanning tree"
✓ "network" problems
✓ "friend circles"
✓ "islands" (sometimes)

IMPLEMENTATION CHECKLIST
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Include path compression in find()
□ Use union by rank OR union by size (pick one)
□ Handle 0-indexed vs 1-indexed correctly
□ Initialize parent[i] = i
□ Check if already connected before union
□ Consider tracking component count if needed
□ Consider tracking component size if needed

COMMON MISTAKES
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
❌ Forgetting path compression → O(n) per query
❌ Not using union by rank/size → O(n) per query
❌ Using both rank and size (choose one!)
❌ Comparing nodes directly instead of their parents
   Wrong: if(u == v)
   Right: if(find(u) == find(v))
❌ 0 vs 1 indexing confusion
❌ In grid problems: wrong coordinate → index conversion

OPTIMIZATION TIPS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✓ Process more valuable operations first (e.g., type 3 edges)
✓ Use unordered_map for sparse data
✓ In grid problems: only check right/down to avoid duplicates
✓ For prime factorization: only check up to √n
✓ Consider offline processing if all queries given upfront

DEBUGGING TIPS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✓ Print parent array to visualize structure
✓ Print component count after each operation
✓ Verify find() returns consistent results
✓ Test with small examples first
✓ Check edge cases: n=1, no edges, all connected

TIME COMPLEXITY ANALYSIS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
With optimizations:
  - Single operation: O(α(n)) ≈ O(1)
  - M operations: O(M·α(n)) ≈ O(M)
  
Without optimizations:
  - Single operation: O(n) worst case
  - M operations: O(M·n)

Always mention α(n) is inverse Ackermann (practically constant).

SPACE COMPLEXITY
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Base DSU: O(n) for parent and rank/size arrays
Additional: depends on problem (maps, grids, etc.)
*/

/*
╔════════════════════════════════════════════════════════════════════╗
║              COMPLETE TEMPLATE FOR INTERVIEWS                      ║
╚════════════════════════════════════════════════════════════════════╝
*/

class DSU_Template {
    vector<int> parent, rank, size;
    int numComponents;
    
public:
    // Constructor
    DSU_Template(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        size.resize(n, 1);
        numComponents = n;
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find with path compression
    int find(int node) {
        if(node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }
    
    // Union by rank
    bool unionByRank(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU == rootV) return false;
        
        numComponents--;
        
        if(rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if(rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        
        return true;
    }
    
    // Union by size
    bool unionBySize(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU == rootV) return false;
        
        numComponents--;
        
        if(size[rootU] < size[rootV]) {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        } else {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
        
        return true;
    }
    
    // Check connectivity
    bool connected(int u, int v) {
        return find(u) == find(v);
    }
    
    // Get component size
    int getSize(int node) {
        return size[find(node)];
    }
    
    // Get number of components
    int getNumComponents() {
        return numComponents;
    }
};

/*
╔════════════════════════════════════════════════════════════════════╗
║              PROBLEM SOLVING FRAMEWORK                             ║
╚════════════════════════════════════════════════════════════════════╝

STEP 1: IDENTIFY IF DSU IS SUITABLE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Ask yourself:
□ Do I need to track connected components?
□ Do I need to merge groups?
□ Do I need to check if two elements are in same group?
□ Am I detecting cycles in undirected graph?
□ Is this a Minimum Spanning Tree problem?

If yes → Consider DSU

STEP 2: DESIGN THE APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. What are the "elements"? (nodes, cells, indices, etc.)
2. When should elements be in same set?
3. Do I need to track component count/size?
4. Any special relationships to track? (weighted DSU?)
5. Can I reorder operations? (offline queries?)

STEP 3: IMPLEMENT
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Initialize DSU with appropriate size
2. Process edges/operations
3. Query as needed
4. Return result

STEP 4: OPTIMIZE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Add path compression (if not already)
□ Add union by rank/size (if not already)
□ Consider processing order (valuable operations first)
□ Consider offline processing
□ Optimize space (sparse data → maps)

STEP 5: TEST
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Test cases:
□ n = 1 (single element)
□ No connections (all separate)
□ All connected (one component)
□ Multiple components
□ Edge cases from problem statement
*/

/*
╔════════════════════════════════════════════════════════════════════╗
║              COMPARATIVE ANALYSIS                                  ║
╚════════════════════════════════════════════════════════════════════╝

DSU vs DFS/BFS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Use DSU when:
✓ Dynamic connectivity (edges added over time)
✓ Just need to check connectivity (not path)
✓ Need to count components
✓ Cycle detection in undirected graphs
✓ Working with edge list

Use DFS/BFS when:
✓ Need actual path between nodes
✓ Need to visit all nodes in component
✓ Cycle detection in directed graphs
✓ Need distance/shortest path
✓ Have adjacency list

DSU vs Tarjan's/Kosaraju's
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
DSU: Undirected graphs, dynamic connectivity
Tarjan/Kosaraju: Directed graphs, strongly connected components

DSU vs Kruskal's vs Prim's
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Kruskal (uses DSU): Better for sparse graphs, edge-centric
Prim's: Better for dense graphs, vertex-centric
*/

int main() {
    cout << "DSU Advanced Concepts & Interview Guide" << endl;
    cout << "Study the patterns above and practice the problems!" << endl;
    
    // Quick test
    DSU_Template dsu(5);
    dsu.unionByRank(0, 1);
    dsu.unionByRank(2, 3);
    cout << "\nComponents after 2 unions: " << dsu.getNumComponents() << endl;
    cout << "0 and 1 connected? " << dsu.connected(0, 1) << endl;
    cout << "0 and 2 connected? " << dsu.connected(0, 2) << endl;
    
    return 0;
}
