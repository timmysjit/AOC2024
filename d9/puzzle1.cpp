#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;

long long checkSum(){
    ifstream file ("./input1");
    vector<int> input;
    string line;
    while (getline(file, line)){
        for (char i : line){
            input.push_back(i - 48);
        }
    }
    file.close();

    long long ans =0;
    int position = 0;
    bool free_space = false;
    int last = input.size()-1;

    int i = 0;
    while (i <= last){
        int block_length = input[i];
        long long id = i/2;
        if (!free_space){
            //if it's not a free space block
            ans += id*((block_length)*(2*position + block_length -1))/2;
            position += block_length;
        } else{
            //if it is a free space block take blocks from the back
            while (block_length > 0){
                id = last/2;
                long long last_block_length = input[last];
                if (last_block_length  >  block_length){
                    ans += id*((block_length)*(2*position + block_length -1))/2;
                    input[last] -= block_length;
                    position += block_length;
                    break;
                } else{
                    ans += id*(last_block_length*(2*position + last_block_length -1))/2;
                    block_length -= last_block_length;
                    position += last_block_length;
                    last-=2;
                }
            }
        }
        
        if (free_space)
            free_space = false;
        else
            free_space = true;
        i++;
    }
    return ans;
}

int main(){
    long long check_sum = checkSum();
    cout << check_sum;
    return 0;
}