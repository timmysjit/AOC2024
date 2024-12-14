#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <cmath>
#include <deque>
using namespace std;

#define height 103
#define width 101
void render(vector<vector<deque<int>>>& map){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (map[i][j].empty())
                cout << ' ';
            else
                cout << '0';
        }
        cout << endl;
    }
}
int easterEgg(){
    ifstream file ("./input");
    string line;
    vector<vector<deque<int>>> map (height, vector<deque<int>> (width, deque<int> ()));
    vector<pair<int,int>> robots;
    int index = 0;
    while (getline(file, line)){
        if (line.empty())
            continue;

        size_t s_pos = line.find(' ');

        string p_string = line.substr(0, s_pos);
        string v_string = line.substr(s_pos+1, line.length()- s_pos -1);
        
        size_t c_pos_p = p_string.find(',');
        size_t c_pos_v = v_string.find(',');

        int x = stoi(p_string.substr(2, c_pos_p -2));
        int y =stoi(p_string.substr(c_pos_p+1, p_string.length() - c_pos_p -1));
        map[y][x].push_back(index++);

        int vx = stoi(v_string.substr(2, c_pos_v -2));
        int vy = stoi(v_string.substr(c_pos_v+1, v_string.length() - c_pos_v -1));
        robots.push_back({vx, vy});
    }
    
    file.close();
    // cout << "t = 0:" << endl;
    // render(map);

    for (int t = 1; t <= 100; t++){
        vector<vector<deque<int>>> newmap (height, vector<deque<int>> (width, deque<int> ()));
        
        for (int i = 0; i < height; i++){
            for (int j = 0; j < width; j++){
                deque<int> rq = map[i][j];
                while (!rq.empty()){
                    int x = j;
                    int y = i;
                    x += (robots[rq.back()].first + width);
                    x %= width;
                    y += (robots[rq.back()].second + height);
                    y %= height;

                    newmap[y][x].push_back(rq.back());
                    rq.pop_back();
                }
            }
        }
        map = newmap;
        if (t  >= 95 && t <=100){
            cout << "t = " << t << ":" << endl;
            render(map);
            cout << endl;
        }
    }

    int ans = 0;
    return ans;
}

int main(){
    int easter_egg = easterEgg();
    cout << easter_egg;
}