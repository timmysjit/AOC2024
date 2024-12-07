#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <fstream>


using namespace std;

void recurse(vector<long long> & operands, bool& ans, long long& test_value, long long& cur, int index){
    if (index == operands.size() && cur == test_value){
        ans = true;
        return;
    }
    if (ans || index == operands.size())
        return;

    // if (test_value%operands[index] == 0){
    //     test_value /= operands[index];
    //     recurse(operands, ans, test_value, cur, index+1);
    //     test_value *= operands[index];

    //     test_value -= operands[index];
    //     recurse(operands, ans, test_value, index-1);
    //     test_value += operands[index];
    // } else{
    //     test_value -= operands[index];
    //     recurse(operands, ans, test_value,index-1);
    //     test_value += operands[index];
    // }

    cur *= operands[index];
    recurse(operands, ans, test_value, cur, index+1);
    cur /= operands[index];

    cur += operands[index];
    recurse(operands, ans, test_value, cur, index+1);
    cur -= operands[index];
}

long long bridgeRepair(){
    ifstream file ("./input1");

    string line;
    vector<long long> test_values;
    vector<vector<long long>> operands;
    while (getline(file, line)){
        stringstream ss(line);
        string num;
        operands.push_back({});
        while (getline(ss, num, ' ')) {
            if (num[num.length()-1] == ':'){
                num.pop_back();
                test_values.push_back(stoll(num));
            }else{
                operands.back().push_back(stoll(num));
            }
        }
    }
    file.close();
    long long ans = 0;

    for (int i = 0; i < test_values.size(); i++){
        bool curr = false;

        int index = 1;
        long long test_value = operands[i][0];
        recurse(operands[i], curr, test_values[i], test_value, index);
        if (curr){
            ans += test_values[i];
        }
    }
    return ans;
}

int main(){
    long long bridge_repair = bridgeRepair();
    cout << bridge_repair;
    return 0;
}