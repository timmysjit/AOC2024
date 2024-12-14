#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <cmath>
using namespace std;

#define height 103
#define width 101

int safetyFactor(){
    ifstream file ("./input");
    string line;
    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;
    while (getline(file, line)){
        if (line.empty())
            continue;

        size_t s_pos = line.find(' ');

        string p_string = line.substr(0, s_pos);
        string v_string = line.substr(s_pos+1, line.length()- s_pos -1);
        
        size_t c_pos_p = p_string.find(',');
        size_t c_pos_v = v_string.find(',');
        int x = stoi(p_string.substr(2, c_pos_p -2))-width/2;
        int y = height/2- stoi(p_string.substr(c_pos_p+1, p_string.length() - c_pos_p -1));
        int vx = stoi(v_string.substr(2, c_pos_v -2));
        int vy = 0 -stoi(v_string.substr(c_pos_v+1, v_string.length() - c_pos_v -1));

        for (int i = 1; i <= 100; i++){
            x += vx;
            y += vy;
            if (x > width/2)
                x -= width;
            else if ( x< -width/2)
                x += width;
            if (y > height/2)
                y -= height;
            else if ( y< -height/2)
                y += height;
        }
        if (x == 0 || y == 0)
            continue;
        if (x > 0 && y > 0)
            q1++;
        if (x >0 && y < 0)
            q4++;
        if (x <0 && y < 0)
            q3++;
        if (x <0 && y > 0)
            q2++;
    }
    file.close();
    cout << q1 << " " << q2 << " " <<q3 << " " << q4  << endl;
    int ans = q1*q2*q3*q4;
    return ans;
}

int main(){
    int safety_factor = safetyFactor();
    cout << safety_factor;
}