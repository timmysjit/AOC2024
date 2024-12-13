#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <cmath>
using namespace std;

#define threshold 0.0000000001



int clawMachine(){
    vector<pair<int, int>> buttonA;
    vector<pair<int, int>> buttonB;
    vector<pair<int, int>> prize;
    ifstream file ("./input");
    string line;
    while (getline(file, line)){
        if (line.empty())
            continue;
        size_t colon_pos = line.find(':');
        size_t y_pos = line.find('Y');
        size_t x_pos = line.find('X');
        size_t comma_pos = line.find(',');
        char button = line[colon_pos-1];

        if (button == 'e')
            prize.push_back({stoi(line.substr(x_pos+2, comma_pos - x_pos -2)), stoi(line.substr(y_pos+2, line.length() - y_pos -2))});
        else if (button == 'A')
            buttonA.push_back({stoi(line.substr(x_pos+2, comma_pos - x_pos -2)), stoi(line.substr(y_pos+2, line.length() - y_pos -2))});
        else
            buttonB.push_back({stoi(line.substr(x_pos+2, comma_pos - x_pos -2)), stoi(line.substr(y_pos+2, line.length() - y_pos -2))});
    }
    file.close();
    int n = prize.size();
    // for (int i = 0; i < n; i++){
    //     cout << buttonA[i].first << " " << buttonA[i].second << endl;
    //     cout << buttonB[i].first << " " << buttonB[i].second << endl;
    //     cout << prize[i].first << " " << prize[i].second << endl;
    // }
    
    int ans = 0;
    for (int i = 0; i < n; i++){
        pair<int,int> A = buttonA[i]; pair<int,int> B = buttonB[i]; pair<int,int> P = prize[i];

        double quotient = static_cast<double>(A.second)/A.first;
        
        double y = (quotient*P.first - P.second)/(quotient*B.first - B.second);

        double x = (P.first - B.first*y)/A.first;

        if (x < 0 || y < 0 || (abs(x - round(x)) > threshold) || (abs(y - round(y)) > threshold))
            continue;
        ans += (3*x + y);
        cout << x << " " << y << " " << ans <<endl;
    }
    return ans;
    
}

int main(){
    int claw_machine = clawMachine();
    cout << claw_machine;
    return 0;
}