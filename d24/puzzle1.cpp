#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

long long crossedWires(){

    ifstream file ("./input");
    string line;
    map<string, int> variables;
    queue<vector<string>> q;
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
        }
    }

    while (!q.empty()){
        vector<string> f = q.front();
        q.pop();
        // cout << f[0] << " " << f[1] << " " << f[2] << " " << f[3]<<endl;
        if (variables.find(f[0]) == variables.end() || variables.find(f[2]) == variables.end()){
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
    string bitstr = "";
    for (int i = 45; i >=0; i--){
        string s = "z";
        if (i/10 == 0)
            s += '0';
        s += to_string(i);
        cout << s << endl;
        bitstr += (variables[s] + '0');
    }
    cout << bitstr << endl;
    long long ans= stoll(bitstr, nullptr, 2);

    return ans;

}

int main(){
    long long crossed_wires = crossedWires();
    cout << crossed_wires;
    return 0; 
}