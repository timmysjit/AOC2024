#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

int checkUpdate(){
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
    bool invalid;
    for (int i = 0; i < updates.size(); i++){
        invalid = false;
        for (int j = 0; j < updates[i].size(); j++){
            set<int> dependents = rules[updates[i][j]];
            for (int k = 0; k < j; k++){
                if (dependents.find(updates[i][k]) != dependents.end()){
                    invalid = true;
                    break;
                }
            }
            if (invalid)
                break;
        }
        if (!invalid)
            ans+= updates[i][updates[i].size()/2];
    }    

    return ans;
}

int main(){
    int check_update = checkUpdate();
    cout << check_update;
    return 0;
}