#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <queue>
using namespace std;

long long computerOperationReversed(){

    ifstream file ("./input");
    string line;
    long long A; long long B; long long C;
    vector<long long> instructions;
    while (getline(file, line)){
        if (line.empty())
            continue;
        size_t colon_pos = line.find(':');
        if (line[colon_pos-1] == 'A')
            A = stoi(line.substr(colon_pos+2, line.length()- colon_pos -2));
        if (line[colon_pos-1] == 'B')
            B = stoi(line.substr(colon_pos+2, line.length()- colon_pos -2));
        if (line[colon_pos-1] == 'C')
            C = stoi(line.substr(colon_pos+2, line.length()- colon_pos -2));
        if (line[colon_pos-1] == 'm'){
            stringstream ss(line.substr(colon_pos+2, line.length()- colon_pos -2));
            string number;
            while (getline(ss, number, ',')) {
                instructions.push_back(stoi(number));
            }
        }
    }

    long long ans = LLONG_MAX;
    long long prev = 0;
    int idx = instructions.size()-1;
    queue<pair<long long, int>> q;
    q.push({0, idx}); 
    while (!q.empty()){
        prev = q.front().first*8;
        idx = q.front().second;
        cout << prev << " " << idx << endl;
        q.pop();
        for (int i = 0; i <= 7; i++){
            
            A = prev +i;
            B = A%8;
            B ^=3;
            C = A/pow(2, B);
            if (C < 0)
                cout << " ajsd;lkfaj;ksdjf;kajsdkf" <<endl;
            B ^=5;
            A /= 8;
            B = B^C;
            
            if ((B%8) == instructions[idx]){
                if (idx == 0)
                    ans = min(ans, prev+i);
                else
                    q.push({prev+i, idx-1});
            }
        }
        cout << endl;
    }
    

    return ans;
}

int main(){
    long long computer_operation_reversed = computerOperationReversed();
    cout << computer_operation_reversed;
    return 0;
}