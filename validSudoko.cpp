class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int n, g;
        bool row[9][9] = {0}, col[9][9] = {0}, grid[9][9] = {0};

        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    n = board[i][j] - '1';
                    g = 3 * (i / 3) + (j / 3);

                    if (col[j][n] || row[i][n] || grid[g][n]) {
                        return false;
                    }

                    col[j][n] = row[i][n] = grid[g][n] = true;
                }              
            }
        return true;
    }
};

// Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the rules of Sudoku.
// time complexity: O(1) since the board size is fixed (9x9).
// space complexity: O(1) since the size of the auxiliary arrays is fixed (9x9).
// Approach: Use three 2D boolean arrays to track the presence of numbers in each row
// , column, and 3x3 sub-grid. Iterate through each cell in the board, and for each filled cell, check if the number has already been seen in the corresponding row, column, or sub-grid. If it has, return false. If not, mark it as seen. If the entire board is traversed without conflicts, return true.
// The grid index is calculated using the formula: g = 3 * (i / 3) + (j / 3), where i and j are the row and column indices of the cell. 
// This formula maps the 3x3 sub-grids to indices 0 through 8. 
// For example, the top-left 3x3 grid corresponds to g = 0, the top-middle to g = 1, and so on.
// The row and column indices are directly used to index into the row and col arrays.