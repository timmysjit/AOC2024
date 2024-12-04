#include <iostream>
#include <vector>
#include <string>

using namespace std;

int xmas(){
    vector<string> puzzle;
    string temp;
    while (getline(cin, temp)){
        puzzle.push_back(temp);
    }
    int m = puzzle.size();
    int n = puzzle[0].length();
    int ans = 0;
    
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (puzzle[i][j] == 'X'){
                //horizontal forward
                if (j < n-3){
                    
                    if (puzzle[i][j+1] == 'M' && puzzle[i][j+2] == 'A' && puzzle[i][j+3] == 'S')
                        ans++;
                }

                //horizontal backward
                if (j > 2){
                    if (puzzle[i][j-1] == 'M' && puzzle[i][j-2] == 'A' && puzzle[i][j-3] == 'S')
                        ans++;
                }
                //vertical forward
                if (i < m-3){
                    if (puzzle[i+1][j] == 'M' && puzzle[i+2][j] == 'A' && puzzle[i+3][j] == 'S')
                        ans++;
                }
                //vertical backward
                if (i > 2){
                    if (puzzle[i-1][j] == 'M' && puzzle[i-2][j] == 'A' && puzzle[i-3][j] == 'S')
                        ans++;
                }
                //diagonal top left to bottom right forward
                if (i < m-3 && j < n-3){
                    if (puzzle[i+1][j+1] == 'M' && puzzle[i+2][j+2] == 'A' && puzzle[i+3][j+3] == 'S')
                        ans++;  
                }
                //diagonal top left to bottom right backward
                if (i > 2 && j > 2){
                    if (puzzle[i-1][j-1] == 'M' && puzzle[i-2][j-2] == 'A' && puzzle[i-3][j-3] == 'S')
                        ans++;  
                }
                //diagonal top right to bottom left forward
                if (i < m-3 && j > 2){
                    if (puzzle[i+1][j-1] == 'M' && puzzle[i+2][j-2] == 'A' && puzzle[i+3][j-3] == 'S')
                        ans++;  
                }
                //diagonal top right to bottom left backward
                if (i > 2 && j < n-3){
                    if (puzzle[i-1][j+1] == 'M' && puzzle[i-2][j+2] == 'A' && puzzle[i-3][j+3] == 'S')
                        ans++;  
                }
            }
        }
    }
    return ans;
}

int main(){
    int xmas_occurence = xmas();
    cout << xmas_occurence;
    return 0;
}