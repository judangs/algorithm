#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

queue<pii> q;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    for(int current=0; current < progresses.size(); current++) {
        int day = (100 - progresses[current]) / speeds[current];
        if((100 - progresses[current]) % speeds[current] != 0)
            day++;
        q.push({current, day});
    }

    vector<int> answer;
    while(!q.empty()) {
        int deploy = 0;
        int comp = q.front().second;
        while(!q.empty() && q.front().second <= comp) {
            deploy++;
            q.pop();
        }
        
        answer.push_back(deploy);
    }

    return answer;
}