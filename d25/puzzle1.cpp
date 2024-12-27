#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void print(vector<int> arr){
    for (int i: arr){
        cout << i << " ";
    } cout << endl;
}
int keyLockPairs(){
    ifstream file ("./input");
    string line;
    vector<vector<int>> keys;
    vector<vector<int>> locks;
    bool key = true;
    vector<int> cur;
    while (getline(file, line)){
        
        if (line.empty()){
            if (key)
                keys.push_back(cur);
            else
                locks.push_back(cur);
            cur.clear();
            continue;
        }
        if (cur.empty()){
            if (line[0] == '#'){
                key = false;
                cur = vector<int> (line.length(), 0);
            }else{
                key = true;
                cur = vector<int> (line.length(), -1);
            }
            
        } else{
            for (int i = 0; i < line.length(); i++){
                if (line[i] == '#')
                    cur[i]++;
            }
        }
        
    }
    if (key)
        keys.push_back(cur);
    else
        locks.push_back(cur);

    file.close();
    int ans = 0;
    int n = keys[0].size();
    int m = 5;
    cout << locks.size() << " " << keys.size() << endl;
    for (vector<int> lock : locks){
        for (vector<int> key : keys){
            for (int i = 0; i < n; i++){
                if (key[i] + lock[i] > m)
                    break;
                if (i == n-1)
                    ans++;
            }
        }
    }
    return ans;
}


int main(){
    int key_lock_pairs = keyLockPairs();
    cout << key_lock_pairs;
    return 0;
}