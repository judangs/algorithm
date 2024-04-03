#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <set>


using namespace std;

vector<bool> visit;
set<set<string>> select_list;


bool check(vector<string> select_user, vector<string> banned_id) {

    for(int i=0; i<select_user.size(); i++) {
        if(select_user[i].size() != banned_id[i].size())
            return false;
        
        for(int j=0; j<select_user[i].size(); j++) {
            if(banned_id[i][j] == '*') continue;
            
            if(select_user[i][j] != banned_id[i][j])
                return false;
        }
    }
    
    return true;
}

void permutation(int depth, vector<string> & select_user, vector<string> & user_id, vector<string> & banned_id) {
    if(depth == banned_id.size()) {
        if(check(select_user, banned_id)) {
            select_list.insert(set<string>(select_user.begin(), select_user.end()));
        }
        return;
    }
    
    for(int i=0; i<user_id.size(); i++) {
        if(visit[i] == false) {
            visit[i] = true;
            select_user.push_back(user_id[i]);
            permutation(depth + 1, select_user, user_id, banned_id);
            select_user.pop_back();
            visit[i] = false;
        }
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    
    visit.resize(user_id.size(), false);

    vector<string> select_user;
    permutation(0, select_user, user_id, banned_id);
    return select_list.size();
}