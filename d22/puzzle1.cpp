#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

long long monkeyMarket(){

    ifstream file ("./input");
    string line;
    vector<long long> buyers;
    while (getline(file, line)){
        if (line.empty())
            continue;
        buyers.push_back(stoll(line));  
    }

    for (int i = 0; i < 2000; i++){
        for (int j = 0; j< buyers.size(); j++){
            buyers[j] = operation(buyers[j]);
        }
    }
    long long ans = 0;
    for (long long it : buyers){
        ans += it;
    }
    return ans;

}

int main(){
    long long monkey_market = monkeyMarket();
    cout << monkey_market;
    return 0; 
}