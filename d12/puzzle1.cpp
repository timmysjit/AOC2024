#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <utility>
using namespace std;

void propagate(char plant, int& area, int& perimeter, int i, int j, int& label, vector<vector<int>> & label_map, vector<string> & map){
    label_map[i][j] = label;
    area++;
    perimeter+=4;

    if ( i > 0 && map[i-1][j] == plant){
        perimeter--;
        if (label_map[i-1][j] < 0){
            propagate(plant, area, perimeter, i-1, j, label, label_map, map);
        }        
    }
    if ( i < map.size()-1 && map[i+1][j] == plant){
        perimeter--;
        if (label_map[i+1][j] < 0){
            propagate(plant, area, perimeter, i+1, j, label, label_map, map);
        }        
    }
    if ( j > 0 && map[i][j-1] == plant){
        perimeter--;
        if (label_map[i][j-1] < 0){
            propagate(plant, area, perimeter, i, j-1, label, label_map, map);
        }        
    }
    if ( j < map[0].size()-1 && map[i][j+1] == plant){
        perimeter--;
        if (label_map[i][j+1] < 0){
            propagate(plant, area, perimeter, i, j+1, label, label_map, map);
        }        
    }
}

int fenceCost(){
    unordered_map<char,int> umap;
    ifstream file ("./input");
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
        vector<int> perimeters;
        vector<vector<int>> labelled_map (map.size(), vector<int> (map[0].size(), -1));
        for (int i = 0; i < map.size(); i++){
            for (int j = 0; j < map[i].size(); j++){
                if (map[i][j] != plant || labelled_map[i][j] >= 0)
                    continue;
                areas.push_back(0);
                perimeters.push_back(0);
                int label = areas.size()-1;
                propagate(plant, areas.back(), perimeters.back(), i, j, label, labelled_map, map);
            }
        }
        for (int i = 0; i < areas.size(); i++){
            ans += areas[i]* perimeters[i];
        }
        
    }    
    return ans;
    
}

int main(){
    int fence_cost = fenceCost();
    cout << fence_cost;
    return 0;
}