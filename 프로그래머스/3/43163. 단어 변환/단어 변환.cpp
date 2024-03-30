#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<bool> visit;
int result = INT32_MAX;

int find_count(string a, string b) {
    int ret = 0;
    for(int i=0; i<a.size(); i++) {
        if(a[i] != b[i])
            ret++;
    }
    
    return ret;
}

void dfs(int depth, string begin, string target, vector<string> & words) {
    if(begin == target) {
        result = min(result, depth);
        return;
    }
    
    for(int i=0; i<words.size(); i++) {
        if(find_count(begin, words[i]) == 1 && visit[i] == false) {
            visit[i] = true;
            dfs(depth + 1, words[i], target, words);
            visit[i] = false;
        }
    }
}

int solution(string begin, string target, vector<string> words) {
    
    visit.resize(words.size(), false);
    dfs(0, begin, target, words);
    
    if(result == INT32_MAX)
        return 0;
    else
        return result;
}