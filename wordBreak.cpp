class Solution {
public:
    bool solve(int idx, string &s, unordered_set<string>&dict, vector<int>&dp) {
        if (idx == s.size()) return true;
        if (dp[idx] != -1) return dp[idx];

        string temp = "";
        for (int i = idx; i < s.size(); i++) {
            temp.push_back(s[i]);
            if (dict.count(temp)) {
                if (solve(i + 1, s, dict, dp))
                    return dp[idx] = true;
            }
        }

        return dp[idx] = false;
    }

    bool wordBreak(string &s, vector<string> &dictionary) {
        unordered_set<string> dict(dictionary.begin(), dictionary.end());
        vector<int> dp(s.size(), -1);
        return solve(0, s, dict, dp);
    }
};

// Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
// Note that the same word in the dictionary may be reused multiple times in the segmentation.
// time complexity: O(n^2) where n is the length of the string s.
// space complexity: O(n) for the dp array and O(m) for the dictionary set
// Approach: Use recursion with memoization (top-down dynamic programming). At each index, try to form words by extending the substring and check if it exists in the dictionary. If a valid word is found, recursively check the remaining substring.
// The dp array stores results of subproblems to avoid redundant calculations.



class Solution {
  public:
  
    bool solve(int idx, string &s, vector<string>&dictionary, string &ds, vector<int>&dp){
        if(idx==s.length()){
            return true;
        }
        
        if(dp[idx]!=-1) return dp[idx];
        
        
        for(int i=0 ; i<dictionary.size() ; i++){
            ds += dictionary[i];
            if(s.find(ds)==0){
              dp[idx] = solve(idx+dictionary[i].size(), s, dictionary, ds, dp);
              if(dp[idx]) return true;
            }
            ds.erase(ds.size() - dictionary[i].size());
            
        }
        
       return dp[idx] = false;
    }
   
    bool wordBreak(string &s, vector<string> &dictionary) {
        // code here
        string ds = "";
        int idx = 0;
        int n = s.length();
        vector<int>dp(n, -1);
        return solve(idx, s, dictionary, ds, dp);
    }
};


// Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
// Note that the same word in the dictionary may be reused multiple times in the segmentation.
// time complexity: O(n*m*k) where n is the length of the string s, m is the number of words in the dictionary, and k is the average length of the words in the dictionary.
// space complexity: O(n) for the dp array and O(m*k) for the dictionary set
// Approach: Use recursion with memoization (top-down dynamic programming). At each index, try