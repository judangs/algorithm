#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

queue<pair<int, int>> q;

int solution(vector<int> players, int m, int k) {
    
    
    int server = 0;
    
    int answer = 0;
    for(int time=0; time<players.size(); time++) {
        if(!q.empty()) {
            if(q.front().first + k == time) {
                server -= q.front().second;
                q.pop();
            }
        }
        if(players[time] == 0) continue;
        if(players[time] >= (server + 1) * m) {
            int need = (players[time] - ((server + 1) * m)) / m + 1;
            
            answer += need, server += need;
            q.push({time, need});
        }
    }
    
    return answer;
}