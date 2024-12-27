#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <bitset>
#include <set>
#include <array>

#include <algorithm>

using namespace std;

void traverse(map<array<string,3>, int>& checked, int& not_tampered, map<string, array<string,3>>& mp, string cur){
    if (mp.find(cur) == mp.end()){
        return;
    }
    if (checked.find(mp[cur]) != checked.end())
        return;
    
        
    cout << mp[cur][0] << " " << mp[cur][1] << " " <<mp[cur][2] << " " << cur << endl;
    checked[mp[cur]] =1;
    not_tampered++;
    traverse(checked, not_tampered, mp, mp[cur][0]);
    traverse(checked, not_tampered, mp, mp[cur][2]);
}

bool check(queue<vector<string>> q, map<string, int> variables, string sum, map<array<string,3>, string> modification){
    int count = 0;
    while (!q.empty()){
        vector<string> f = q.front();
        q.pop();
        if (modification.find({f[0], f[1], f[2]}) != modification.end()){
            f[3] = modification[{f[0], f[1], f[2]}];
        }
        if (variables.find(f[0]) == variables.end() || variables.find(f[2]) == variables.end()){
            if (count++ > 1000)
                return false;
            q.push(f);
            continue;
        }
        if (f[1] == "OR"){
            variables[f[3]] = variables[f[0]]|variables[f[2]];
        } else if (f[1] == "AND"){
            variables[f[3]] = variables[f[0]]&variables[f[2]];
        } else{
            variables[f[3]] = variables[f[0]]^variables[f[2]];
        }
    }
    string z_bit = "";
    for (int i = 45; i >=0; i--){
        string s = "z";
        if (i/10 == 0)
            s += '0';
        s += to_string(i);
        z_bit += (variables[s] + '0');
    }
    
    
    if (sum == z_bit)
        return true;
    return false;

}

string crossedWires2(){

    ifstream file ("./input");
    string line;
    map<string, int> variables;
    queue<vector<string>> q;
    map<string, array<string,3>> mp;
    map<array<string,3>, string> mp2;
    while (getline(file, line)){
        if (line.empty())
            continue;
        if (line[3] == ':'){
            variables[line.substr(0,3)] = (line[line.length()-1] - '0');
        } else{
            size_t d_pos = line.find('-');
            string var1 = line.substr(0,3);
            string var2 = line.substr(d_pos-4, 3);
            string var3 = line.substr(line.length()-3, 3);
            string op = line.substr(4,d_pos-9);
            q.push({var1, op, var2, var3});
            mp[var3] = {var1, op, var2};
            mp2[{var1, op, var2}] = var3;
        }
    }

    string x_bit = "";
    for (int i = 44; i >=0; i--){
        string s = "x";
        if (i/10 == 0)
            s += '0';
        s += to_string(i);
        x_bit += (variables[s] + '0');
    }

    string y_bit = "";
    for (int i = 44; i >=0; i--){
        string s = "y";
        if (i/10 == 0)
            s += '0';
        s += to_string(i);
        y_bit += (variables[s] + '0');
    }

    long long x = stoll(x_bit, nullptr, 2);
    long long y = stoll(y_bit, nullptr, 2);
    string sum = bitset<46>(x+y).to_string();
    unordered_map<string, int> faults = {{"z40",1}, {"z39",1}, {"z26",1}, {"z25",1},{ "z24",1}, {"z23",1},{"z22",1}, 
            {"z21",1}, {"z20",1}, {"z10",1}, {"z07",1}, {"z06",1}};
    int ori = mp.size();
    //nbd, kbs, z06, ksv, tqq, z20, ckb, z39

    int not_tampered = 0;
    map<array<string,3>, int> checked;
    traverse(checked, not_tampered, mp, "z39");
    
    return "";

}

int main(){
    string crossed_wires2 = crossedWires2();
    cout << crossed_wires2;
    return 0; 
}