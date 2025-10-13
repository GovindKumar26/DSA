class Solution {
public:
 bool isPeakElement(vector<vector<int>>& mat, int row, int col){
        int n = mat.size();
        int m = mat[0].size();
        int dxdy[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for(int i=0; i<4; i++){
            int newrow = row + dxdy[i][0];
            int newcol = col + dxdy[i][1];
            if(newrow >= 0 && newcol >= 0 && newrow < n && newcol < m && mat[newrow][newcol] > mat[row][col]){
                return false;
            }
        }
        return true;
    }

    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        //  int n = mat.size();
        // int m = mat[0].size();
        // for(int i=0; i<n; i++){
        //     for(int j=0; j<m; j++){
        //         if(isPeakElement(mat, i, j)){
        //             return {i, j};
        //         }
        //     }
        // }
        // return {-1, -1};


         int n = mat.size();
        int m = mat[0].size();
        int low = 0, high = m-1;
        while(low <= high){
            int maxRow = 0;
            int midCol = (low+high) >> 1;
            for(int row=0; row<n; row++){
                if(mat[row][midCol] > mat[maxRow][midCol]){
                    maxRow = row;
                }
            }
            int currElement =  mat[maxRow][midCol];
            int leftElement = midCol == 0 ? -1 : mat[maxRow][midCol-1];
            int rightElement = midCol == m-1 ? -1 : mat[maxRow][midCol+1];
            if(currElement > leftElement && currElement > rightElement){
                return {maxRow, midCol};
            }
            else if(currElement < leftElement){
                high = midCol - 1;
            }
            else{
                low = midCol + 1;
            }
        }
        return {-1, -1};
    }
};


// time complexity: O(nlogm)
// space complexity: O(1)
// A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom. Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].