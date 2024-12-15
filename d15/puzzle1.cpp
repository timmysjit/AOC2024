#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

int lanternFish(){

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
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (map[i][j] == '@'){
                robot.first = i;
                robot.second = j;
                break;
            }
        }
        if (robot.first >= 0)
            break;
    }

    for ( char move : moves){
        int y = robot.first;
        int x = robot.second;
        if (move == '^'){
            if (map[y-1][x] == '.'){
                map[y][x] = '.';
                robot.first -=1;
                map[y-1][x] = '@';
            } else if (map[y-1][x] == 'O'){
                int i = y-1;
                int j = x;
                while (map[i][j] == 'O'){
                    i -=1;
                }

                if (map[i][j] == '.'){
                    map[i][j] = 'O';
                    map[y][x] = '.';
                    map[y-1][x] = '@';
                    robot.first -=1;
                }
            }
        } else if (move == 'v'){
            if (map[y+1][x] == '.'){
                map[y][x] = '.';
                robot.first +=1;
                map[y+1][x] = '@';
            } else if (map[y+1][x] == 'O'){
                int i = y+1;
                int j = x;
                while (map[i][j] == 'O'){
                    i +=1;
                }

                if (map[i][j] == '.'){
                    map[i][j] = 'O';
                    map[y][x] = '.';
                    map[y+1][x] = '@';
                    robot.first +=1;
                }
            }
        } else if (move == '<'){
            if (map[y][x-1] == '.'){
                map[y][x] = '.';
                robot.second -=1;
                map[y][x-1] = '@';
            } else if (map[y][x-1] == 'O'){
                int i = y;
                int j = x-1;
                while (map[i][j] == 'O'){
                    j -=1;
                }

                if (map[i][j] == '.'){
                    map[i][j] = 'O';
                    map[y][x] = '.';
                    map[y][x-1] = '@';
                    robot.second -=1;
                }
            }
        }else{
            if (map[y][x+1] == '.'){
                map[y][x] = '.';
                robot.second ++;
                map[y][x+1] = '@';
            } else if (map[y][x+1] == 'O'){
                int i = y;int j = x+1;
                while (map[i][j] == 'O'){
                    j +=1;
                }
                if (map[i][j] == '.'){
                    map[i][j] = 'O';
                    map[y][x] = '.';
                    map[y][x+1] = '@';
                    robot.second ++;
                }
            }
        }
    }

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (map[i][j] == 'O'){
                ans += 100*i + j;
            }
        }
    }

    return ans;
}

int main(){
    int lantern_fish = lanternFish();
    cout << lantern_fish;
    return 0;
}