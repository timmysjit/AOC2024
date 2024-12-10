#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
using namespace std;

void checkPath(int& ans, int i, int j, int height, vector<string>& input_map, map<string, int> & mp){
    int m = input_map.size();
    int n = input_map[0].size();
    if (height == 9){
        string code (1, i+48);
        code += (j+48);
        if (mp[code] == 0){
            ans++;
            mp[code] = 1;
        }
        return;
    }
    if (i > 0 && ((input_map[i-1][j] -48) == (height +1))){
        checkPath(ans, i-1, j, height+1, input_map, mp);
    }
    if (i < m-1 && ((input_map[i+1][j] -48) == (height +1))){
        checkPath(ans, i+1, j, height+1, input_map, mp);
    }
    if (j > 0 && ((input_map[i][j-1] -48) == (height +1))){
        checkPath(ans, i, j-1, height+1, input_map, mp);
    }
    if (j < n-1 && ((input_map[i][j+1] -48) == (height +1))){
        checkPath(ans, i, j+1, height+1, input_map, mp);
    }
}

int trailHeadScores(){
    ifstream file ("./input");
    vector<string> input_map;
    string line;
    while (getline(file, line)){
        input_map.push_back(line);
    }
    file.close();
    // for (int i = 0; i< input_map.size(); i++){
    //     for (int j = 0; j < input_map[i].size(); j++){
    //         cout << input_map[i][j] << " " ;
    //     } cout <<endl;
    // }
    int ans =0;
    int m = input_map.size();
    int n = input_map[0].size();

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (input_map[i][j] != '0')
                continue;
            map<string, int> mp;
            checkPath(ans, i, j, 0, input_map, mp);
        }
    }
    return ans;
}

int main(){
    int trail_head_scores = trailHeadScores();
    cout << trail_head_scores;
    return 0;
}