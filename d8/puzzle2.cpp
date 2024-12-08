#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <utility>


using namespace std;

int antinodeCount2(){
    ifstream file ("./input2");

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
        int ant_num = antennas.size();
        if (ant_num == 0){
            continue;
        }

        for (int i = 0; i < ant_num; i++){
            vector<int> cur = antennas[i];
            if (antinodes[cur[0]][cur[1]] == 0){
                antinodes[cur[0]][cur[1]] = 1;
                ans++;
            }
            for (int j = i+1; j < ant_num; j++){
                vector<int> adj_ant = antennas[j];
                int row_diff = adj_ant[0] - cur[0];
                int col_diff = adj_ant[1] - cur[1];

                vector<int> antinode = {adj_ant[0] + row_diff,adj_ant[1] + col_diff};
                while (antinode[0] < m && antinode[0] >= 0 && antinode[1] < n && antinode[1] >= 0){
                    if (antinodes[antinode[0]][antinode[1]] == 0){
                        ans++;
                        antinodes[antinode[0]][antinode[1]] = 1;
                    }
                    antinode[0] += row_diff;
                    antinode[1] += col_diff;
                }
                antinode = {cur[0] - row_diff,cur[1] - col_diff};
                while (antinode[0] < m && antinode[0] >= 0 && antinode[1] < n && antinode[1] >= 0){
                    if (antinodes[antinode[0]][antinode[1]] == 0){
                        ans++;
                        antinodes[antinode[0]][antinode[1]] = 1;
                    }
                    antinode[0] -= row_diff;
                    antinode[1] -= col_diff;
                }
            }
        }
    }


    return ans;
}

int main(){
    int antinode_count2 = antinodeCount2();
    cout << antinode_count2;
    return 0;
}