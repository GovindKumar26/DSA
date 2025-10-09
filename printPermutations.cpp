#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 123;
    vector<int> digits;

    while(n > 0){
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());

    sort(digits.begin(), digits.end()); // start from smallest permutation

    do {
        for(int d : digits) cout << d;
        cout << endl;
    } while(next_permutation(digits.begin(), digits.end()));

    return 0;
}

// time complexity: O(n * n!)
// space complexity: O(n)
// print all permutations of a number




#include <bits/stdc++.h>
using namespace std;

void permute(vector<int>& digits, int idx, vector<vector<int>>& result){
    if(idx == digits.size()){
        result.push_back(digits);
        return;
    }
    for(int i = idx; i < digits.size(); i++){
        swap(digits[i], digits[idx]);
        permute(digits, idx+1, result);
        swap(digits[i], digits[idx]); // backtrack
    }
}

int main(){
    int n = 123;
    vector<int> digits;
    while(n > 0){
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());

    vector<vector<int>> result;
    permute(digits, 0, result);

    for(auto &p : result){
        for(int d : p) cout << d;
        cout << endl;
    }

    return 0;
}

// time complexity: O(n * n!)
// space complexity: O(n * n!) for storing all permutations
// print all permutations of a number
// e.g., input: 123
// output: 123, 132, 213, 231, 312, 321