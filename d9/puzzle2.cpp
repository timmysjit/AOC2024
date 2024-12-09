#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;

long long checkSum2(){
    ifstream file ("./input2");
    vector<int> input;
    vector<int> free_space;
    string line;
    while (getline(file, line)){
        for (int i = 0; i < line.length(); i++){
            input.push_back(line[i] - 48);
            free_space.push_back(i%2);
        }
    }
    file.close();

    long long ans =0;
    int position = 0;
    int last = input.size()-1;

    int i = 0;
    while (i <= last){
        int block_length = input[i];
        long long id = i/2;
        if (free_space[i] == 0){
            //if it's not a free space block
            ans += id*((block_length)*(2*position + block_length -1))/2;
            position += block_length;
        } else{
            //if it is a free space block take blocks from the back
            int j = last;
            while (j > i && block_length > 0){
                id = j/2;
                if (free_space[j] == 0){
                    if (input[j] <= block_length){
                        ans += id*((input[j])*(2*position + input[j] -1))/2;
                        position += input[j];
                        block_length -= input[j];
                        free_space[j] = 1;
                    }
                }
                j--;
            }
            position += block_length;
        }
        i++;
        cout << ans << endl;
    }
    return ans;
}

int main(){
    long long check_sum2 = checkSum2();
    cout << check_sum2;
    return 0;
}