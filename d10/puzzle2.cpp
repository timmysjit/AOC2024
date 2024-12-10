#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void checkPath(int& ans, int i, int j, int height, vector<string>& input_map){
    int m = input_map.size();
    int n = input_map[0].size();
    if (height == 9){
        ans++;
        return;
    }
    if (i > 0 && ((input_map[i-1][j] -48) == (height +1))){
        checkPath(ans, i-1, j, height+1, input_map);
    }
    if (i < m-1 && ((input_map[i+1][j] -48) == (height +1))){
        checkPath(ans, i+1, j, height+1, input_map);
    }
    if (j > 0 && ((input_map[i][j-1] -48) == (height +1))){
        checkPath(ans, i, j-1, height+1, input_map);
    }
    if (j < n-1 && ((input_map[i][j+1] -48) == (height +1))){
        checkPath(ans, i, j+1, height+1, input_map);
    }
}

int trailHeadScores2(){
    ifstream file ("./input");
    vector<string> input_map;
    string line;
    while (getline(file, line)){
        input_map.push_back(line);
    }
    file.close();
    int ans =0;
    int m = input_map.size();
    int n = input_map[0].size();

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (input_map[i][j] != '0')
                continue;
            checkPath(ans, i, j, 0, input_map);
        }
    }
    return ans;
}

int main(){
    int trail_head_scores2 = trailHeadScores2();
    cout << trail_head_scores2;
    return 0;
}