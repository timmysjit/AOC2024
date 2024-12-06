#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

int placeObstacle(){
    string line;
    vector<string> map;
    int ans = 0;

    while (getline(cin, line)){
        map.push_back(line);
    }
    int m = map.size();
    int n = map[0].length();
    vector<vector<int>> visited (m, vector<int> (n, 0));

    pair<int, int> start = {-1,-1};
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (map[i][j] == '#'){
                visited[i][j] = 2;
            } else if (map[i][j] == '^'){
                start.first = i;
                start.second = j;
            }
        }
    }
    int dir = 0;
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    int i = start.first;

    int j = start.second;
    vector<pair<int, int>> obstacles;
    while (i >= 0 && i < m && j >= 0 && j < n){
        
        while (visited[i + directions[dir].first][j + directions[dir].second] == 2){
            obstacles.push_back({i + directions[dir].first, j + directions[dir].second});
            dir = (dir+1)%4;
        }
        i += directions[dir].first;
        j += directions[dir].second;
    }

    for (int i = 0; i < obstacles.size() -1; i++){
        for (int j = i+1; j < obstacles.size(); j++){
            if (obstacles[i].second == obstacles[j].second || obstacles[i].first == obstacles[j].first)
                continue;
            
            if ()
        }
    }

    return ans;
}

int main(){
    int place_obstacle = placeObstacle();
    cout << place_obstacle;
    return 0;
}