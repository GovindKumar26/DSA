class Solution {
public:

    bool isValid(vector<vector<char>>board,int row, int col, char c){
        for(int i=0; i<9 ; i++){
            if(board[i][col]==c) return false;
            if(board[row][i]==c) return false;

            if(board[3*(row/3)+i/3][3*(col/3)+i%3]==c) return false;
        }

        return true;
    } 

    bool solve(vector<vector<char>>&board){ 
        for(int i=0;i<board.size();i++)
          for(int j=0;j<board[0].size();j++){
            if(board[i][j]=='.'){

                for(char c='1' ;c<='9';c++){
                    if(isValid(board,i,j,c)){
                        board[i][j] = c;

                        if(solve(board)==true){
                            return true;
                        } else board[i][j]='.';
                    }
                } 
                return false;
            }
          }
          return true;
    }

    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};


// Write a program to solve a Sudoku puzzle by filling the empty cells.
// time complexity: O(9^(m*n)) in the worst case, where m and n are the dimensions of the board (9x9 for standard Sudoku).
// space complexity: O(1) since we are modifying the board in place and using only
// a constant amount of extra space.
// Approach: Use backtracking to fill the empty cells (denoted by '.') with digits from '1' to '9'. For each empty cell, try placing each digit and check if it is valid according to Sudoku rules (no duplicates in the same row, column, or 3x3 sub-grid). If placing a digit leads to a solution, return true. If not, backtrack by resetting the cell and trying the next digit. If all digits are tried and none lead to a solution, return false.
// The isValid function checks if placing a digit in a specific cell is valid by checking the corresponding row, column, and 3x3 sub-grid for duplicates. The solve function recursively attempts to fill the board using backtracking.
// The grid index is calculated using the formula: g = 3 * (i / 3) + (j / 3), where i and j are the row and column indices of the cell. 
// This formula maps the 3x3 sub-grids to indices 0 through 8. 
// For example, the top-left 3x3 grid corresponds to g = 0, the top-middle to g = 1, and so on. 
// The row and column indices are directly used to index into the row and col arrays.