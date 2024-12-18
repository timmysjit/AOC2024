#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
using namespace std;

int computerOperations(){

    ifstream file ("./input");
    string line;
    int A; int B; int C;
    vector<int> instructions;
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

    // cout << A << " " << B << " " << C << endl;
    // for (int num: instructions){
    //     cout << num << " ";
    // }cout << endl;
    vector<int> mapping = {0, 1,2,3, A, B, C};
    for (int i = 0; i < instructions.size(); i+=2){
        int inst = instructions[i];

        if (inst == 0){
            int power = mapping[instructions[i+1]];
            while (power--){
                mapping[4] /=2;
            }
        } else if (inst == 1){
            int operand = instructions[i+1];
            mapping[5] = mapping[5]^operand;
        } else if (inst == 2){
            int operand = mapping[instructions[i+1]];
            mapping[5] = operand%8;
        } else if (inst == 3){
            //jump
            int operand = instructions[i+1];
            if (mapping[4] != 0){
                i = operand-2;
            }
        }else if (inst == 4){
            mapping[5] = mapping[5]^mapping[6];
        }else if (inst == 5){
            int operand = mapping[instructions[i+1]];
            cout << operand%8 << ',';
        }else if (inst == 6){
            int power = mapping[instructions[i+1]];
            mapping[5] = mapping[4];
            while (power--){
                mapping[5] /=2;
            }
        } else if (inst == 7){
            int power = mapping[instructions[i+1]];
            mapping[6] = mapping[4];
            while (power--){
                mapping[6] /=2;
            }
        }

    }



    int ans = 0;
    return ans;
}

int main(){
    int computer_operations = computerOperations();
    return 0;
}