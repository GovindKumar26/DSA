#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Function to find element at position (r, c) in Pascal's triangle
    // Assuming 1-indexed: row r, column c
    int pascalTriangleI(int r, int c) {
        // Element at row r, column c is C(r-1, c-1)
        // Using formula: C(n, r) = n! / (r! * (n-r)!)
        // Optimized: C(n, r) = (n * (n-1) * ... * (n-r+1)) / (r!)
        
        if (c > r || c < 1) return 0;
        
        long long result = 1;
        int n = r - 1;
        int k = c - 1;
        
        // Optimize by using smaller k
        if (k > n - k) {
            k = n - k;
        }
        
        // Calculate C(n, k) = n! / (k! * (n-k)!)
        for (int i = 0; i < k; i++) {
            result = result * (n - i) / (i + 1);
        }
        
        return result;
    }
    
    // Generate entire row of Pascal's triangle
    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex + 1, 1);
        
        for (int i = 1; i < rowIndex; i++) {
            row[i] = (long long)row[i-1] * (rowIndex - i + 1) / i;
        }
        
        return row;
    }
    
    // Generate first n rows of Pascal's triangle
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;
        
        for (int i = 0; i < numRows; i++) {
            vector<int> row(i + 1, 1);
            
            for (int j = 1; j < i; j++) {
                row[j] = triangle[i-1][j-1] + triangle[i-1][j];
            }
            
            triangle.push_back(row);
        }
        
        return triangle;
    }
};

int main() {
    Solution sol;
    
    // Test pascalTriangleI
    cout << "Element at row 5, column 3: " << sol.pascalTriangleI(5, 3) << endl; // Expected: 6
    cout << "Element at row 6, column 2: " << sol.pascalTriangleI(6, 2) << endl; // Expected: 5
    
    // Test getRow
    cout << "\nRow 4 of Pascal's triangle: ";
    vector<int> row = sol.getRow(4);
    for (int num : row) {
        cout << num << " ";
    }
    cout << endl;
    
    // Test generate
    cout << "\nFirst 5 rows of Pascal's triangle:" << endl;
    vector<vector<int>> triangle = sol.generate(5);
    for (auto& r : triangle) {
        for (int num : r) {
            cout << num << " ";
        }
        cout << endl;
    }
    
    return 0;
}
