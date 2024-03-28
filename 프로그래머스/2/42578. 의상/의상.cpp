#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

map<string, int> m;
vector<int> theme;

/*
int result = 0;

void dfs(int depth, int count, int ptr, int total) {
    if(depth == count) {
        result += total;
        return;
    }

    for(int i=ptr; i<theme.size(); i++) {
        dfs(depth + 1, count, i + 1, total * theme[i]);
    }
}
*/

int solution(vector<vector<string>> clothes) {
    
    for(vector<string> cloth: clothes) {
        m[cloth[1]]++;
    }

    for(auto iter=m.begin(); iter != m.end(); iter++) {
        theme.push_back(iter->second);
    }
    
    int result = 1;
    for(int i=0; i<theme.size(); i++) {
        result *= (theme[i] + 1);
    }
    return result - 1;
}