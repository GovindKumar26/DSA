// ====================================================================
// DISJOINT SET UNION (DSU) / UNION-FIND - COMPLETE GUIDE
// ====================================================================

/*
╔════════════════════════════════════════════════════════════════════╗
║                    TABLE OF CONTENTS                               ║
╠════════════════════════════════════════════════════════════════════╣
║ 1. What is DSU?                                                    ║
║ 2. Core Operations                                                 ║
║ 3. Basic Implementation                                            ║
║ 4. Optimizations (Path Compression & Union by Rank/Size)          ║
║ 5. Complete Optimized Implementation                              ║
║ 6. Time & Space Complexity                                        ║
║ 7. When to Use DSU?                                               ║
║ 8. Common Problem Patterns                                        ║
║ 9. Practice Problems                                              ║
╚════════════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════════
1. WHAT IS DSU (DISJOINT SET UNION)?
═══════════════════════════════════════════════════════════════════

DSU is a data structure that keeps track of elements partitioned into 
disjoint (non-overlapping) sets. It efficiently handles:
  • Checking if two elements belong to the same set
  • Merging two sets into one

Think of it as managing groups/components where you can:
  - Find which group an element belongs to
  - Merge two groups together

REAL-WORLD ANALOGY:
Imagine social network friend circles:
  - Each person starts in their own circle
  - When A and B become friends, merge their circles
  - Check if two people are in the same friend network

═══════════════════════════════════════════════════════════════════
2. CORE OPERATIONS
═══════════════════════════════════════════════════════════════════

1. MAKE_SET(x): Create a new set containing only element x
   - Initially, each element is in its own set
   - parent[x] = x (each element is its own parent/representative)

2. FIND(x): Find the representative/root of the set containing x
   - Returns the "leader" or "parent" of the group
   - Two elements are in the same set if FIND(x) == FIND(y)

3. UNION(x, y): Merge the sets containing x and y
   - Find representatives of both sets
   - Make one representative point to the other
   - Now both sets become one

═══════════════════════════════════════════════════════════════════
3. BASIC IMPLEMENTATION (Naive)
═══════════════════════════════════════════════════════════════════
*/

#include <bits/stdc++.h>
using namespace std;

class DSU_Basic {
    vector<int> parent;
    
public:
    // Initialize: each element is its own parent
    DSU_Basic(int n) {
        parent.resize(n);
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find the representative/root of the set containing 'node'
    int find(int node) {
        if(node == parent[node]) {
            return node;  // Found the root
        }
        return find(parent[node]);  // Recursively find root
    }
    
    // Merge sets containing u and v
    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU != rootV) {
            parent[rootU] = rootV;  // Make rootV parent of rootU
        }
    }
    
    // Check if u and v are in the same set
    bool connected(int u, int v) {
        return find(u) == find(v);
    }
};

/*
PROBLEM WITH BASIC IMPLEMENTATION:
- Tree can become skewed (long chain)
- find() can take O(n) time in worst case
- Example: 1->2->3->4->5->6 (linear chain)

SOLUTION: Use optimizations!

═══════════════════════════════════════════════════════════════════
4. OPTIMIZATIONS
═══════════════════════════════════════════════════════════════════

OPTIMIZATION 1: PATH COMPRESSION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
When finding root, make all nodes point directly to root.

Before:     1 → 2 → 3 → 4 (root)
After find(1): 1 ↘
               2 → 4 (root)
               3 ↗

Implementation: return parent[node] = find(parent[node]);

This flattens the tree structure, making future finds faster.


OPTIMIZATION 2: UNION BY RANK
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Always attach smaller tree under larger tree.
Rank ~ approximate depth/height of tree.

Example:
Tree A (rank 2):    Tree B (rank 1):
      1                   5
     / \                  
    2   3                 

Union(A, B) → Attach B under A (smaller under larger):
      1
     /|\
    2 3 5


OPTIMIZATION 3: UNION BY SIZE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Always attach smaller set under larger set.
Size = number of elements in the set.

Similar to union by rank but tracks actual count.

═══════════════════════════════════════════════════════════════════
5. COMPLETE OPTIMIZED IMPLEMENTATION
═══════════════════════════════════════════════════════════════════
*/

class DSU_Optimized {
    vector<int> parent, rank, size;
    int numComponents;  // Track number of disjoint sets
    
public:
    DSU_Optimized(int n) {
        parent.resize(n);
        rank.resize(n, 0);      // Initial rank is 0
        size.resize(n, 1);      // Initial size is 1
        numComponents = n;      // Initially n separate components
        
        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // FIND with PATH COMPRESSION
    int find(int node) {
        if(node == parent[node]) {
            return node;
        }
        // Path compression: flatten tree structure
        return parent[node] = find(parent[node]);
    }
    
    // UNION BY RANK
    void unionByRank(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU == rootV) return;  // Already in same set
        
        numComponents--;  // Two sets merging into one
        
        // Attach smaller rank tree under larger rank tree
        if(rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } 
        else if(rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } 
        else {
            // Equal rank: choose either, increase rank of new root
            parent[rootV] = rootU;
            rank[rootU]++;
        } 
    }
    
    // UNION BY SIZE
    void unionBySize(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if(rootU == rootV) return;
        
        numComponents--;
        
        // Attach smaller size tree under larger size tree
        if(size[rootU] < size[rootV]) {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        } 
        else {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }
    
    // Check if u and v are in same component
    bool connected(int u, int v) {
        return find(u) == find(v);
    }
    
    // Get size of the component containing node
    int getSize(int node) {
        return size[find(node)];
    }
    
    // Get number of disjoint components
    int getNumComponents() {
        return numComponents;
    }
};

/*
═══════════════════════════════════════════════════════════════════
6. TIME & SPACE COMPLEXITY
═══════════════════════════════════════════════════════════════════

WITHOUT OPTIMIZATIONS:
  • Find: O(n) worst case
  • Union: O(n) worst case
  
WITH PATH COMPRESSION + UNION BY RANK/SIZE:
  • Find: O(α(n)) ≈ O(1) amortized
  • Union: O(α(n)) ≈ O(1) amortized
  
  where α(n) is the inverse Ackermann function
  α(n) < 5 for any practical value of n
  (even for n = 2^65536, α(n) = 5)
  
  So effectively: CONSTANT TIME operations!

SPACE COMPLEXITY: O(n)
  • parent array: O(n)
  • rank/size array: O(n)
  • Total: O(n)

═══════════════════════════════════════════════════════════════════
7. WHEN TO USE DSU?
═══════════════════════════════════════════════════════════════════

USE DSU when you need to:
✓ Track connected components in a graph
✓ Detect cycles in undirected graphs
✓ Find if two nodes are in same component
✓ Merge two groups/components
✓ Count number of connected components
✓ Dynamic connectivity problems 

CLASSIC APPLICATIONS:
✓ Kruskal's MST algorithm
✓ Network connectivity
✓ Image processing (connected regions)
✓ Percolation problems
✓ Social network friend circles
✓ Redundant connections

DON'T USE DSU when:
✗ Need to split/disconnect components (DSU only merges)
✗ Need to find path between nodes (use BFS/DFS)
✗ Working with directed graphs (DSU is for undirected)
✗ Need actual edges in component (DSU only tracks connectivity)

═══════════════════════════════════════════════════════════════════
8. COMMON PROBLEM PATTERNS
═══════════════════════════════════════════════════════════════════

PATTERN 1: CYCLE DETECTION
━━━━━━━━━━━━━━━━━━━━━━━━━
For each edge (u, v):
  - If find(u) == find(v): cycle detected!
  - Else: union(u, v)

PATTERN 2: CONNECTED COMPONENTS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
- Process all edges with union operations
- Count unique parent nodes (or use counter)

PATTERN 3: MINIMUM SPANNING TREE (Kruskal's)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
- Sort edges by weight
- For each edge, if connects different components: add to MST

PATTERN 4: GRID CONNECTIVITY
━━━━━━━━━━━━━━━━━━━━━━━━━━━━
- Convert 2D coordinates to 1D: idx = i*cols + j
- Union adjacent cells with same property

PATTERN 5: DYNAMIC QUERIES
━━━━━━━━━━━━━━━━━━━━━━━━━━━
- Process union operations
- Answer connectivity queries

═══════════════════════════════════════════════════════════════════
9. PRACTICE PROBLEMS (EASY TO HARD)
═══════════════════════════════════════════════════════════════════
*/

// ────────────────────────────────────────────────────────────────
// PROBLEM 1: Number of Provinces (LeetCode 547) - EASY
// ────────────────────────────────────────────────────────────────
class Solution_Provinces {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        DSU_Optimized dsu(n);
        
        // Process all connections
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(isConnected[i][j] == 1) {
                    dsu.unionByRank(i, j);
                }
            }
        }
        
        // Count unique components
        return dsu.getNumComponents();
    }
};

// ────────────────────────────────────────────────────────────────
// PROBLEM 2: Redundant Connection (LeetCode 684) - MEDIUM
// ────────────────────────────────────────────────────────────────
class Solution_RedundantConnection {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        DSU_Optimized dsu(n + 1);  // 1-indexed
        
        for(auto& edge : edges) {
            int u = edge[0], v = edge[1];
            
            // If already connected, this edge creates a cycle
            if(dsu.connected(u, v)) {
                return edge;
            }
            
            dsu.unionByRank(u, v);
        }
        
        return {};
    }
};

// ────────────────────────────────────────────────────────────────
// PROBLEM 3: Number of Islands II (LeetCode 305) - HARD
// ────────────────────────────────────────────────────────────────
class Solution_IslandsII {
    int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        DSU_Optimized dsu(m * n);
        vector<vector<bool>> grid(m, vector<bool>(n, false));
        vector<int> result;
        int count = 0;
        
        for(auto& pos : positions) {
            int r = pos[0], c = pos[1];
            int idx = r * n + c;
            
            if(grid[r][c]) {
                result.push_back(count);
                continue;
            }
            
            grid[r][c] = true;
            count++;  // New island
            
            // Check 4 directions
            for(auto& dir : dirs) {
                int nr = r + dir[0], nc = c + dir[1];
                int nidx = nr * n + nc;
                
                if(nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc]) {
                    if(!dsu.connected(idx, nidx)) {
                        dsu.unionByRank(idx, nidx);
                        count--;  // Two islands merged
                    }
                }
            }
            
            result.push_back(count);
        }
        
        return result;
    }
};

// ────────────────────────────────────────────────────────────────
// PROBLEM 4: Satisfiability of Equality Equations (LeetCode 990)
// ────────────────────────────────────────────────────────────────
class Solution_EquationsPossible {
public:
    bool equationsPossible(vector<string>& equations) {
        DSU_Optimized dsu(26);  // 26 letters
        
        // First pass: process all equality equations
        for(string& eq : equations) {
            if(eq[1] == '=') {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';
                dsu.unionByRank(u, v);
            }
        }
        
        // Second pass: check inequality equations
        for(string& eq : equations) {
            if(eq[1] == '!') {
                int u = eq[0] - 'a';
                int v = eq[3] - 'a';
                // If they should be different but are in same set: contradiction
                if(dsu.connected(u, v)) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

// ────────────────────────────────────────────────────────────────
// PROBLEM 5: Longest Consecutive Sequence (LeetCode 128)
// Using DSU approach
// ────────────────────────────────────────────────────────────────
class Solution_LongestConsecutive {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int n = nums.size();
        DSU_Optimized dsu(n);
        unordered_map<int, int> numToIdx;  // num -> index
        
        for(int i = 0; i < n; i++) {
            int num = nums[i];
            
            if(numToIdx.count(num)) continue;  // Duplicate
            
            // Check if num-1 exists
            if(numToIdx.count(num - 1)) {
                dsu.unionBySize(i, numToIdx[num - 1]);
            }
            
            // Check if num+1 exists
            if(numToIdx.count(num + 1)) {
                dsu.unionBySize(i, numToIdx[num + 1]);
            }
            
            numToIdx[num] = i;
        }
        
        // Find maximum component size
        int maxLen = 0;
        for(int i = 0; i < n; i++) {
            maxLen = max(maxLen, dsu.getSize(i));
        }
        
        return maxLen;
    }
};

/*
═══════════════════════════════════════════════════════════════════
MORE PROBLEMS TO PRACTICE:
═══════════════════════════════════════════════════════════════════

EASY:
✓ LeetCode 200: Number of Islands
✓ LeetCode 323: Number of Connected Components (Premium)
✓ LeetCode 1971: Find if Path Exists in Graph

MEDIUM:
✓ LeetCode 547: Number of Provinces
✓ LeetCode 684: Redundant Connection
✓ LeetCode 990: Satisfiability of Equality Equations
✓ LeetCode 721: Accounts Merge
✓ LeetCode 128: Longest Consecutive Sequence
✓ LeetCode 1319: Number of Operations to Make Network Connected
✓ LeetCode 1101: Earliest Moment When Everyone Becomes Friends
✓ LeetCode 1202: Smallest String With Swaps

HARD:
✓ LeetCode 305: Number of Islands II
✓ LeetCode 803: Bricks Falling When Hit
✓ LeetCode 952: Largest Component Size by Common Factor
✓ LeetCode 1579: Remove Max Number of Edges to Keep Graph Traversable

═══════════════════════════════════════════════════════════════════
KEY TAKEAWAYS:
═══════════════════════════════════════════════════════════════════

1. DSU manages disjoint sets with near-constant time operations
2. Always use Path Compression + Union by Rank/Size for optimization
3. Perfect for dynamic connectivity and cycle detection
4. Cannot split components (only merge)
5. Works on undirected graphs
6. Time: O(α(n)) ≈ O(1), Space: O(n)
7. Three main operations: find, union, connected

VISUALIZATION:
Initial: {0} {1} {2} {3} {4}
union(0,1): {0,1} {2} {3} {4}
union(2,3): {0,1} {2,3} {4}
union(1,3): {0,1,2,3} {4}
union(0,4): {0,1,2,3,4}

═══════════════════════════════════════════════════════════════════
*/

int main() {
    // Example usage
    DSU_Optimized dsu(10);
    
    cout << "Initial components: " << dsu.getNumComponents() << endl;
    
    dsu.unionByRank(0, 1);
    dsu.unionByRank(2, 3);
    dsu.unionByRank(4, 5);
    
    cout << "After 3 unions: " << dsu.getNumComponents() << " components" << endl;
    
    cout << "0 and 1 connected? " << (dsu.connected(0, 1) ? "Yes" : "No") << endl;
    cout << "0 and 2 connected? " << (dsu.connected(0, 2) ? "Yes" : "No") << endl;
    
    dsu.unionByRank(1, 3);
    
    cout << "After union(1,3), 0 and 2 connected? " << (dsu.connected(0, 2) ? "Yes" : "No") << endl;
    cout << "Size of component containing 0: " << dsu.getSize(0) << endl;
    
    return 0;
}
