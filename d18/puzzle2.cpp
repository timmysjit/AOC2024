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

pair<int,int> ramRun2(){

    ifstream file ("./input");
    string line;
    vector<vector<int>> map (71, vector<int> (71, 1));
    string moves = "";
    int count = 0;
    queue<pair<int,int>> q;
    while (getline(file, line)){
        if (line.empty())
            continue;
        
        size_t colon_pos= line.find(',');
        int num1 = stoi(line.substr(0, colon_pos));
        int num2 = stoi(line.substr(colon_pos+1, line.length() - colon_pos-1));
        if (count >= 1024){
            q.push({num1,num2});
            continue;
        }
        map[num1][num2] = 0;
        count++;  
    }
    count = 0;
    while (!q.empty()){
        cout << count++ << endl;
        int i = q.front().first;
        int j = q.front().second;
        map[i][j] =0;

        if (dijkstra(map)== INT_MAX)
            return q.front();
        map[i][j] =1;
        q.pop();
    }
    return {-1,-1};
}

int main(){
    pair<int,int> ram_run2 = ramRun2();
    cout << ram_run2.first << " " <<ram_run2.second;
    return 0;
}