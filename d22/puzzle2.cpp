#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

long long operation(long long secret){
    long long temp = secret * 64;
    secret = temp ^ secret;
    secret %= 16777216;

    temp = secret/32;
    secret = temp ^ secret;
    secret %= 16777216;

    temp = secret * 2048;
    secret = temp ^ secret;
    secret %= 16777216;
    return secret;
}

string encode(deque<long long> arr){
    string d = to_string(arr[0]);
    for (int i = 1; i < arr.size();i++){
        d += ',';
        d += to_string(arr[i]);
    }
    return d;
}

long long monkeyMarket2(){

    ifstream file ("./input");
    string line;
    vector<long long> buyers;
    while (getline(file, line)){
        if (line.empty())
            continue;
        buyers.push_back(stoll(line));  
    }

    unordered_map<string,long long> p;
    for (int j = 0; j< buyers.size(); j++){
        cout << j << endl;
        deque<long long> seq;
        unordered_map<string,long long> prices;
        for (int i = 0; i < 2000; i++){
            long long temp = (buyers[j]+10)%10;
            // cout << temp << endl;
            buyers[j] = operation(buyers[j]);
            if (seq.size() < 4){
                seq.push_back((buyers[j]+10)%10 - temp);
            } else{
                seq.pop_front();
                seq.push_back((buyers[j]+10)%10 - temp);
            }
            if (seq.size() == 4){
                string s = encode(seq);
                if (prices[s] == 0)
                    prices[s] = (buyers[j]+ 10)%10;
            }
        }
        for (auto it : prices){
            p[it.first] += it.second;
        }
    }
    long long ans = 0;
    for (auto it : p){
        ans = max(ans, it.second);
    }
    return ans;

}

int main(){
    long long monkey_market2 = monkeyMarket2();
    cout << monkey_market2;
    return 0; 
}