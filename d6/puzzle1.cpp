#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

int guardCoverage(){
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
    while (i >= 0 && i < m && j >= 0 && j < n){
        if (visited[i][j] == 0){
            ans++;
            visited[i][j] = 1;
        }

        while (visited[i + directions[dir].first][j + directions[dir].second] == 2){
            dir = (dir+1)%4;
        }
        i += directions[dir].first;
        j += directions[dir].second;
    }

    return ans;
}

int main(){
    int guard_coverage = guardCoverage();
    cout << guard_coverage;
    return 0;
}