#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<pair<int, int>> sale;
vector<pair<int, int>> result;
vector<vector<int>> user_info;


void solve(vector<int> & emoticons) {
    int emoticon_plus = 0;
    int total_cost = 0;
    for(auto user: user_info) {
        int want = user[0];
        int max_cost = user[1];
        
        int cost = 0;
        for(auto emoticon: sale) {
            if(emoticon.second >= want) {
                cost += (emoticons[emoticon.first] * (100 - emoticon.second) / 100);
            }
        }
        if(cost >= max_cost)
            emoticon_plus += 1;
        else
            total_cost += cost;
        
        result.push_back(make_pair(emoticon_plus, total_cost));
        
    }
}

void dfs(int depth, vector<int> & event, vector<int> & emoticons) {
    if(depth == emoticons.size()) {
        solve(emoticons);
        return;
    }
    
    for(int idx=0; idx<event.size(); idx++) {
        sale.push_back(make_pair(depth, event[idx]));
        dfs(depth + 1, event, emoticons);
        sale.pop_back();
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    
    vector<int> event = {10, 20, 30, 40};
    user_info = users;
    
    
    dfs(0, event, emoticons);
    
    int root_idx = 0;
    for(int i=0; i<result.size(); i++) {
        if(result[i].first > result[root_idx].first) {
            root_idx = i;
        }
        else if(result[i].first == result[root_idx].first) {
            if(result[i].second > result[root_idx].second) {
                root_idx = i;
            }
        }
    }
    
    vector<int> answer = {result[root_idx].first, result[root_idx].second};
    return answer;
}