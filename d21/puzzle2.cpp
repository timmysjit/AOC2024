// 218309335714068
// 248737376587816

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string encode(unordered_map<char, pair<int,int>>& keymap, string& plaintext, int sy, int sx){
    int y = sy; int x = sx;
    string d = "";
    for (int i = 0; i < plaintext.length(); i++){
        pair<int,int> target = keymap[plaintext[i]];
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

        if (( sy == y || sy == target.first) && ( 0 == x || 0 == target.second)){
            string temp = "";
            if (y == sy){
                temp += vertical;
                temp += horizontal;
                d += temp;
            } else if (x == 0){
                temp += horizontal;
                temp += vertical;
                d += temp;
            }
        } else{
            if (horizontal.empty() || vertical.empty()){
                if (!horizontal.empty())
                    d += horizontal;
                if (!vertical.empty())
                    d += vertical;
            } else{
                
                if (target.second < x && target.first > y){
                    d += horizontal;
                    d+= vertical;
                } else if (target.second < x && target.first < y){
                    d += horizontal;
                    d+= vertical;
                } 
                else if (target.first > y){
                    d += vertical;
                    d+= horizontal;
                } else{
                    d += vertical;
                    d += horizontal;
                }
            }
            
        }
        d+= 'A';
        y = target.first;
        x = target.second;
    }
    return d;
}
vector<string> decode(string& plaintext){
    vector<string> ans;
    string temp = "";
    for (int j = 0; j < plaintext.length();j++){
        if (plaintext[j] == 'A' && (j == plaintext.length()-1 || plaintext[j+1] != 'A')){
            temp += plaintext[j];
            ans.push_back(temp);
            temp = "";
        } else{
            temp += plaintext[j];
        }
    }
    return ans;
}
long long keypadSequence2(){
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

    unordered_map<string,vector<string>> umap;
    umap["^A"] = {"<A", ">A"};
    umap["vA"] = {"<vA", "^>A"};
    umap[">A"] = {"vA", "^A"};
    umap["<A"] = {"v<<A", ">>^A"};

    umap["<vA"] = {"v<<A", ">A", "^>A"};
    umap["v<A"] = {"<vA", "<A", ">>^A"};
    umap["<^A"] = {"v<<A", ">^A", ">A"};
    umap["^<A"] = {"<A", "v<A", ">>^A"};

    umap[">vA"] = {"vA", "<A", "^>A"};
    umap["v>A"] = {"<vA", ">A", "^A"};
    umap[">^A"] = {"vA", "<^A", ">A"};
    umap["^>A"] = {"<A", "v>A", "^A"};

    vector<string> directionals;
    for (string code : codes){
        int y = 3, x = 2;
        directionals.push_back(encode(numpad, code, y, x));
    }

    vector<long long> ans;
    for (int i = 0; i < directionals.size();i++){
        unordered_map<string, long long> segments;
        string temp = "";
        for (int j = 0; j < directionals[i].length();j++){
            if (directionals[i][j] == 'A' && (j == directionals[i].length()-1 || directionals[i][j+1] != 'A')){
                temp += directionals[i][j];
                segments[temp]++;
                temp = "";
            } else{
                temp += directionals[i][j];
            }
        }

        for (int j = 0; j < 25; j++){
            unordered_map<string, long long> new_segments;
            for (auto it : segments){
                string s = it.first;
                long long count = it.second;
                if (umap[s].empty()){
                    string encoded = encode(dirpad, s, 0,2);
                    umap[s] = decode(encoded);
                }
                for (int k = 0; k < umap[s].size(); k++){
                    new_segments[umap[s][k]] += count;
                }
            }
            segments = new_segments;
        }
        ans.push_back(0);
        for (auto it : segments){
            string s = it.first;
            long long len = s.length();
            long long count = it.second;
            long long weight = len*count;
            ans.back() += weight;
        }
    }
    
    long long ans_val = 0;
    for (int i = 0; i < ans.size(); i++){
        // cout << stoi(codes[i].substr(0, codes[i].length()-1)) << " " << directionals[i].size()<<endl;
        ans_val += stoi(codes[i].substr(0, codes[i].length()-1))*ans[i];
    }
    
    return ans_val;

}
int main(){
    long long keypad_sequence2 = keypadSequence2();
    cout << keypad_sequence2;
}