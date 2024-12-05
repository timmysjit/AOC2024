#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

void sort (unordered_map<int, set<int>>& umap, vector<int>& arr){
    for (int i = 0; i < arr.size(); i++){
        for (int j = 0; j <i; j ++){
            if (umap[arr[i]].find(arr[j]) != umap[arr[i]].end()){
                int temp = arr[j];
                arr[j] = arr[i];
                for (int k = j+1; k <= i; k++){
                    int temp2 = arr[k];
                    arr[k] = temp;
                    temp = temp2;
                }
            }
        }
    }
}

bool checkUpdate(vector<int>& update, unordered_map<int, set<int>>& rules){
    bool valid = true;
    for (int j = 0; j < update.size(); j++){
        set<int> dependents = rules[update[j]];
        for (int k = 0; k < j; k++){
            if (dependents.find(update[k]) != dependents.end()){
                valid = false;
                break;
            }
        }
        if (!valid)
            break;
    }
    return valid;
}

int fixUpdate(){
    string line;
    vector<vector<int>> updates;
    unordered_map<int, set<int>> rules;
    int ans = 0;
    while (getline(cin, line)){
        if (line.empty())
            continue;
        if (line[2] == '|'){
            rules[stoi(line.substr(0, 2))].insert(stoi(line.substr(3, 2)));
        } else if (line[2] == ','){
            vector<int> update;
            stringstream ss(line);
            string num;
            while (getline(ss, num, ',')) {
                update.push_back(stoi(num));
            }
            updates.push_back(update);
        }

    }

    for (int i = 0; i < updates.size(); i++){
        if (checkUpdate(updates[i], rules))
            continue;
        sort(rules, updates[i]);
        ans += updates[i][updates[i].size()/2];
    }    

    return ans;
}

int main(){
    int fix_update = fixUpdate();
    cout << fix_update;
    return 0;
}