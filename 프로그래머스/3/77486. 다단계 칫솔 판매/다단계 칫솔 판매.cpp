#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

map<string, string> m;
map<string, int> revenue;

void dfs(string current, int cost) {
    if(current == "-" || cost < 10) {
        revenue[current] += cost;
        return;
    }

    revenue[current] += cost - (cost / 10);
    dfs(m[current], cost / 10);
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    for(int current=0; current < enroll.size(); current++) {
        m[enroll[current]] = referral[current];
    }

    for(int current=0; current < seller.size(); current++) {
        dfs(seller[current], amount[current] * 100);
    }

    vector<int> answer;
    for(int current=0; current < enroll.size(); current++) {
        answer.push_back(revenue[enroll[current]]);
    }

    return answer;
}