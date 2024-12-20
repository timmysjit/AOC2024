#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <unordered_map>
using namespace std;

long long towelSort2(){

    ifstream file ("./input");
    string line;
    vector<string> arrangements;
    unordered_map<string, int> towels;
    bool flag = true;
    while (getline(file, line)){
        if (line.empty())
            continue;
        if (flag){
            flag = false;
            stringstream ss (line);
            string towel;
            while (getline(ss, towel, ',')){
                if (towel[0] == ' ')
                    towels[towel.substr(1, towel.length()-1)] = 1;
                else
                    towels[towel] = 1;
            }
        } else{
            arrangements.push_back(line);
        }
    }
    long long ans = 0;
    for (string arrangement : arrangements){
        int n = arrangement.length();
        vector<vector<long long>> dp (n, vector<long long>(n,0));
        for (int i = 0; i < n; i++){
            string temp  = "";
            temp += arrangement[i];
            if (towels[temp]){
                dp[i][i] = 1;
            }
        }
        for (int l = 2; l <= n; l++){
            for (int i = 0; i <= n - l; i++){
                int j = i+l-1;
                for (int k = j; k > i; k--){
                    if (towels[arrangement.substr(k, j - k +1)] == 0)
                        continue;
                    dp[i][j] += dp[i][k-1];
                }
                dp[i][j] += towels[arrangement.substr(i, l)];


            }
        }
        ans += dp[0][n-1];
    }
    
    return ans;
}

int main(){
    long long towel_sort2 = towelSort2();
    cout << towel_sort2;
    return 0;
}