// User function template in C++

class Solution {
  public:
    // Function to return the count of number of elements in union of two arrays.
    int doUnion(vector<int> arr1, vector<int> arr2) {
        
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        
        vector<int>ans;
        
        int i = 0, j = 0;
        int n1 = arr1.size(), n2 = arr2.size();
        while(i<n1 && j<n2){
            if(arr1[i]<=arr2[j]){
                if(ans.size()==0 || ans.back()!=arr1[i]){
                    ans.push_back(arr1[i]);
                }
                i++;
            }
            
            else if(arr2[j]<=arr1[i]){
                if(ans.size()==0 || ans.back()!=arr2[j]){
                    ans.push_back(arr2[j]);
                }
                j++;
            }
        }
        
        while(i<n1){
          
                if(ans.size()==0 || ans.back()!=arr1[i]){
                    ans.push_back(arr1[i]);
                }
                i++;
        }
        
        while(j<n2){
           
                if(ans.size()==0 || ans.back()!=arr2[j]){
                    ans.push_back(arr2[j]);
                }
                j++;
        }
        
        return ans.size();
        
    
        
        
    //   set<int>st;
    //   for(auto i : arr1) st.insert(i);
    //   for(auto i : arr2) st.insert(i);
      
    //   vector<int>ans;
    //   for(auto i : st){
    //       ans.push_back(i);
    //   }
      
    //   return ans.size();
     }
};





// You are given two arrays a[] and b[], return the Union of both the arrays in any order.

// The Union of two arrays is a collection of all distinct elements present in either of the arrays. If an element appears more than once in one or both arrays, it should be included