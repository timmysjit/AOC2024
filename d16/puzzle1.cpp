#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <queue>
using namespace std;


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
    return distance[1][n-2];
}

int reindeerRace(){

    ifstream file ("./i");
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