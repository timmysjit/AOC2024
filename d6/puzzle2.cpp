#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <fstream>
#include <unordered_map>

using namespace std;

int placeObstacle(){
    // input parsing
    ifstream file("./input2");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }
    string line;
    vector<string> map;
    while (getline(file, line)){
        map.push_back(line);
    }
    file.close();


    //solution starts here:
    int ans = 0;
    int m = map.size(), n = map[0].length();

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


    vector<vector<int>> obstacles;
    while (i >= 0 && i < m && j >= 0 && j < n){
        if (visited[i][j] == 0){
            visited[i][j] = 1;
        }
        while (i + directions[dir].first >= 0 && i + directions[dir].first < m && j + directions[dir].second >= 0 && j + directions[dir].second < n && visited[i + directions[dir].first][j + directions[dir].second] == 2){
            obstacles.push_back({i + directions[dir].first, j + directions[dir].second, dir});
            dir = (dir+1)%4;
        }
        i += directions[dir].first;
        j += directions[dir].second;
    }

    for (int i = 0; i < obstacles.size() -1; i++){
        for (int j = i+1; j < obstacles.size(); j++){
            if (obstacles[i][2] == 0 && obstacles[j][2] != 2)
                continue;
            if (obstacles[i][2] == 1 && obstacles[j][2] != 3)
                continue;
            if (obstacles[i][2] == 2 && obstacles[j][2] != 0)
                continue;
            if (obstacles[i][2] == 3 && obstacles[j][2] != 1)
                continue;
            
            int greater_col = obstacles[i][1] > obstacles[j][1] ? i : j;
            int greater_row = obstacles[i][0] > obstacles[j][0] ? i : j;

            if (greater_col == greater_row){
                int temp = greater_col == i ? j : i;
                
                if (obstacles[greater_col][2] == 1){
                    if (obstacles[temp][0] > 0){
                        if (visited[obstacles[temp][0]-1][obstacles[greater_col][1]-1] == 2)
                            ans++;
                    }
                    if (obstacles[greater_col][0] < m-1){
                        if (visited[obstacles[greater_col][0]+1][obstacles[temp][1]+1] == 2)
                            ans++;
                    }

                } else if (obstacles[greater_col][2] == 2){
                    if (obstacles[greater_col][1] < n-1){
                        if (visited[obstacles[temp][0]+1][obstacles[greater_col][1]+1] == 2)
                            ans++;
                    }
                    if (obstacles[temp][1] > 0){
                        if (visited[obstacles[greater_col][0]-1][obstacles[temp][1]-1] == 2)
                            ans++;
                    }
                }
            } else{
                
                if (obstacles[greater_col][2] == 1){
                    if (obstacles[greater_col][0] > 0){
                        if (visited[obstacles[greater_col][0]-1][obstacles[greater_row][1]+1] == 2)
                            ans++;
                    }
                    if (obstacles[greater_row][0] < m-1){
                        if (visited[obstacles[greater_row][0]+1][obstacles[greater_col][1]-1] == 2)
                            ans++;
                    }

                } else if (obstacles[greater_col][2] == 0){
                    if (obstacles[greater_row][1] > 0){
                        if (visited[obstacles[greater_col][0]+1][obstacles[greater_row][1]-1] == 2)
                            ans++;
                    }
                    if (obstacles[greater_row][1] < n-1){
                        if (visited[obstacles[greater_row][0]-1][obstacles[greater_col][1]+1] == 2)
                            ans++;
                    }
                }
            }
            
        }
    }

    return ans;
}

int placeObstacle2(){
    // input parsing
    ifstream file("./input2");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }
    string line;
    vector<string> map;
    while (getline(file, line)){
        map.push_back(line);
    }
    file.close();


    //solution starts here:
    int ans = 0;
    int m = map.size(), n = map[0].length();

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
   
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    unordered_map<string, int> umap;

    for (int k = 0; k < m; k++){
        for (int l = 0; l < n; l++){
            if (visited[k][l] == 2 || (start.first == k && start.second == l))
                continue;
            visited[k][l]=2;


            int dir = 0;
            int i = start.first;
            int j = start.second;
            bool loop = false;
            while (i >= 0 && i < m && j >= 0 && j < n){
                
                while (i + directions[dir].first >= 0 && i + directions[dir].first < m && j + directions[dir].second >= 0 && j + directions[dir].second < n && visited[i + directions[dir].first][j + directions[dir].second] == 2){
                    string encoded = to_string(i) + to_string(j) + to_string(dir);
                    if (umap[encoded]){
                        ans++;
                        loop = true;
                        break;
                    } else{
                        umap[encoded] = 1;
                    }
                    dir = (dir+1)%4;
                }
                if (loop)
                    break;
                i += directions[dir].first;
                j += directions[dir].second;
            }

            umap.clear();
            visited[k][l] = 0;
        }
    }

    

            

    return ans;
}


                
int main(){
    int place_obstacle = placeObstacle2();
    cout << place_obstacle;
    return 0;
}