#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <cmath>
using namespace std;

#define threshold 0.000001
#define offset 10000000000000
// #define offset 0



long long clawMachineReviewed(){
    vector<pair<long long, long long>> buttonA;
    vector<pair<long long, long long>> buttonB;
    vector<pair<long long, long long>> prize;
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
            prize.push_back({offset+stoll(line.substr(x_pos+2, comma_pos - x_pos -2)), offset+stoll(line.substr(y_pos+2, line.length() - y_pos -2))});
        else if (button == 'A')
            buttonA.push_back({stoll(line.substr(x_pos+2, comma_pos - x_pos -2)), stoll(line.substr(y_pos+2, line.length() - y_pos -2))});
        else
            buttonB.push_back({stoll(line.substr(x_pos+2, comma_pos - x_pos -2)), stoll(line.substr(y_pos+2, line.length() - y_pos -2))});
    }
    file.close();
    int n = prize.size();
    // for (int i = 0; i < n; i++){
    //     cout << buttonA[i].first << " " << buttonA[i].second << endl;
    //     cout << buttonB[i].first << " " << buttonB[i].second << endl;
    //     cout << prize[i].first << " " << prize[i].second << endl;
    // }
    
    long long ans = 0;
    for (int i = 0; i < n; i++){
        pair<long long,long long> A = buttonA[i]; pair<long long,long long> B = buttonB[i]; pair<long long,long long> P = prize[i];

        long double quotient = static_cast<long double>(A.second)/A.first;
        
        long double y = (quotient*P.first - P.second)/(quotient*B.first - B.second);

        long double x = (P.first - B.first*y)/A.first;

        if (x < 0 || y < 0 || (abs(x - round(x)) > threshold) || (abs(y - round(y)) > threshold))
            continue;
        ans += (3*x + y);
        cout << x << " " << y << " " << ans <<endl;
    }
    return ans;
    
}

int main(){
    long long claw_machine_reviewed = clawMachineReviewed();
    cout << claw_machine_reviewed;
    return 0;
}