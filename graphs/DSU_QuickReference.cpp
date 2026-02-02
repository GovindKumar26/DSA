// ====================================================================
// DSU QUICK REFERENCE CARD & TESTING
// ====================================================================

/*
╔════════════════════════════════════════════════════════════════════╗
║                   DSU QUICK REFERENCE                              ║
╚════════════════════════════════════════════════════════════════════╝

CORE TEMPLATE (Copy-Paste Ready):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

#include <bits/stdc++.h>
using namespace std;

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
    
    bool connected(int x, int y) { return find(x) == find(y); }
};

/*
╔════════════════════════════════════════════════════════════════════╗
║                   COMMON OPERATIONS                                ║
╚════════════════════════════════════════════════════════════════════╝

INITIALIZATION:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
DSU dsu(n);                    // Create DSU with n elements (0 to n-1)

BASIC OPERATIONS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
dsu.find(x)                    // Find representative of x's set
dsu.unite(x, y)                // Merge sets containing x and y
dsu.connected(x, y)            // Check if x and y in same set

GRID PROBLEMS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
int idx = i * cols + j         // Convert (i,j) to 1D index
int i = idx / cols             // Convert 1D to row
int j = idx % cols             // Convert 1D to col

CYCLE DETECTION:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
if (dsu.find(u) == dsu.find(v))
    // Cycle detected!
else
    dsu.unite(u, v)

COUNT COMPONENTS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
int count = 0;
for(int i = 0; i < n; i++)
    if(dsu.find(i) == i) count++;
*/

/*
╔════════════════════════════════════════════════════════════════════╗
║                   TIME COMPLEXITY CHEAT SHEET                      ║
╚════════════════════════════════════════════════════════════════════╝

Operation          | Without Optimization | With Optimization
─────────────────────────────────────────────────────────────────
find()            | O(n) worst          | O(α(n)) ≈ O(1)
unite()           | O(n) worst          | O(α(n)) ≈ O(1)
connected()       | O(n) worst          | O(α(n)) ≈ O(1)
M operations      | O(M·n)              | O(M·α(n)) ≈ O(M)

Optimizations needed:
✓ Path Compression (in find)
✓ Union by Rank or Union by Size (in unite)

α(n) = Inverse Ackermann function (< 5 for all practical n)
*/

/*
╔════════════════════════════════════════════════════════════════════╗
║                   PROBLEM PATTERNS                                 ║
╚════════════════════════════════════════════════════════════════════╝

PATTERN                      | APPROACH
─────────────────────────────────────────────────────────────────
Connected Components         | Union all edges, count unique parents
Cycle Detection              | If find(u)==find(v), edge (u,v) creates cycle
Minimum Spanning Tree        | Kruskal's: sort edges, add if no cycle
Grid Connectivity            | Convert 2D → 1D, unite adjacent cells
Redundant Connections        | Track which edges don't merge components
Network Problems             | Unite connections, check final components
String/Array Grouping        | Unite based on common properties
Dynamic Connectivity         | Process operations in order
Offline Queries              | Sometimes process in reverse
*/

/*
╔════════════════════════════════════════════════════════════════════╗
║                   TESTING EXAMPLES                                 ║
╚════════════════════════════════════════════════════════════════════╝
*/

// Test 1: Basic connectivity
void test_basic() {
    cout << "\n=== TEST 1: Basic Connectivity ===" << endl;
    DSU dsu(5);
    
    cout << "Initial state: 5 separate components" << endl;
    cout << "0 and 1 connected? " << dsu.connected(0, 1) << " (Expected: 0)" << endl;
    
    dsu.unite(0, 1);
    cout << "\nAfter unite(0, 1):" << endl;
    cout << "0 and 1 connected? " << dsu.connected(0, 1) << " (Expected: 1)" << endl;
    
    dsu.unite(2, 3);
    dsu.unite(1, 2);
    cout << "\nAfter unite(2, 3) and unite(1, 2):" << endl;
    cout << "0 and 3 connected? " << dsu.connected(0, 3) << " (Expected: 1)" << endl;
    cout << "0 and 4 connected? " << dsu.connected(0, 4) << " (Expected: 0)" << endl;
}

// Test 2: Cycle detection
void test_cycle_detection() {
    cout << "\n=== TEST 2: Cycle Detection ===" << endl;
    DSU dsu(4);
    
    vector<pair<int,int>> edges = {{0,1}, {1,2}, {2,3}};
    
    cout << "Adding edges: (0,1), (1,2), (2,3)" << endl;
    for(auto [u, v] : edges) {
        if(dsu.connected(u, v)) {
            cout << "Edge (" << u << "," << v << ") creates cycle!" << endl;
        } else {
            dsu.unite(u, v);
            cout << "Edge (" << u << "," << v << ") added" << endl;
        }
    }
    
    cout << "\nTrying to add edge (0,3):" << endl;
    if(dsu.connected(0, 3)) {
        cout << "Edge (0,3) would create cycle! (Expected)" << endl;
    }
}

// Test 3: Count components
void test_count_components() {
    cout << "\n=== TEST 3: Count Components ===" << endl;
    DSU dsu(10);
    
    vector<pair<int,int>> edges = {{0,1}, {2,3}, {4,5}, {6,7}, {1,2}};
    
    auto countComponents = [&]() {
        int count = 0;
        for(int i = 0; i < 10; i++) {
            if(dsu.find(i) == i) count++;
        }
        return count;
    };
    
    cout << "Initial components: " << countComponents() << " (Expected: 10)" << endl;
    
    for(auto [u, v] : edges) {
        dsu.unite(u, v);
    }
    
    cout << "After unions: " << countComponents() << " (Expected: 6)" << endl;
    cout << "Components: {0,1,2,3}, {4,5}, {6,7}, {8}, {9}" << endl;
}

// Test 4: Grid conversion
void test_grid_conversion() {
    cout << "\n=== TEST 4: Grid Conversion (2D to 1D) ===" << endl;
    int rows = 3, cols = 4;
    
    cout << "Grid: 3x4" << endl;
    cout << "Position | 1D Index" << endl;
    cout << "─────────────────" << endl;
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            int idx = i * cols + j;
            cout << "(" << i << "," << j << ")    | " << idx << endl;
        }
    }
    
    cout << "\nReverse conversion:" << endl;
    int idx = 7;
    int i = idx / cols;
    int j = idx % cols;
    cout << "Index " << idx << " -> Position (" << i << "," << j << ")" << endl;
}

// Test 5: Performance test
void test_performance() {
    cout << "\n=== TEST 5: Performance Test ===" << endl;
    
    int n = 100000;
    DSU dsu(n);
    
    auto start = chrono::high_resolution_clock::now();
    
    // Random unions
    for(int i = 0; i < n - 1; i++) {
        dsu.unite(i, i + 1);
    }
    
    // Random finds
    for(int i = 0; i < 100000; i++) {
        dsu.find(rand() % n);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Performed " << n << " unions and 100000 finds" << endl;
    cout << "Time taken: " << duration.count() << " ms" << endl;
    cout << "(Should be very fast with optimizations)" << endl;
}

/*
╔════════════════════════════════════════════════════════════════════╗
║                   VISUALIZATION HELPER                             ║
╚════════════════════════════════════════════════════════════════════╝
*/

class DSU_Visualizer {
    vector<int> parent, rank;
    int n;
    
public:
    DSU_Visualizer(int size) : n(size) {
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
    
    void visualize() {
        cout << "\nCurrent DSU State:" << endl;
        cout << "Node   : ";
        for(int i = 0; i < n; i++) cout << setw(3) << i;
        cout << "\nParent : ";
        for(int i = 0; i < n; i++) cout << setw(3) << parent[i];
        cout << "\nRank   : ";
        for(int i = 0; i < n; i++) cout << setw(3) << rank[i];
        cout << endl;
        
        // Group by components
        map<int, vector<int>> components;
        for(int i = 0; i < n; i++) {
            components[find(i)].push_back(i);
        }
        
        cout << "\nComponents:" << endl;
        for(auto& [root, nodes] : components) {
            cout << "{";
            for(int i = 0; i < nodes.size(); i++) {
                if(i > 0) cout << ",";
                cout << nodes[i];
            }
            cout << "} ";
        }
        cout << endl;
    }
};

void test_visualization() {
    cout << "\n=== VISUALIZATION TEST ===" << endl;
    DSU_Visualizer dsu(8);
    
    cout << "\nInitial state:";
    dsu.visualize();
    
    cout << "\nAfter unite(0, 1):";
    dsu.unite(0, 1);
    dsu.visualize();
    
    cout << "\nAfter unite(2, 3) and unite(4, 5):";
    dsu.unite(2, 3);
    dsu.unite(4, 5);
    dsu.visualize();
    
    cout << "\nAfter unite(1, 2):";
    dsu.unite(1, 2);
    dsu.visualize();
}

/*
╔════════════════════════════════════════════════════════════════════╗
║                   MAIN TEST RUNNER                                 ║
╚════════════════════════════════════════════════════════════════════╝
*/

int main() {
    cout << "╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║         DSU QUICK REFERENCE & TESTING SUITE           ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    
    test_basic();
    test_cycle_detection();
    test_count_components();
    test_grid_conversion();
    test_visualization();
    test_performance();
    
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║                   ALL TESTS COMPLETED                  ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\nFiles to study:" << endl;
    cout << "1. DSU_Complete_Guide.cpp - Comprehensive theory & problems" << endl;
    cout << "2. DSU_Practice_1_MakingALargeIsland.cpp" << endl;
    cout << "3. DSU_Practice_2_SmallestStringWithSwaps.cpp" << endl;
    cout << "4. DSU_Practice_3_NetworkConnected.cpp" << endl;
    cout << "5. DSU_Practice_4_LargestComponentByFactor.cpp" << endl;
    cout << "6. DSU_Practice_5_RemoveMaxEdges.cpp" << endl;
    cout << "7. DSU_Practice_6_CycleDetection.cpp" << endl;
    cout << "8. DSU_Advanced_InterviewGuide.cpp" << endl;
    cout << "9. accounts_merge.cpp (in your graphs folder)" << endl;
    cout << "10. kruskals_algorithm.cpp (in your graphs folder)" << endl;
    
    return 0;
}

/*
╔════════════════════════════════════════════════════════════════════╗
║                   COMPILATION & EXECUTION                          ║
╚════════════════════════════════════════════════════════════════════╝

COMPILE:
g++ -std=c++17 -O2 DSU_QuickReference.cpp -o dsu_test

RUN:
./dsu_test

OR (Windows):
dsu_test.exe

ONLINE JUDGE TEMPLATE:
Just copy the DSU class and use it in your solution!

╔════════════════════════════════════════════════════════════════════╗
║                   STUDY PLAN                                       ║
╚════════════════════════════════════════════════════════════════════╝

DAY 1: Fundamentals
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Read DSU_Complete_Guide.cpp sections 1-6
□ Understand find and union operations
□ Learn path compression and union by rank
□ Solve LeetCode 547 (Provinces)

DAY 2: Basic Problems
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Solve LeetCode 684 (Redundant Connection)
□ Solve LeetCode 990 (Equality Equations)
□ Practice cycle detection
□ Study DSU_Practice_6_CycleDetection.cpp

DAY 3: Intermediate Problems
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Solve LeetCode 1202 (Smallest String With Swaps)
□ Solve LeetCode 1319 (Network Connected)
□ Solve LeetCode 721 (Accounts Merge)
□ Study DSU_Practice_2 and DSU_Practice_3

DAY 4: Advanced Problems
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Solve LeetCode 827 (Making A Large Island)
□ Solve LeetCode 952 (Largest Component by Factor)
□ Study DSU_Practice_4
□ Learn weighted DSU from DSU_Advanced_InterviewGuide.cpp

DAY 5: Hard Problems & Interview Prep
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Solve LeetCode 1579 (Remove Max Edges)
□ Solve LeetCode 305 (Number of Islands II)
□ Review DSU_Advanced_InterviewGuide.cpp
□ Practice explaining DSU in interviews

╔════════════════════════════════════════════════════════════════════╗
║                   FINAL CHECKLIST                                  ║
╚════════════════════════════════════════════════════════════════════╝

Before Your Interview:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
□ Can implement DSU from scratch in < 5 minutes
□ Know when to use DSU vs DFS/BFS
□ Understand time complexity (α(n))
□ Can explain path compression
□ Can explain union by rank/size
□ Solved at least 10 DSU problems
□ Can recognize DSU patterns
□ Know grid → 1D index conversion
□ Practiced cycle detection
□ Familiar with Kruskal's algorithm

*/
