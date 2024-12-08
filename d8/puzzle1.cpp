#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;

int antinodeCount(){
    ifstream file ("./input1");

    string line;
    vector<string> map;
    while (getline(file, line)){
        map.push_back(line);
    }
    file.close();

    int m = map.size();
    int n = map[0].size();
    unordered_map<char, vector<vector<int>>> umap;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (map[i][j] == '.')
                continue;
            umap[map[i][j]].push_back({i,j});
        }
    }
    int ans = 0;

    vector<vector<int>> antinodes (m, vector<int> (n, 0));

    for (auto it : umap){
        vector<vector<int>> antennas = it.second;
        // cout << it.first << ": ";
        // for (int i = 0; i < antennas.size(); i++){
        //     cout << antennas[i][0] << " " << antennas[i][1] << endl;
        // }
        int row_sz = antennas.size();

        for (int i = 0; i < row_sz; i++){
            vector<int> cur = antennas[i];

            for (int j = i+1; j < row_sz; j++){
                int row_diff = antennas[j][0] - antennas[i][0];
                int col_diff = antennas[j][1] - antennas[i][1];

                vector<int> antinode = {antennas[j][0] + row_diff,antennas[j][1] + col_diff};
                if (antinode[0] < m && antinode[0] >= 0 && antinode[1] < n && antinode[1] >= 0){
                    if (antinodes[antinode[0]][antinode[1]] == 0){
                        ans++;
                        antinodes[antinode[0]][antinode[1]] = 1;
                    }
                }
                antinode = {antennas[i][0] - row_diff,antennas[i][1] - col_diff};
                if (antinode[0] < m && antinode[0] >= 0 && antinode[1] < n && antinode[1] >= 0){
                    if (antinodes[antinode[0]][antinode[1]] == 0){
                        ans++;
                        antinodes[antinode[0]][antinode[1]] = 1;
                    }
                }
            }
        }
    }


    return ans;
}

int main(){
    int antinode_count = antinodeCount();
    cout << antinode_count;
    return 0;
}