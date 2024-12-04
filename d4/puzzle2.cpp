#include <iostream>
#include <vector>
#include <string>

using namespace std;

int x_mas(){
    vector<string> puzzle;
    string line;
    while (getline(cin, line)){
        puzzle.push_back(line);
    }
    int m = puzzle.size();
    int n = puzzle[0].length();
    int ans = 0;
    
    for (int i = 1; i < m-1; i++){
        for (int j = 1; j < n-1; j++){
            if (puzzle[i][j] == 'A'){
                if (puzzle[i-1][j-1] == 'M' && puzzle[i+1][j-1] == 'M' && puzzle[i-1][j+1] == 'S' && puzzle[i+1][j+1] == 'S')
                    ans++;
                if (puzzle[i-1][j-1] == 'M' && puzzle[i+1][j-1] == 'S' && puzzle[i-1][j+1] == 'M' && puzzle[i+1][j+1] == 'S')
                    ans++;
                if (puzzle[i-1][j-1] == 'S' && puzzle[i+1][j-1] == 'S' && puzzle[i-1][j+1] == 'M' && puzzle[i+1][j+1] == 'M')
                    ans++;
                if (puzzle[i-1][j-1] == 'S' && puzzle[i+1][j-1] == 'M' && puzzle[i-1][j+1] == 'S' && puzzle[i+1][j+1] == 'M')
                    ans++;
            }
        }
    }
    return ans;
}

int main(){
    int x_mas_occurence = x_mas();
    cout << x_mas_occurence;
    return 0;
}