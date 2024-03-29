#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

vector<int> select1;
vector<int> select2;

vector<int> user1_case;
vector<int> user2_case;

vector<int> result;
int max_count = 0;

void dfs(int depth, int count, int value, vector<vector<int>> & dice, int user) {
    if(depth == count) {
        if(user == 0) {
            user1_case.push_back(value);
        }
        else {
            user2_case.push_back(value);
        }
        return;
    }

    for(int i=0; i<6; i++) {
        if(user == 0) {
            int idx = select1[depth];
            dfs(depth + 1, count, value + dice[idx][i], dice, user);
        }
        else {
            int idx = select2[depth];
            dfs(depth + 1, count, value + dice[idx][i], dice, user);
        }

    }
}

int solver() {
    sort(user1_case.begin(), user1_case.end());
    sort(user2_case.begin(), user2_case.end());

    int total = 0;
    for(int value: user1_case) {
        int idx = lower_bound(user2_case.begin(), user2_case.end(), value) - user2_case.begin();
        total += (idx - 1);
    }
    
    return total;
}

void combination(int depth, int count, int ptr, vector<vector<int>> & dice) {
    if(depth == count / 2) {
        for(int i=0; i<dice.size(); i++) {
            if(find(select1.begin(), select1.end(), i) == select1.end()) {
                select2.push_back(i);
            }
        }
        dfs(0, count / 2, 0, dice, 0);
        dfs(0, count / 2, 0, dice, 1);

        int win_count = solver();
        
        if(max_count < win_count) {
            max_count = win_count;
            result = select1;
        }

        select2.clear();
        user1_case.clear();
        user2_case.clear();
        return;
    }

    for(int i=ptr; i<count; i++) {
        select1.push_back(i);
        combination(depth + 1, count, i + 1, dice);
        select1.pop_back();
    }
} 

vector<int> solution(vector<vector<int>> dice) {

    combination(0, dice.size(), 0, dice);
    
    vector<int> answer = result;
    for(int i=0; i<answer.size(); i++) 
        answer[i]++;
    return answer;
}