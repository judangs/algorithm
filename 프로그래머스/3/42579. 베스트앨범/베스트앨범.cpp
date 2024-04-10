#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b) {
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

typedef pair<string, vector<pair<int, int>>> dict;

bool cmp(dict a, dict b) {
    long long total_a = 0, total_b = 0;
    for(pair<int, int> sub: a.second) 
        total_a += sub.second;
    for(pair<int, int> sub: b.second)
        total_b += sub.second;
    
    return total_a > total_b;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    map<string, vector<pair<int, int>>> m;
    
    for(int i=0; i<genres.size(); i++) {
        m[genres[i]].push_back(make_pair(i, plays[i]));
    }
    
    for(auto iter=m.begin(); iter!=m.end(); iter++) {
        sort(iter->second.begin(), iter->second.end(), compare);
    }
    
    vector<dict> arr(m.begin(), m.end());
    sort(arr.begin(), arr.end(), cmp);
    
    vector<int> answer;
    for(auto iter=arr.begin(); iter!=arr.end(); iter++) {
        if(iter->second.size() == 1) {
            answer.push_back(iter->second.front().first);
            continue;
        }
        for(auto current=iter->second.begin(); current != iter->second.begin() + 2; current++) {
            answer.push_back(current->first);
        }
    }
    
    return answer;
    
}