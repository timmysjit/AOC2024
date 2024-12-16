#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <queue>
using namespace std;

void dfs(vector<vector<int>>& distance, int i, int j , vector<vector<int>>& visited, int& ans, int dir){
    cout << i << " "<< j << " " << dir << " " << distance[i][j]<< " " << ans <<endl;
    
    if (visited[i][j] == 0)
        ans++;
    visited[i][j]=1;

        
    if (distance[i][j] - distance[i-1][j] == 1001 ||distance[i][j] - distance[i-1][j] == 1 ){
        dfs(distance, i-1, j, visited, ans, 0);
    } else if (distance[i][j] - distance[i-1][j] == -999 && dir == 0){
        dfs(distance, i-1, j, visited, ans, 0);
    }



    if (distance[i][j] - distance[i+1][j] == 1001 || distance[i][j] - distance[i+1][j] == 1){
        dfs(distance, i+1, j, visited, ans, 2);
    }else if (distance[i][j] - distance[i+1][j] == -999 && dir == 2){
        dfs(distance, i+1, j, visited, ans, 2);
    }


    if (distance[i][j] - distance[i][j+1] == 1001 || distance[i][j] - distance[i][j+1] == 1){
        dfs(distance, i, j+1, visited, ans, 1);
    } else if (distance[i][j] - distance[i][j+1] == -999 && dir == 1){
        dfs(distance, i, j+1, visited, ans, 1);
    }


    if (distance[i][j] - distance[i][j-1] == 1001 || distance[i][j] - distance[i][j-1] == 1){
        dfs(distance, i, j-1, visited, ans, 3);
    } else if (distance[i][j] - distance[i][j-1] == -999 && dir == 3){
        dfs(distance, i, j-1, visited, ans, 3);
    }

        
}

int dijkstra(vector<string>& map){
    int m = map.size();
    int n = map[0].length();
    vector<vector<int>> visited (m, vector<int> (n, 0));
    vector<vector<int>> distance (m, vector<int> (n, INT_MAX));
    priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
    distance[m-2][1] = 0;    
    pq.push({0, m-2, 1, 1});
    while (!pq.empty()){
        vector<int> e = pq.top();
        pq.pop();
        if (visited[e[1]][e[2]])
            continue;
        visited[e[1]][e[2]]=1;

        int dist = 1;
        if (map[e[1]-1][e[2]] != '#' && visited[e[1]-1][e[2]] == 0){
            if (e[3] == 1 || e[3] == 3)
                dist+= 1000;
            distance[e[1]-1][e[2]] = min(distance[e[1]-1][e[2]], dist+ e[0]);
            pq.push({distance[e[1]-1][e[2]], e[1]-1, e[2], 0});
        }

        dist = 1;
        if (map[e[1]+1][e[2]] != '#' && visited[e[1]+1][e[2]] == 0){
            if (e[3] == 1 || e[3] == 3)
                dist+= 1000;
            distance[e[1]+1][e[2]] = min(distance[e[1]+1][e[2]], dist+ e[0]);
            pq.push({distance[e[1]+1][e[2]], e[1]+1, e[2], 2});
        }
        dist = 1;
        if (map[e[1]][e[2]+1] != '#' && visited[e[1]][e[2]+1] == 0){
            if (e[3] == 0 || e[3] == 2)
                dist+= 1000;
            distance[e[1]][e[2]+1] = min(distance[e[1]][e[2]+1], dist+ e[0]);

            pq.push({distance[e[1]][e[2]+1], e[1], e[2]+1, 1});
        }
        dist = 1;
        if (map[e[1]][e[2]-1] != '#' && visited[e[1]][e[2]-1] == 0){
            if (e[3] == 0 || e[3] == 2)
                dist+= 1000;
            distance[e[1]][e[2]-1] = min(distance[e[1]][e[2]-1], dist+ e[0]);

            pq.push({distance[e[1]][e[2]-1], e[1], e[2]-1, 3});
        }
        
    }
    
    int ans = 0;
    vector<vector<int>> visited2 (m, vector<int> (n, 0));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (map[i][j] == '#')
                visited2[i][j] = 1;
        }
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (distance[i][j] == INT_MAX)
                cout << 0 << "\t";
            else
                cout << distance[i][j] << "\t";
        } cout <<endl;
    }
    dfs(distance, 1, n-2, visited2, ans, 2);
    return ans;
}
int reindeerRace(){

    ifstream file ("./input");
    string line;
    vector<string> map;
    string moves = "";
    while (getline(file, line)){
        if (line.empty())
            continue;
        map.push_back(line);   
    }
    return dijkstra(map);
}

int main(){
    int reindeer_race = reindeerRace();
    cout << reindeer_race;
    return 0;
}