#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
using namespace std;
int dijkstra(vector<vector<int>>& map){
    int m = map.size();
    int n = map[0].size();
    vector<vector<int>> visited (m, vector<int> (n, 0));
    vector<vector<int>> distance (m, vector<int> (n, INT_MAX));
    priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
    distance[70][70] = 0;    
    pq.push({0, 70, 70});

    while (!pq.empty()){
        vector<int> node = pq.top();
        cout << node[1] << " " << node[2] <<endl;
        pq.pop();
        if (visited[node[1]][node[2]])
            continue;
        visited[node[1]][node[2]]=1;

        if (node[1] > 0 && map[node[1]-1][node[2]] && visited[node[1]-1][node[2]] == 0){
            distance[node[1]-1][node[2]] = min(distance[node[1]-1][node[2]], 1+ node[0]);
            pq.push({distance[node[1]-1][node[2]],node[1]-1, node[2]});
        }
        if (node[1] < 70 && map[node[1]+1][node[2]] && visited[node[1]+1][node[2]] == 0){
            distance[node[1]+1][node[2]] = min(distance[node[1]+1][node[2]], 1+ node[0]);
            pq.push({distance[node[1]+1][node[2]],node[1]+1, node[2]});
        }
        if (node[2] > 0 && map[node[1]][node[2]-1] && visited[node[1]][node[2]-1] == 0){
            distance[node[1]][node[2]-1] = min(distance[node[1]][node[2]-1], 1+ node[0]);
            pq.push({distance[node[1]][node[2]-1],node[1], node[2]-1});
        }
        if (node[2] < 70 && map[node[1]][node[2]+1] && visited[node[1]][node[2]+1] == 0){
            distance[node[1]][node[2]+1] = min(distance[node[1]][node[2]+1], 1+ node[0]);
            pq.push({distance[node[1]][node[2]+1],node[1], node[2]+1});
        }
    }
    return distance[0][0];
}

int ramRun(){

    ifstream file ("./input");
    string line;
    vector<vector<int>> map (71, vector<int> (71, 1));
    string moves = "";
    int count = 0;
    while (getline(file, line)){
        if (line.empty())
            continue;
        if (count >= 1024)
            continue;
        size_t colon_pos= line.find(',');
        int num1 = stoi(line.substr(0, colon_pos));
        int num2 = stoi(line.substr(colon_pos+1, line.length() - colon_pos-1));
        map[num1][num2] = 0;
        count++;  
    }
    return dijkstra(map);
}

int main(){
    int ram_run = ramRun();
    cout << ram_run;
    return 0;
}