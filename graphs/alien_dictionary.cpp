// Alien Dictionary (LeetCode Premium 269 / GFG)
// Problem: Given a sorted dictionary of an alien language having N words and k starting 
// alphabets of standard dictionary. Find the order of characters in the alien language.
// Note: Many alien language orders are possible. Return any valid order.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findOrder(string dict[], int N, int K) {
        // Build graph
        vector<set<int>> adj(K);
        vector<int> indegree(K, 0);
        
        // Compare adjacent words to find character ordering
        for(int i = 0; i < N - 1; i++) {
            string word1 = dict[i];
            string word2 = dict[i + 1];
            
            int minLen = min(word1.length(), word2.length());
            
            // Find first different character
            for(int j = 0; j < minLen; j++) {
                if(word1[j] != word2[j]) {
                    int u = word1[j] - 'a';
                    int v = word2[j] - 'a';
                    
                    // Add edge only if not already present
                    if(adj[u].find(v) == adj[u].end()) {
                        adj[u].insert(v);
                        indegree[v]++;
                    }
                    break;
                }
            }
        }
        
        // Topological sort using Kahn's Algorithm
        queue<int> q;
        for(int i = 0; i < K; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        
        string result = "";
        
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            result += (char)(node + 'a');
            
            for(int neighbor : adj[node]) {
                indegree[neighbor]--;
                if(indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return result;
    }
};

int main() {
    int N, K;
    cin >> N >> K;
    
    string dict[N];
    for(int i = 0; i < N; i++) {
        cin >> dict[i];
    }
    
    Solution obj;
    string result = obj.findOrder(dict, N, K);
    
    cout << "Alien dictionary order: " << result << endl;
    
    return 0;
}

// Time Complexity: O(N * L + K)
// where N = number of words, L = average length of words, K = number of unique characters
// - Comparing adjacent words: O(N * L)
// - Topological sort: O(K + E) where E is number of edges
// - Overall: O(N * L + K)
//
// Space Complexity: O(K)
// - Adjacency list: O(K + E)
// - Indegree array: O(K)
// - Queue: O(K)
// - Overall: O(K)
//
// Explanation:
// We need to find the character ordering in an alien language given a sorted dictionary.
// The key insight is that if word1 comes before word2, the first differing character
// in word1 must come before the corresponding character in word2 in the alien alphabet.
//
// Algorithm:
// 1. Compare each pair of adjacent words in the dictionary
// 2. Find the first position where characters differ
// 3. Create a directed edge from word1[j] to word2[j] (word1[j] comes before word2[j])
// 4. Build a graph with characters as nodes and ordering as edges
// 5. Perform topological sort using Kahn's Algorithm to get character order
// 6. Return the topological order as the alien dictionary order
//
// Key Insight: The sorted dictionary gives us ordering constraints between characters.
// By comparing adjacent words, we can build a directed graph of character dependencies.
// Topological sort on this graph gives us a valid character ordering.
//
// Example: ["baa", "abcd", "abca", "cab", "cad"]
// Comparing "baa" and "abcd": b comes before a
// Comparing "abca" and "cab": a comes before c
// Comparing "cab" and "cad": b comes before d
// Order: b -> a -> c -> d
