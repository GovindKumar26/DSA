class Solution {
  public:
    vector<int> findMajority(vector<int>& arr) {
        // Code here
        
        int cnt1 = 0, cnt2 = 0;
        int ele1=INT_MIN , ele2=INT_MIN;
        int n = arr.size();

        for(int i=0 ; i<n ; i++){
            if(cnt1==0 && ele2!=arr[i]){
                cnt1 = 1;
                ele1 = arr[i];
            } else if(cnt2==0 && ele1!=arr[i]){
                cnt2 = 1;
                ele2 = arr[i];
            }
            else if(ele1==arr[i]) cnt1++;
            else if(ele2==arr[i]) cnt2++;
            else{
                cnt1--, cnt2--;
            }
        }
     
        vector<int>ans;
        cnt1=0, cnt2=0;
        for(int i=0 ; i<n ; i++){
             if(arr[i]==ele1) cnt1++;
             if(arr[i]==ele2) cnt2++;
        }

        if (cnt1 > n / 3) ans.push_back(ele1);
        if (cnt2 > n / 3 && ele2 != ele1) ans.push_back(ele2);  
        sort(ans.begin(), ans.end());
        return ans;
    }
};

// time complexity: O(n)
// space complexity: O(1)
// Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.