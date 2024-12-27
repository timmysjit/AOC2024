// #include <fstream>
// #include <iostream>
// #include <string>
// #include <vector>
// #include <unordered_map>

// using namespace std;

// int lanParty(){

//     ifstream file ("./input");
//     string line;
//     unordered_map<string, vector<string>> lan;
//     while (getline(file, line)){
//         if (line.empty())
//             continue;
//         string part1 = line.substr(0, 2);
//         string part2 = line.substr(3, 2);
//         lan[part1].push_back(part2);
//         lan[part2].push_back(part1);
//     }
//     double ans = 0;
//     for(auto it : lan){
//         if (it.first[0] != 't')
//             continue;
        
//         for (int i = 0; i < it.second.size(); i++){
//             double t_count = 1;
//             if (it.second[i][0] == 't')
//                 t_count++;
//             for (int j = i+1; j < it.second.size(); j++){
//                 if (it.second[j][0] == 't')
//                     t_count++;
//                 for (int k = 0; k < lan[it.second[i]].size(); k++){
//                     if (lan[it.second[i]][k] == it.second[j]){
//                         ans += 1/t_count;
//                         break;
//                     }
//                 }
//                 if (it.second[j][0] == 't')
//                     t_count--;
//             }
//         }
//     }
//     return static_cast<int> (ans);

// }

// int main(){
//     int lan_party = lanParty();
//     cout << lan_party;
//     return 0; 
// }

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

int lanParty(){

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
    double ans = 0;
    for(auto it : lan){
        if (it.first[0] != 't')
            continue;
        map<string, int> covered;
         for (auto it2 : it.second){
            covered[it2.first] = 1;
            double t_count = 1;
            if (it2.first[0] == 't')
                t_count++;
            for (auto it3: it.second){
                if (covered[it3.first])
                    continue;
                if (it3.first[0] == 't')
                    t_count++;

                if (lan[it2.first].find(it3.first) != lan[it2.first].end()){
                    ans += 1/t_count;
                }
                if (it3.first[0] == 't')
                    t_count--;
            }
        }
    }
    cout << ans << endl;
    return static_cast<int> (ans);

}

int main(){
    int lan_party = lanParty();
    cout << lan_party;
    return 0; 
}