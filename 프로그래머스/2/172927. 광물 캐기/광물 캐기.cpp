#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> p = {
    {1, 1, 1},
    {5, 1, 1},
    {25, 5, 1}
};

int solution(vector<int> picks, vector<string> minerals) {


    vector<tuple<int, int, int>> mine;
    
    int total = (picks[0] + picks[1] + picks[2]) * 5;
    int current = 0;
    while(current < minerals.size()) {
        if(current >= total)
            break;
        
        int d = 0, i = 0, s = 0;
        int pivot = current;
        for(int next= current; next<pivot+5 && next<minerals.size(); next++) {
            if(minerals[next] == "diamond") d++;
            else if(minerals[next] == "iron") i++;
            else s++;
            current++;
        }

        mine.push_back(make_tuple(d, i, s));
    }

    sort(mine.rbegin(), mine.rend());
    
    int answer = 0;
    for(auto mineset: mine) {
        int d, i, s;
        tie(d, i, s) = mineset;
        
        for(int idx=0; idx<picks.size(); idx++) {
            if(picks[idx] > 0) {
                answer += (p[idx][0] * d + p[idx][1] * i + p[idx][2] * s);
                picks[idx]--;
                break;
            }
        }
    }

    return answer;
}