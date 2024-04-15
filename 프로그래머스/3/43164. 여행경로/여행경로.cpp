#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

vector<string> answer, result;
vector<bool> visit;

bool compare(vector<string> lhs, vector<string> rhs) {
    if(lhs[0] == rhs[0])
        return lhs[1] < rhs[1];
    return lhs[0] < rhs[0]; 
}

void dfs(string current, vector<vector<string>> & tickets, int count) {

    answer.push_back(current);
    if(count == tickets.size()) {
        return;
    }

    for(int i=0; i<tickets.size(); i++) {
        if(visit[i] == false && tickets[i][0] == current) {
            visit[i] = true;
            dfs(tickets[i][1], tickets, count + 1);
            if(answer.size() < tickets.size()) {
                answer.pop_back();
                visit[i] = false;
            }
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    
    visit.resize(tickets.size(), false);
    sort(tickets.begin(), tickets.end(), compare);

    dfs("ICN", tickets, 0);

    return answer;
    
}