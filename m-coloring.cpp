class Solution {
  public:
    // helper function to check if we can color vertex `node` with `c`
    bool isSafe(int node, int c, vector<int> &color, vector<vector<int>> &adj) {
        for (int nei : adj[node]) {
            if (color[nei] == c) return false;
        }
        return true;
    }

    // backtracking function
    bool solve(int node, int v, vector<vector<int>> &adj, vector<int> &color, int m) {
        if (node == v) return true; // all vertices colored

        for (int c = 1; c <= m; c++) {
            if (isSafe(node, c, color, adj)) {
                color[node] = c;
                if (solve(node + 1, v, adj, color, m)) return true;
                color[node] = 0; // backtrack
            }
        }
        return false;
    }

    bool graphColoring(int v, vector<vector<int>> &edges, int m) {
        // Build adjacency list
        vector<vector<int>> adj(v);
        for (auto &e : edges) {
            int u = e[0], w = e[1];
            adj[u].push_back(w);
            adj[w].push_back(u);
        }

        vector<int> color(v, 0); // 0 means uncolored
        return solve(0, v, adj, color, m);
    }
};


// Given an undirected graph and an integer M, determine if the graph can be colored with at most M colors such that no two adjacent vertices of the graph are colored with the same color.
// time complexity: O(M^V) in the worst case, where V is the number of vertices and M is the number of colors.
// space complexity: O(V) for the color array and O(V + E) for the adjacency list, where E is the number of edges.
// Approach: Use backtracking to try and color each vertex with one of the M colors, ensuring that no two adjacent vertices share the same color. If a valid coloring is found, return true; otherwise, backtrack and try a different color.
// The isSafe function checks if it's safe to color a vertex with a given color by checking its adjacent vertices. The solve function recursively attempts to color each vertex.