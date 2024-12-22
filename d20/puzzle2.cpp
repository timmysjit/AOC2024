#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <unordered_map>
using namespace std;
void print(vector<pair<int,int>> arr){
    for (auto i : arr){
        cout << i.first << " " << i.second << endl;
    }
}

void printmap(vector<vector<int>> map){
    for (auto i : map){
        for (int cell : i)
            cout << cell;
        cout <<endl;
    }
}

vector<vector<int>> dijkstra(vector<vector<int>>& map, pair<int,int> s){
    int m = map.size();
    int n = map[0].size();
    vector<vector<int>> visited (m, vector<int> (n, 0));
    vector<vector<int>> distance (m, vector<int> (n, INT_MAX));
    priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
    distance[s.first][s.second] = 0;    
    pq.push({0, s.first, s.second});

    while (!pq.empty()){
        vector<int> node = pq.top();
        pq.pop();
        if (visited[node[1]][node[2]])
            continue;
        visited[node[1]][node[2]]=1;

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
    return distance;
}

vector<pair<int, int>> reachable_points(vector<vector<int>>& map, int r, int i, int j) {
    int m = map.size();
    int n = map[0].size();
    vector<pair<int, int>> ans;

    for (int y = max(0, i - r); y <= min(m - 1, i + r); y++) {
        for (int x = max(0, j - r); x <= min(n - 1, j + r); x++) {
            if (map[y][x] == 1 && (y != i || x != j) && abs(i - y) + abs(j - x) <= r) {
                ans.push_back({y, x});
            }
        }
    }
    return ans;
}


int raceCondition2(){
    //Parse Input *********
    ifstream file ("./input");
    string line;
    vector<vector<int>> map;
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

    //******************************************************
    int ans = 0;
    vector<vector<int>> dmap = dijkstra(map, start);
    int radius = 20;
    for (int i = 1; i < m-1; i++){
        for (int j = 1; j < n-1; j++){
            if (map[i][j] == 0)
                continue;
            vector<pair<int,int>> paths = reachable_points(map, radius, i, j);
            for (pair<int,int> node : paths){
                int d = (abs(i - node.first) + abs(j -node.second));
                int diff =  (dmap[node.first][node.second] - dmap[i][j]) - d;
                if (diff  >= 100){
                    cout << i << " " << j << " " << node.first << " " <<node.second << endl;
                    ans++;
                }
            }            
        }
    }
    return ans;
}

int main(){
    int race_condition2 = raceCondition2();
    cout << race_condition2;
    return 0;
}