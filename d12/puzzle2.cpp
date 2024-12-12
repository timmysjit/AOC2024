#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <utility>
using namespace std;

void propagate(char plant, int& area, int i, int j, int& label, vector<vector<int>> & label_map, vector<string> & map){
    label_map[i][j] = label;
    area++;
    if ( i > 0 && map[i-1][j] == plant){
        if (label_map[i-1][j] < 0){
            propagate(plant, area, i-1, j, label, label_map, map);
        }        
    }
    if ( i < map.size()-1 && map[i+1][j] == plant){
        if (label_map[i+1][j] < 0){
            propagate(plant, area, i+1, j, label, label_map, map);
        }        
    }
    if ( j > 0 && map[i][j-1] == plant){
        if (label_map[i][j-1] < 0){
            propagate(plant, area, i, j-1, label, label_map, map);
        }        
    }
    if ( j < map[0].size()-1 && map[i][j+1] == plant){
        if (label_map[i][j+1] < 0){
            propagate(plant, area, i, j+1, label, label_map, map);
        }        
    }
}

pair<int, int> nc(int i, int j, int dir){
    if (dir == 0)
        return {i, j+1};
    else if (dir == 1)
        return {i+1, j};
    else if (dir == 2)
        return {i, j-1};
    else
        return {i-1, j}; 
}

void checkSides(vector<vector<int>>& labelled_map, int i, int j, int&sides, int dir, int starti, int startj, int label){
    //0: right 1: down 2:left 3: up
    cout << i << " " << j << " " << dir << endl;
    if (i == starti && j == startj)
        return;

    int m = labelled_map.size();
    int n = labelled_map[0].size();
    pair<int,int> c = nc(i, j, dir);
    pair<int, int>c2 = nc(c.first, c.second, (dir+1)%4);

    pair<int, int>c3 = nc(i, j, (dir+3)%4);
    pair<int, int>c4 = nc(c3.first, c3.second, dir%4);

    if (c.first >= 0 && c.second >= 0 && c.first < m && c.second < n && labelled_map[c.first][c.second] == label){
        if (c4.first >= 0 && c4.second >= 0 && c4.first < m && c4.second < n && labelled_map[c4.first][c4.second] == label){
            sides +=1;
            checkSides(labelled_map, c3.first, c3.second, sides, (dir+3)%4, starti, startj, label);
        } else{
            sides +=2;
            checkSides(labelled_map, c4.first, c4.second, sides, dir%4, starti, startj, label);
        }
    } else{
        if (c2.first >= 0 && c2.second >= 0 && c2.first < m && c2.second < n && labelled_map[c2.first][c2.second] ==label){
            checkSides(labelled_map, c.first, c.second, sides, dir%4, starti, startj, label);
        } else{
            sides +=1;
            checkSides(labelled_map, c2.first, c2.second, sides, (dir+1)%4, starti, startj, label);
        }
    }
}

int discountFenceCost(){
    unordered_map<char,int> umap;
    ifstream file ("./i");
    string line;
    vector<string> map;
    while (getline(file, line)){
        map.push_back(line);
        for (char i: line){
            umap[i]++;
        }
    }
    file.close();
    int ans = 0;
    for (auto item: umap){
        char plant = item.first;
        vector<int> areas;
        vector<int> sides;
        vector<vector<int>> labelled_map (map.size(), vector<int> (map[0].size(), -1));
        for (int i = 0; i < map.size(); i++){
            for (int j = 0; j < map[i].size(); j++){
                if (map[i][j] != plant || labelled_map[i][j] >= 0)
                    continue;
                cout << map[i][j] << endl;
                sides.push_back(1);
                areas.push_back(0);
                int label = areas.size()-1;
                propagate(plant, areas.back(), i, j, label, labelled_map, map);

                checkSides(labelled_map, i-1, j, sides.back(), 0, i, j-1, label);
            }
        }
        for (int i = 0; i < areas.size(); i++){
            ans += areas[i]* sides[i];
        }
        
    }    
    return ans;
    
}

int main(){
    int discount_fence_cost = discountFenceCost();
    cout << discount_fence_cost;
    return 0;
}