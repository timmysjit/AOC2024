#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

string lanPartyPassWord(){

    ifstream file ("./input");
    string line;
    map<string, map<string,int>> lan;
    while (getline(file, line)){
        if (line.empty())
            continue;
        string part1 = line.substr(0, 2);
        string part2 = line.substr(3, 2);
        lan[part1][part2] = 1;
        lan[part2][part1] = 1;
    }
    
    set<set<string>> subsets;
    for(auto it : lan){
        map<string, int> covered;
         for (auto it2 : it.second){
            covered[it2.first] = 1;
            for (auto it3: it.second){
                if (covered[it3.first])
                    continue;
                if (lan[it2.first].find(it3.first) != lan[it2.first].end()){
                    set<string> s = {it.first, it2.first, it3.first};
                    subsets.insert(s);
                }
            }
        }
    }

    set<string> largest;


    while (subsets.size() > 0){
        largest = *subsets.begin();
        cout << largest.size() << endl;
        set<set<string>> new_subsets;
        cout << subsets.size() << endl;
        for (auto subset : subsets){
            for (auto it : lan){
                //check if the computer connects to all the computers in the subset
                bool valid = true;
                for (auto s : subset){
                    if (lan[it.first].find(s) == lan[it.first].end()){
                        valid = false;
                        break;
                    }
                }
                if (valid){
                    set<string> temp = subset;
                    temp.insert(it.first);
                    new_subsets.insert(temp);
                }
            }
        }
        subsets = new_subsets;
    }
    vector<string> ans (largest.begin(), largest.end());
    sort(ans.begin(), ans.end());
    string d = ans[0];
    for (int i = 1; i < ans.size(); i++){
        d += ',';
        d += ans[i];
    }
    for (auto subset : subsets){
        for (string s : subset){
            cout << s << " " ;
        }cout << endl;
    }
    return d;

}

int main(){
    string lan_party_password = lanPartyPassWord();
    cout << lan_party_password;
    return 0; 
}