#include <iostream>
#include <vector>
#include <string>
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

int numStones(){
    vector<long long> stones;
    long long num;
    while (cin >> num){
        stones.push_back(num);
    }
    for (int i = 0; i < 25; i++){

        long long sz = stones.size();
        cout << i << " " <<  sz << endl;
        for (int j = 0; j < sz; j++){
            if (stones[j] == 0){
                stones[j] =1;
            }
            else if (digits(stones[j])%2 == 0){
                long long temp = stones[j];
                string str = to_string(temp);
                int str_len = str.length();
                stones[j] = stoll(str.substr(0, str_len/2));
                stones.push_back(stoll(str.substr(str_len/2, str_len/2)));
            } 
            else{
                stones[j] *= 2024;
            }
        }

    }
    int ans = stones.size();
    return ans;
}

int main(){
    int num_stones = numStones();
    cout << num_stones;
    return 0;
}