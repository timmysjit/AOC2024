#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int digits (long long num){
    int ans = 0;
    while (num){
        num /= 10;
        ans++;
    }
    if (ans == 0)
        ans++;
    return ans;
}

long long numStones(){
    unordered_map<long long, long long> stones;
    long long num;
    while (cin >> num){
        stones[num]++;
    }

    for (int i = 0; i < 75; i++){
        unordered_map<long long, long long> temp;

        for (const auto& stone : stones) {
            if (stone.first == 0){
                temp[1] += stone.second;
            } else if (digits(stone.first)%2 == 0){
                string str = to_string(stone.first);
                long long part1 = stoll(str.substr(0, str.length()/2));
                long long part2 = stoll(str.substr(str.length()/2, str.length()/2));
                temp[part1] += stone.second;
                temp[part2] += stone.second;
            } else{
                temp[stone.first*2024] += stone.second;
            }
        }
        stones = temp;
    }
    long long ans = 0;
    for (auto stone : stones){
        ans+= stone.second;
    }
    return ans;
}

int main(){
    long long num_stones = numStones();
    cout << num_stones;
    return 0;
}