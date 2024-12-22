#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
using namespace std;
int dijkstra(vector<vector<int>> map, pair<int,int> start, pair<int,int> end, vector<pair<int,int>> cheat){
    int m = map.size();
    int n = map[0].size();
    vector<vector<int>> visited (m, vector<int> (n, 0));
    vector<vector<int>> distance (m, vector<int> (n, INT_MAX));
    priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
    distance[start.first][start.second] = 0;    
    pq.push({0, start.first, start.second});

    int cheatcount = 0;
    while (!pq.empty()){
        vector<int> node = pq.top();
        pq.pop();
        if (visited[node[1]][node[2]])
            continue;
        visited[node[1]][node[2]]=1;
        if (cheat[0].first == node[1] && cheat[0].second == node[2]){
            cheatcount =1;
        }   
        if (cheatcount > 0){
            if (visited[node[1] + cheat[1].first][node[2]+cheat[1].second] == 0){
                distance[node[1] + cheat[1].first][node[2]+cheat[1].second] = min(distance[node[1] + cheat[1].first][node[2]+cheat[1].second], 1+ node[0]);
                pq.push({distance[node[1] + cheat[1].first][node[2]+cheat[1].second],node[1] + cheat[1].first, node[2]+cheat[1].second});
                map[node[1] + cheat[1].first][node[2]+cheat[1].second] =1;
            }
            cheatcount--;
        } else{
            if (node[1] > 0 && map[node[1]-1][node[2]] && visited[node[1]-1][node[2]] == 0){
                distance[node[1]-1][node[2]] = min(distance[node[1]-1][node[2]], 1+ node[0]);
                pq.push({distance[node[1]-1][node[2]],node[1]-1, node[2]});
            }
            if (node[1] < m-1 && map[node[1]+1][node[2]] && visited[node[1]+1][node[2]] == 0){
                distance[node[1]+1][node[2]] = min(distance[node[1]+1][node[2]], 1+ node[0]);
                pq.push({distance[node[1]+1][node[2]],node[1]+1, node[2]});
            }
            if (node[2] > 0 && map[node[1]][node[2]-1] && visited[node[1]][node[2]-1] == 0){
                distance[node[1]][node[2]-1] = min(distance[node[1]][node[2]-1], 1+ node[0]);
                pq.push({distance[node[1]][node[2]-1],node[1], node[2]-1});
            }
            if (node[2] < n-1 && map[node[1]][node[2]+1] && visited[node[1]][node[2]+1] == 0){
                distance[node[1]][node[2]+1] = min(distance[node[1]][node[2]+1], 1+ node[0]);
                pq.push({distance[node[1]][node[2]+1],node[1], node[2]+1});
            }
        }
    }
    return distance[end.first][end.second];
}

int raceCondition(){

    ifstream file ("./input");
    string line;
    vector<vector<int>> map;
    string moves = "";
    pair<int,int> start;
    pair<int, int> end;
    while (getline(file, line)){
        if (line.empty())
            continue;
        map.push_back({});
        for (char c : line){
            if (c == '.'){
                map.back().push_back(1);
            } else if (c == '#'){
                map.back().push_back(0);
            } else if (c == 'S'){
                map.back().push_back(1);
                start = {map.size()-1, map.back().size()-1};
            } else{
                map.back().push_back(1);
                end = {map.size()-1, map.back().size()-1};
            }
        }
    }
    int m = map.size();
    int n = map[0].size();
    int ans = 0;
    vector<vector<int>> visited (m, vector<int> (n,0));
    vector<pair<int, int>> dir = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    int nocheat = dijkstra(map, start, end, {{-1,-1}, {-1,-1}});
    for (int i = 1; i < m-1; i++){
        for (int j = 1; j < n -1; j++){
            if (map[i][j] == 0)
                continue;
            for (int k = 0; k < 4; k++){
                if (map[i + dir[k].first][j + dir[k].second] == 1)
                    continue;
                int wcheat = dijkstra(map, start, end,{{i,j},dir[k]});
                if (nocheat - wcheat >= 100){
                    cout << i << " " << j << " " << nocheat - wcheat << endl;
                    ans++;
                }

            }
        }
    }
    return ans;
}

int main(){
    int race_condition = raceCondition();
    cout << race_condition;
    return 0;
}