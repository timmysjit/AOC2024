#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void recurse(vector<string>& ans, string& cur, vector<vector<string>>& possibilities, int pos){

    if (pos >= possibilities.size()){
        ans.push_back(cur);
        return;
    }
    
    if (possibilities[pos].size() == 0){
        cur += 'A';
        recurse(ans, cur, possibilities, pos+1);
        cur = cur.substr(0, cur.length()-1);
    } else if (possibilities[pos].size() == 1){
        int sz = cur.length();
        cur += possibilities[pos][0];
        cur += 'A';
        recurse(ans, cur, possibilities, pos+1);
        cur = cur.substr(0, sz);
    } else{
        int sz = cur.length();
        cur += possibilities[pos][0];
        cur += possibilities[pos][1];
        cur += 'A';
        recurse(ans, cur, possibilities, pos+1);
        cur = cur.substr(0, sz);

        cur += possibilities[pos][1];
        cur += possibilities[pos][0];
        cur += 'A';
        recurse(ans, cur, possibilities, pos+1);
        cur = cur.substr(0, sz);
    }
}

int keypadSequence(){
    ifstream file ("./input");
    string line;
    vector<string> codes;
    while (getline(file, line))
        codes.push_back(line);
    file.close();

    unordered_map<char, pair<int,int>> numpad;
    numpad['0'] = {3,1};
    numpad['A'] = {3,2};
    numpad['1'] = {2,0};
    numpad['2'] = {2,1};
    numpad['3'] = {2,2};
    numpad['4'] = {1,0};
    numpad['5'] = {1,1};
    numpad['6'] = {1,2};
    numpad['7'] = {0,0};
    numpad['8'] = {0,1};
    numpad['9'] = {0,2};
    unordered_map<char, pair<int,int>> dirpad;
    dirpad['^'] = {0,1};
    dirpad['A'] = {0,2};
    dirpad['<'] = {1,0};
    dirpad['v'] = {1,1};
    dirpad['>'] = {1,2};

    vector<vector<string>> directional1;
    for (string code : codes){
        int y = 3, x = 2;
        vector<vector<string>> parts;
        vector<string> transcriptions;
        for (int i = 0; i < code.length(); i++){
            pair<int,int> target = numpad[code[i]];
            string vertical = "";
            if (target.first < y){
                for (int j = 0; j < (y - target.first); j++)
                    vertical += '^';
            } else{
                for (int j = 0; j < (target.first - y); j++)
                    vertical += 'v';
            }
            string horizontal = "";
            if (target.second < x){
                for (int j = 0; j < (x - target.second); j++)
                    horizontal += '<';
            } else{
                for (int j = 0; j < (target.second - x); j++)
                    horizontal += '>';
            }
            vector<string> possibilities;

            if (( 3 == y || 3 == target.first) && ( 0 == x || 0 == target.second)){
                string temp = "";
                if (y == 3){
                    temp += vertical;
                    temp += horizontal;
                    possibilities.push_back(temp);
                } else if (x == 0){
                    temp += horizontal;
                    temp += vertical;
                    possibilities.push_back(temp);
                }
            } else{
                if (!horizontal.empty())
                    possibilities.push_back(horizontal);
                if (!vertical.empty())
                    possibilities.push_back(vertical);
            }

            
            parts.push_back(possibilities);
            y = target.first;
            x = target.second;
        }
        string cur  = "";
        recurse(transcriptions, cur, parts, 0);
        directional1.push_back(transcriptions);
    }
    for (int i = 0; i < directional1.size();i++){
        cout << i << endl;
        for (string s : directional1[i]){
            cout << s <<endl;
        }
        
    }

    vector<vector<string>> directional2;

    for (auto d1 : directional1){
        directional2.push_back({});
        for (string d : d1){
            int y = 0, x = 2;
            vector<vector<string>> parts;
            for (int i = 0; i < d.length(); i++){
                pair<int,int> target = dirpad[d[i]];
                string vertical = "";
                if (target.first < y){
                    for (int j = 0; j < (y - target.first); j++)
                        vertical += '^';
                } else{
                    for (int j = 0; j < (target.first - y); j++)
                        vertical += 'v';
                }
                string horizontal = "";
                if (target.second < x){
                    for (int j = 0; j < (x - target.second); j++)
                        horizontal += '<';
                } else{
                    for (int j = 0; j < (target.second - x); j++)
                        horizontal += '>';
                }
                vector<string> possibilities;
                if (( 0 == y || 0 == target.first) && ( 0 == x || 0 == target.second)){
                    string temp = "";
                    if (y == 0){
                        temp += vertical;
                        temp += horizontal;
                        possibilities.push_back(temp);
                    } else if (x == 0){
                        temp += horizontal;
                        temp += vertical;
                        possibilities.push_back(temp);
                    }
                } else{
                    if (!horizontal.empty())
                        possibilities.push_back(horizontal);
                    if (!vertical.empty())
                        possibilities.push_back(vertical);
                }
                parts.push_back(possibilities);
                y = target.first;
                x = target.second;
            }
            string cur ="";
            recurse(directional2.back(), cur, parts, 0);
        }
    }

    vector<vector<string>> directional3;

    for (auto d2 : directional2){
        directional3.push_back({});
        for (string d : d2){
            int y = 0, x = 2;
            vector<vector<string>> parts;
            for (int i = 0; i < d.length(); i++){
                pair<int,int> target = dirpad[d[i]];
                string vertical = "";
                if (target.first < y){
                    for (int j = 0; j < (y - target.first); j++)
                        vertical += '^';
                } else{
                    for (int j = 0; j < (target.first - y); j++)
                        vertical += 'v';
                }
                string horizontal = "";
                if (target.second < x){
                    for (int j = 0; j < (x - target.second); j++)
                        horizontal += '<';
                } else{
                    for (int j = 0; j < (target.second - x); j++)
                        horizontal += '>';
                }
                vector<string> possibilities;
                if (( 0 == y || 0 == target.first) && ( 0 == x || 0 == target.second)){
                    string temp = "";
                    if (y == 0){
                        temp += vertical;
                        temp += horizontal;
                        possibilities.push_back(temp);
                    } else if (x == 0){
                        temp += horizontal;
                        temp += vertical;
                        possibilities.push_back(temp);
                    }
                } else{
                    if (!horizontal.empty())
                        possibilities.push_back(horizontal);
                    if (!vertical.empty())
                        possibilities.push_back(vertical);
                }
                parts.push_back(possibilities);
                y = target.first;
                x = target.second;
            }
            string cur ="";
            recurse(directional3.back(), cur, parts, 0);
        }
    }

    vector<int> ans_arr (codes.size(),INT_MAX);

    for (int i = 0; i< codes.size(); i++){
        cout << i << endl;
        unordered_map<int,int> umap;
        for (int j= 0; j < directional3[i].size(); j++){
            if (umap[directional3[i][j].length()] == 0){
                cout << directional3[i][j] <<endl;
                umap[directional3[i][j].length()] = 1;
            }
                
            ans_arr[i] = min(ans_arr[i], static_cast<int> (directional3[i][j].length()));
        }
    }
    
    int ans = 0;
    for (int i = 0; i < codes.size(); i++){
        cout << stoi(codes[i].substr(0, codes[i].length()-1)) << " " << ans_arr[i]<<endl;
        ans += stoi(codes[i].substr(0, codes[i].length()-1))*ans_arr[i];
    }
    
    return ans;

}
int main(){
    int keypad_sequence = keypadSequence();
    cout << keypad_sequence;
}