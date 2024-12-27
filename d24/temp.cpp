#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <bitset>

using namespace std;

string crossedWires2(){

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
    string z_bit = "";
    for (int i = 45; i >=0; i--){
        string s = "z";
        if (i/10 == 0)
            s += '0';
        s += to_string(i);
        z_bit += (variables[s] + '0');
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
    cout << " " << y_bit << endl << " " << x_bit << endl << z_bit << endl << sum << endl;
    for (int i =0; i <=45; i++){
        if (sum[i] != z_bit[i]){
            cout <<i << endl;
        }
    }

    return "";

}

int main(){
    string crossed_wires2 = crossedWires2();
    cout << crossed_wires2;
    return 0; 
}