#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

queue<pair<int, int>> q;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int second = 0, current = 0;
    for(int i=0; i<truck_weights.size(); i++) {
        
        second++;
        if(!q.empty()) {
            while(q.front().second == second) {
                current -= q.front().first;
                answer = max(answer, q.front().second);
                q.pop();
            }
        }
        
        if(q.size() < bridge_length && current + truck_weights[i] <= weight) {
            q.push(make_pair(truck_weights[i], second + bridge_length));
            current += truck_weights[i];
        }
        else {
            i--;
        }
    }
    
    while(!q.empty()) {
        answer = max(answer, q.front().second);
        q.pop();
    }
    
    return answer;
}