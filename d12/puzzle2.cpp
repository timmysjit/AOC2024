#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <utility>
using namespace std;

vector<vector<int>> covered;
void propagate(char plant, int& area, int i, int j, int& label, vector<vector<int>> & label_map, vector<string> & map, int& corners){
    label_map[i][j] = label;
    area++;
    int adj[4] = {0};
    if ( i > 0 && map[i-1][j] == plant){
        if (label_map[i-1][j] < 0){
            propagate(plant, area, i-1, j, label, label_map, map, corners);
        }   
    }else{
        adj[0] =1;
    }

    if ( i < map.size()-1 && map[i+1][j] == plant){
        if (label_map[i+1][j] < 0){
            propagate(plant, area, i+1, j, label, label_map, map, corners);
        }        
    } else{
        adj[2] =1;
    }

    if ( j > 0 && map[i][j-1] == plant){
        if (label_map[i][j-1] < 0){
            propagate(plant, area, i, j-1, label, label_map, map, corners);
        }
    } else{
        adj[3]=1;
    }

    if ( j < map[0].size()-1 && map[i][j+1] == plant){
        if (label_map[i][j+1] < 0){
            propagate(plant, area, i, j+1, label, label_map, map, corners);
        }   
    } else{
        adj[1]=1;
    }

    int sum = adj[1] +adj[0] +adj[2] + adj[3];
    covered[i][j] =1;
    if (plant == 'J'){
        cout << i << " " << j << " " << sum << " " <<corners << endl;
    }
    if (sum == 3){
        corners += 2;
        if (adj[0] == 0){
            if (i >0 && j >0 && map[i-1][j-1] == plant && covered[i-1][j-1] == 0)
                corners++;
            if (i >0 && j < map[0].size()-1 && map[i-1][j+1] == plant && covered[i-1][j+1] == 0)
                corners++;
        }
        else if (adj[1] == 0){
            if (i >0 && j <map[0].size()-1 && map[i-1][j+1] == plant && covered[i-1][j+1] == 0)
                corners++;
            if (i < map.size()-1 && j < map[0].size()-1 && map[i+1][j+1] == plant && covered[i+1][j+1] == 0)
                corners++;
        } else if (adj[2] == 0){
            if (i < map.size()-1 && j > 0 && map[i+1][j-1] == plant && covered[i+1][j-1] == 0)
                corners++;
            if (i < map.size()-1 && j < map[0].size()-1 && map[i+1][j+1] == plant && covered[i+1][j+1] == 0)
                corners++;
        } else if (adj[3] == 0){
            if (i >0 && j >0 && map[i-1][j-1] == plant && covered[i-1][j-1] == 0)
                corners++;
            if (i < map.size()-1 && j >0 && map[i+1][j-1] == plant && covered[i+1][j-1] == 0)
                corners++;
        }
        return;
    } else if (sum == 2){
        if (!(adj[0] && adj[2])&& !(adj[1] && adj[3])){
            corners++;
        }
        if ((adj[0] == 0 && adj[1] == 0)|| (adj[2] == 0 && adj[3] == 0)){
            if (i >0 && j >0 && map[i-1][j-1] == plant && covered[i-1][j-1] == 0)
                corners++;
            if (i < map.size()-1 && j < map[0].size()-1 && map[i+1][j+1] == plant && covered[i+1][j+1] == 0)
                corners++;

            return;
        }
        if ((adj[1] == 0 && adj[2] == 0)||(adj[3] == 0 && adj[0] == 0)){
            if (i < map.size()-1 && j > 0 && map[i+1][j-1] == plant && covered[i+1][j-1] == 0)
                corners++;
            if (i >0 && j <map[0].size()-1 && map[i-1][j+1] == plant && covered[i-1][j+1] == 0)
                corners++;
            return;
        }
    } else if (sum == 4){
        corners = 4;
        return;
    }

    if (adj[0] == 1){
        if (i >0 && j >0 && map[i-1][j-1] == plant && covered[i-1][j-1] == 0)
            corners++;
        if (i >0 && j < map[0].size()-1 && map[i-1][j+1] == plant && covered[i-1][j+1] == 0)
            corners++;
    }

    if (adj[1] == 1){
        if (i < map.size()-1 && j < map[0].size()-1 && map[i+1][j+1] == plant && covered[i+1][j+1] == 0)
            corners++;
        if (i >0 && j < map[0].size()-1 && map[i-1][j+1] == plant && covered[i-1][j+1] == 0){
            
            corners++;
        }
    }
    if (adj[2] == 1){
        if (i < map.size()-1 && j < map[0].size()-1 && map[i+1][j+1] == plant && covered[i+1][j+1] == 0)
            corners++;
        if (i < map.size()-1 && j >0 && map[i+1][j-1] == plant && covered[i+1][j-1] == 0)
            corners++;
    }
    if (adj[3] == 1){
        if (i >0 && j >0 && map[i-1][j-1] == plant && covered[i-1][j-1] == 0)
            corners++;
        if (i < map.size()-1 && j >0 && map[i+1][j-1] == plant && covered[i+1][j-1] == 0)
            corners++;
    }

}
int discountFenceCost(){
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
    covered = vector<vector<int>>(map.size(), vector<int> (map[0].length(), 0));
    int ans = 0;
    for (auto item: umap){
        char plant = item.first;
        vector<int> areas;
        vector<int> corners;
        vector<vector<int>> labelled_map (map.size(), vector<int> (map[0].size(), -1));
        for (int i = 0; i < map.size(); i++){
            for (int j = 0; j < map[i].size(); j++){
                if (map[i][j] != plant || labelled_map[i][j] >= 0)
                    continue;
                corners.push_back(0);
                areas.push_back(0);
                int label = areas.size()-1;
                propagate(plant, areas.back(), i, j, label, labelled_map, map, corners.back());

            }
        }
        for (int i = 0; i < areas.size(); i++){
            cout << plant << " " <<areas[i] << " " << corners[i] << endl;
            ans += areas[i]* corners[i];
        }
        
    }    
    return ans;
    
}

int main(){
    int discount_fence_cost = discountFenceCost();
    cout << discount_fence_cost;
    return 0;
}