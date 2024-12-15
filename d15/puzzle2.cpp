#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

bool push(vector<char> row, vector<vector<char>>& map, int left, int right, int row_num, int dir){
    int new_left = -1;
    int new_right = -1;
    vector<char> next_row = map[row_num+ dir];
    for (int i = left; i < right; i++){
        if (row[i] == '['){
            if (map[row_num+dir][i] == '#' || map[row_num+dir][i+1] == '#')
                return false;
            map[row_num+dir][i] = '[';
            map[row_num+dir][i+1] = ']';
            if (map[row_num+dir][i-1] == '[')
                map[row_num+dir][i-1] = '.';
            if (map[row_num+dir][i+2] == ']')
                map[row_num+dir][i+2] = '.';
            i++;
        } else if (row[i] == '.' && row[i+1] == '.'){
            if (map[row_num+dir][i] == '#' && map[row_num+dir][i+1] == '#'){
                next_row[i] = '.';
                next_row[i+1] = '.';
            } else if (map[row_num+dir][i] == '[' && map[row_num+dir][i+1] == ']'){
                next_row[i] = '.';
                next_row[i+1] = '.';
            }
            i++;
        }
    }

    for (int i = left -1; i<= right; i++){
        if (next_row[i] == '#')
            continue;
        else if (next_row[i] == '['){
            if (new_left <0)
                new_left = i;
            new_right = i+1;
            i++;
        }
        
    }

    if (new_left <0)
        return true;
    else
        return push(next_row, map, new_left, new_right, row_num+dir, dir);
}

int num_box(vector<vector<char>>& map){
    int ans = 0;
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[0].size(); j++){
            if (map[i][j] == '[')
                ans++;
        }
    }
    return ans;
}

int lanternFish2(){

    ifstream file ("./input");
    string line;
    vector<string> map;
    string moves = "";
    while (getline(file, line)){
        if (line.empty())
            continue;
        if (line[0] == '#')
            map.push_back(line);
        else
            moves += line;
        
    }
    int ans = 0;

    int m = map.size();
    int n = map[0].length();
    pair<int,int> robot = {-1,-1};

    vector<vector<char>> newmap (m, vector<char> (n*2, '.'));

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (map[i][j] == '.')
                continue;
            else if (map[i][j] == '@'){
                robot.first = i;
                robot.second = 2*j;
                newmap[i][2*j] = '@';
            } else if (map[i][j] == 'O'){
                newmap[i][2*j] = '[';
                newmap[i][2*j +1] = ']';
            } else{
                newmap[i][2*j] = '#';
                newmap[i][2*j +1] = '#';
            }
        }
    }
    vector<vector<char>> map2;
    for (char move : moves){
        int y = robot.first;
        int x = robot.second;
        map2 = newmap;
        if (move == '^'){
            if (newmap[y-1][x] == '['){
                vector<char> row = map2[y-1];
                map2[y-1][x] = '@';
                map2[y-1][x+1] = '.';
                map2[y][x] = '.';
                if (push(row, map2, x, x+1, y-1, -1)){
                    newmap = map2;
                    robot.first--;
                }
            }
            else if (newmap[y-1][x] == ']'){
                vector<char> row = map2[y-1];
                map2[y-1][x-1] = '.';
                map2[y-1][x] = '@';
                map2[y][x] = '.';
                if (push(row, map2, x-1, x, y-1, -1)){
                    newmap = map2;
                    robot.first--;
                }
            } else if (newmap[y-1][x] == '.'){
                newmap[y][x] = '.';
                robot.first --;
                newmap[y-1][x] = '@';
            }
        } else if (move == 'v'){
            if (newmap[y+1][x] == '['){
                vector<char> row = map2[y+1];
                map2[y+1][x] = '@';
                map2[y+1][x+1] = '.';
                map2[y][x] = '.';
                if (push(row, map2, x, x+1, y+1, 1)){
                    newmap = map2;
                    robot.first++;
                }
            }
            else if (newmap[y+1][x] == ']'){
                vector<char> row = map2[y+1];
                map2[y+1][x-1] = '.';
                map2[y+1][x] = '@';
                map2[y][x] = '.';
                if (push(row, map2, x-1, x, y+1, 1)){
                    newmap = map2;
                    robot.first++;
                }
            } else if (newmap[y+1][x] == '.'){
                newmap[y][x] = '.';
                robot.first++;
                newmap[y+1][x] = '@';
            }
        } else if (move == '<'){
            if (newmap[y][x-1] == '.'){
                newmap[y][x] = '.';
                robot.second -=1;
                newmap[y][x-1] = '@';
            } else if (newmap[y][x-1] == ']'){
                int i = y;
                int j = x-1;
                char prev = '@';
                map2[y][x] = '.';
                while (map2[i][j] == ']' || map2[i][j] == '['){
                    char temp = map2[i][j];
                    map2[i][j] = prev;
                    prev= temp;
                    j--;
                }
                
                if (map2[i][j] == '.'){
                    map2[i][j] = prev;
                    newmap = map2;
                    robot.second--;
                }
            }
        }else{
            if (newmap[y][x+1] == '.'){
                newmap[y][x] = '.';
                robot.second +=1;
                newmap[y][x+1] = '@';
            } else if (newmap[y][x+1] == '['){
                int i = y;
                int j = x+1;
                char prev = '@';
                map2[y][x] = '.';
                while (map2[i][j] == ']' || map2[i][j] == '['){
                    char temp = map2[i][j];
                    map2[i][j] = prev;
                    prev= temp;
                    j++;
                }
                if (map2[i][j] == '.'){
                    map2[i][j] = prev;
                    newmap = map2;
                    robot.second++;
                }
            }
        }
    }
    for (int i = 0; i < newmap.size(); i++){
        for (int j = 0; j < newmap[0].size(); j++){
            cout << newmap[i][j];
            if (newmap[i][j] == '['){
                ans += 100*i + j;
                
            }
        }
        cout << endl;
    }

    return ans;
}

int main(){
    int lantern_fish2 = lanternFish2();
    cout << lantern_fish2;
    return 0;
}