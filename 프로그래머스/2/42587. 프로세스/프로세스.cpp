#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(vector<int> priorities, int location) {
    
    queue<pair<int, int>> q;
    for(int i=0; i<priorities.size(); i++) {
        q.push(make_pair(i, priorities[i]));
    }

    int answer = 1;
    int max_value = *max_element(priorities.begin(), priorities.end());
    while(!q.empty()) {
        if(q.front().second != max_value) {
            auto next = q.front();
            q.push(next);
        }
        else {
            if(max_value == q.front().second) {
                if(location == q.front().first) {
                    return answer;
                }
                else {
                    auto iter = find(priorities.begin(), priorities.end(), max_value);
                    priorities.erase(iter);
                    answer++;
                }
            }
        }

        q.pop();

        max_value = *max_element(priorities.begin(), priorities.end());
    }

    return answer;
}