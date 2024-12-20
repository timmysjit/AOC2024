#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;

void recurse(string& arrangement, int i, unordered_map<string, int>& umap, bool & valid){
    if (valid)
        return;
    if (i == arrangement.length()){
        valid = true;
        return;
    }

    for (int j = i; j < arrangement.length(); j++){
        if (umap[arrangement.substr(i, j- i +1)])
            recurse(arrangement, j+1, umap, valid);
    }
}

int towelSort(){

    ifstream file ("./input");
    string line;
    vector<string> arrangements;
    unordered_map<string, int> towels;
    bool flag = true;
    while (getline(file, line)){
        if (line.empty())
            continue;
        if (flag){
            flag = false;
            stringstream ss (line);
            string towel;
            while (getline(ss, towel, ',')){
                if (towel[0] == ' ')
                    towels[towel.substr(1, towel.length()-1)]=1;
                else
                    towels[towel] = 1;
            }
        } else{
            arrangements.push_back(line);
        }
    }
    int ans = 0;

    for (int i = 0; i < arrangements.size(); i++){
        string arrangement = arrangements[i];
        bool valid = false;
        recurse(arrangement, 0, towels, valid);
        if (valid)
            ans++;
    }

    return ans;
}

int main(){
    int towel_sort = towelSort();
    cout << towel_sort;
    return 0;
}